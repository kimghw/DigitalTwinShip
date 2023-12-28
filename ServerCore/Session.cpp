#include "pch.h"
#include "Session.h"
#include "SocketUtils.h"
#include "Service.h"

void PacketHeaderByteSwap(BYTE* byte);

/*--------------
	Session
---------------*/

Session::Session() : _recvBuffer(BUFFER_SIZE)
{
	_socket = SocketUtils::CreateSocket();
}

Session::~Session()
{
	SocketUtils::Close(_socket);
}

void Session::Send(SendBufferRef sendBuffer)
{
	if (IsConnected() == false)
		return;

	bool registerSend = false;

	// ÇöÀç RegisterSend°¡ °É¸®Áö ¾ÊÀº »óÅÂ¶ó¸é, °É¾îÁØ´Ù
	{
		WRITE_LOCK;

		_sendQueue.push(sendBuffer);

		if (_sendRegistered.exchange(true) == false)
			registerSend = true;
	}
	
	if (registerSend)
		RegisterSend();
}

bool Session::Connect()
{
	return RegisterConnect();
}

void Session::Disconnect(const WCHAR* cause)
{
	if (_connected.exchange(false) == false)
		return;

	// TEMP
	wcout << "Disconnect : " << cause << endl;

	RegisterDisconnect();
}

HANDLE Session::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}

void Session::Dispatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	//cout << "The number of incomming data :" << numOfBytes << "session.64line" << endl;
	switch (iocpEvent->eventType)
	{
	case EventType::Connect:
		ProcessConnect();
		break;
	case EventType::Disconnect:
		ProcessDisconnect();
		break;
	case EventType::Recv:
		ProcessRecv(numOfBytes);
		//std::cout << numOfBytes << endl;
		break;
	case EventType::Send:
		ProcessSend(numOfBytes);
		break;
	default:
		break;
	}
}

bool Session::RegisterConnect()
{
	if (IsConnected())
		return false;

	if (GetService()->GetServiceType() != ServiceType::Client)
		return false;

	if (SocketUtils::SetReuseAddress(_socket, true) == false)
		return false;

	if (SocketUtils::BindAnyAddress(_socket, 0/*³²´Â°Å*/) == false)
		return false;

	_connectEvent.Init();
	_connectEvent.owner = shared_from_this(); // ADD_REF

	DWORD numOfBytes = 0;
	SOCKADDR_IN sockAddr = GetService()->GetNetAddress().GetSockAddr();
	if (false == SocketUtils::ConnectEx(_socket, reinterpret_cast<SOCKADDR*>(&sockAddr), sizeof(sockAddr), nullptr, 0, &numOfBytes, &_connectEvent))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			_connectEvent.owner = nullptr; // RELEASE_REF
			return false;
		}
	}

	return true;
}

bool Session::RegisterDisconnect()
{
	_disconnectEvent.Init();
	_disconnectEvent.owner = shared_from_this(); // ADD_REF

	if (false == SocketUtils::DisconnectEx(_socket, &_disconnectEvent, TF_REUSE_SOCKET, 0))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			_disconnectEvent.owner = nullptr; // RELEASE_REF
			return false;
		}
	}

	return true;
}

void Session::RegisterRecv()
{
	if (IsConnected() == false)
		return;

	_recvEvent.Init();
	_recvEvent.owner = shared_from_this(); // ADD_REF

	WSABUF wsaBuf;
	wsaBuf.buf = reinterpret_cast<char*>(_recvBuffer.WritePos());
	wsaBuf.len = _recvBuffer.FreeSize();

	DWORD numOfBytes = 0;
	DWORD flags = 0;
	if (SOCKET_ERROR == ::WSARecv(_socket, &wsaBuf, 1, OUT &numOfBytes, OUT &flags, &_recvEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			_recvEvent.owner = nullptr; // RELEASE_REF
		}
	}
}

