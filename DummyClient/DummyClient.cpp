#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "BufferReader.h"
#include "ServerPacketHandler.h"

class ServerSession : public PacketSession
{
public:
	~ServerSession()
	{
		cout << "~ServerSession" << endl;
	}

	virtual void OnConnected() override
	{
		cout << "Connected To Server" << endl;
	}

	virtual void OnRecvPacket(BYTE* buffer, int32 len) override
	{
		PacketSessionRef session = GetPacketSessionRef();

		//First, check what kind of packet is comming
		// and then, call the function that handles the packet
		ServerPacketHandler::HandlePacket(session, buffer, len);


	}

	virtual void OnSend(int32 len) override
	{
		//cout << "OnSend Len = " << len << endl;
	}

	virtual void OnDisconnected() override
	{
		//cout << "Disconnected" << endl;
	}
};

int main()
{
	ServerPacketHandler::Init();

	ClientServiceRef service = MakeShared<ClientService>(
		NetAddress(L"20.200.230.157", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager 등
		1);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 2; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	wchar_t test[] = L"Hello";



	//Protocol::H_LOGIN logPkg;
	//logPkg.set_str("Hello, I am Hololens2");
	//auto sendBuffer = ServerPacketHandler::MakeSendBuffer(logPkg);

	Protocol::C_TEST testPkg;
	

	while (true)
	{


		this_thread::sleep_for(0.1s);
		
	}


	




	GThreadManager->Join();
}