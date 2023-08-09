#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Networking.Sockets.h>
#include <winrt/Windows.Networking.h>
#include <winrt/Windows.Storage.Streams.h>
#include <windows.h>

#include <iostream>
#include <thread>
#include <mutex>

#include "Type.h"
#include <stdint.h>


using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage::Streams;



class ClientService
{

public:
	ClientService();
	ClientService(Windows::Networking::HostName serverHost, winrt::hstring serverPort)
		: _serverHost(serverHost), _serverPort(serverPort)
	{
	}
	~ClientService();

	IAsyncAction		 Start(HostName& serverHost, hstring& port);
	IAsyncAction		 RegisterAsync(StreamSocket& socket, uint32_t recvBufSize);
	//bool			     RegisterRecvEvent(StreamSocket& socket, uint8_t recvBufSize);
	bool			     OnReceivePacket(uint8_t* buffer, uint32_t recvBufSize);

	//bool				 RegisterSendEvent(StreamSocket& socket);
	//bool				 BufferToVector(IBuffer& buffer, OUT std::vector<uint8_t>& recvBuffer);
	bool	BufferToVector(IBuffer& buffer, OUT std::vector<BYTE>& recvBuffer);


	StreamSocket& GetSocket() { return _socket; }
	uint32_t GetRecvBufferSize() { return _recvBufSize; }

private:
	// Lock이 필요할거 같은데...
	StreamSocket _socket;
	std::mutex _lock;

	//BYTE* _sendbuffer;
	//BYTE* _recvbuffer;

	HostName _serverHost{ L"127.0.0.1" }; // Replace with the server IP address or hostname
	hstring _serverPort{ L"7777" };
	

	const uint32_t _recvBufSize = 1024;
	const uint32_t _sendBufSize = 1024;

	std::vector<uint8_t> _recvBuffer;
	
};

struct PacketHeader
{
	uint32_t id;
	uint32_t size;
};


//////////////////