void Session::RegisterSend()
{
	if (IsConnected() == false)
		return;

	_sendEvent.Init();
	_sendEvent.owner = shared_from_this(); // ADD_REF

	// º¸³¾ µ¥ÀÌÅÍ¸¦ sendEvent¿¡ µî·Ï
	{
		WRITE_LOCK;

		int32 writeSize = 0;
		while (_sendQueue.empty() == false)
		{
			SendBufferRef sendBuffer = _sendQueue.front();

			writeSize += sendBuffer->WriteSize();
			// TODO : ¿¹¿Ü Ã¼Å©

			_sendQueue.pop();
			_sendEvent.sendBuffers.push_back(sendBuffer);
		}
	}

	// Scatter-Gather (Èð¾îÁ® ÀÖ´Â µ¥ÀÌÅÍµéÀ» ¸ð¾Æ¼­ ÇÑ ¹æ¿¡ º¸³½´Ù)
	Vector<WSABUF> wsaBufs;
	wsaBufs.reserve(_sendEvent.sendBuffers.size());
	for (SendBufferRef sendBuffer : _sendEvent.sendBuffers)
	{
		WSABUF wsaBuf;
		wsaBuf.buf = reinterpret_cast<char*>(sendBuffer->Buffer());
		wsaBuf.len = static_cast<LONG>(sendBuffer->WriteSize());
		wsaBufs.push_back(wsaBuf);
	}

	DWORD numOfBytes = 0;
	if (SOCKET_ERROR == ::WSASend(_socket, wsaBufs.data(), static_cast<DWORD>(wsaBufs.size()), OUT &numOfBytes, 0, &_sendEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			_sendEvent.owner = nullptr; // RELEASE_REF
			_sendEvent.sendBuffers.clear(); // RELEASE_REF
			_sendRegistered.store(false);
		}
	}
}

void Session::ProcessConnect()
{
	_connectEvent.owner = nullptr; // RELEASE_REF

	_connected.store(true);

	// ¼¼¼Ç µî·Ï
	GetService()->AddSession(GetSessionRef());

	// ÄÁÅÙÃ÷ ÄÚµå¿¡¼­ ÀçÁ¤ÀÇ
	OnConnected();

	// ¼ö½Å µî·Ï
	RegisterRecv();
}

void Session::ProcessDisconnect()
{
	_disconnectEvent.owner = nullptr; // RELEASE_REF

	OnDisconnected(); // ÄÁÅÙÃ÷ ÄÚµå¿¡¼­ ÀçÁ¤ÀÇ
	GetService()->ReleaseSession(GetSessionRef());
}

// 문제생길 시 락걸면 될듯
void Session::ProcessRecv(int32 numOfBytes)
{
	_recvEvent.owner = nullptr; // RELEASE_REF
	int32 unprocessedData = 0;
	BYTE* pinitBuffer = nullptr;
	static int16 initHeaderSize = 0; //
	static bool accum = false;

	if (accum == false)
	{

		//PacketHeaderByteSwap(_recvBuffer.WritePos());
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_recvBuffer.WritePos());

		pinitBuffer    = _recvBuffer.WritePos();
		initHeaderSize = header->size;
	}
	else if (accum == true)
	{
		unprocessedData = _recvBuffer.DataSize();
		_recvBuffer.OnWrite(numOfBytes);
	}


	if (numOfBytes == 0)
	{
		Disconnect(L"Recv 0");
		return;
	}

	if (numOfBytes == initHeaderSize && accum == false)
	{
		//accum = false;
		_recvBuffer.OnWrite(numOfBytes);
	}
	else if (numOfBytes != initHeaderSize && accum == false)
	{
		// 보낸 사이즈보다 들어온 사이즈가
		// first partial data comming
		/*	const char* partialBuf = reinterpret_cast<const char*>(_recvBuffer.WritePos());
		int32 length = strlen(partialBuf);

		if (length > numOfBytes)
		{
			numOfBytes = initHeaderSize;
		}*/
		
		if (_recvBuffer.OnWrite(numOfBytes) == false)
		{
			Disconnect(L"OnWrite Overflow");
			return;
		}

		if (_recvBuffer.DataSize() < initHeaderSize)
		{
			accum = true;
			RegisterRecv();
			return;
		}
		//numOfBytes = initHeaderSize;
	}
	else if (_recvBuffer.DataSize() == initHeaderSize && accum == true)
	{
		// 누적된 패킷사이즈가 헤더의 사이즈랑 같음
		accum = false;

	}
	else if (_recvBuffer.DataSize() > initHeaderSize && accum == true)
	{
		// 누적된 패킷사이즈가 헤더의 사이즈랑 같음
		accum = true;

	}
	else if (_recvBuffer.DataSize() < initHeaderSize && accum == true)
	{
		accum = true;
		RegisterRecv();
		return;
	}
	
	int32 dataSize = _recvBuffer.DataSize();
	int32 processLen = OnRecv(_recvBuffer.ReadPos(), dataSize);
	if (processLen < 0 || dataSize<processLen || _recvBuffer.OnRead(processLen) == false)
	{
		Disconnect(L"OnRead Overflow");
		return;
	}

	if ( processLen < dataSize )
	{
		accum = true;
	}

	_recvBuffer.Clean();

	// ¼ö½Å µî·Ï
	RegisterRecv();

}

void Session::ProcessSend(int32 numOfBytes)
{
	_sendEvent.owner = nullptr; // RELEASE_REF
	_sendEvent.sendBuffers.clear(); // RELEASE_REF

	if (numOfBytes == 0)
	{
		Disconnect(L"Send 0");
		return;
	}

	// ÄÁÅÙÃ÷ ÄÚµå¿¡¼­ ÀçÁ¤ÀÇ
	OnSend(numOfBytes);

	WRITE_LOCK;
	if (_sendQueue.empty())
		_sendRegistered.store(false);
	else
		RegisterSend();
}

void Session::HandleError(int32 errorCode)
{
	switch (errorCode)
	{
	case WSAECONNRESET:
	case WSAECONNABORTED:
		Disconnect(L"HandleError");
		break;
	default:
		// TODO : Log
		cout << "Handle Error : " << errorCode << endl;
		break;
	}
}

/*-----------------
	PacketSession
------------------*/

PacketSession::PacketSession()
{
}

PacketSession::~PacketSession()
{
}

// [size(2)][id(2)][data....][size(2)][id(2)][data....]
int32 PacketSession::OnRecv(BYTE* buffer, int32 len)
{
	//std::cout << "recevived data_Session_314" << endl;
	int32 processLen = 0;
	
	while (true)
	{

		int32 dataSize = len - processLen;
		// ÃÖ¼ÒÇÑ Çì´õ´Â ÆÄ½ÌÇÒ ¼ö ÀÖ¾î¾ß ÇÑ´Ù
		if (dataSize < sizeof(PacketHeader))
			break;

		PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
		// Çì´õ¿¡ ±â·ÏµÈ ÆÐÅ¶ Å©±â¸¦ ÆÄ½ÌÇÒ ¼ö ÀÖ¾î¾ß ÇÑ´Ù
		if (dataSize < header.size) break;
		

			// The second factor should switch to header.size
		OnRecvPacket(&buffer[processLen], header.size);
		int leftData = dataSize - header.size;
		processLen += header.size;

		// 남은 데이터 크기 계산
		if ( leftData > 0 && processLen > 0 )
		{
			PacketHeaderByteSwap(buffer + processLen);
			header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
		}

		// 데이터 조각인가?
		if (leftData < header.size)
			break;
	}

	return processLen;
}

void PacketHeaderByteSwap(BYTE* byte)
{
	std::swap(*byte, *(byte + 1));
	std::swap(*(byte + 2), *(byte + 3));
}

int32 ValidateNumOfByte(BYTE* byte, int32 numOfBytes)
{
	int32 length = 0;
	while (*(byte++) != 0x00)
	{
		length++;
		if (length = numOfBytes )
		{
			numOfBytes = length;
			break;
		}
	}
	return length;
}

