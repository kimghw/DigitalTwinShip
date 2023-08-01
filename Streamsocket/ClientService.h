#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Networking.Sockets.h>
#include <winrt/Windows.Networking.h>
#include <winrt/Windows.Storage.Streams.h>
#include <windows.h>

#include <iostream>
#include <thread>
#include <mutex>

#include "ServerPacketHandler.h"


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
	IAsyncAction		 RegisterAsync(StreamSocket& socket, uint8_t recvBufSize);
	bool			     RegisterRecvEvent(StreamSocket& socket, uint8_t recvBufSize);
	bool			     ProcessRecvEvent(uint8_t* buffer, uint8_t recvBufSize);

	bool				 RegisterSendEvent(StreamSocket& socket);
	bool				 BufferToVector(IBuffer& buffer, OUT std::vector<uint8_t>& recvBuffer);

private:
	// Lock이 필요할거 같은데...
	StreamSocket _socket;
	std::mutex _lock;
	//BYTE* _sendbuffer;
	//BYTE* _recvbuffer;


	HostName _serverHost{ L"0.0.0.0" }; // Replace with the server IP address or hostname
	hstring _serverPort{ L"0" };
	

	const unsigned int _recvBufSize = 1024;
	const unsigned int _sendBufSize = 1024;

	std::vector<uint8_t> _recvBuffer;
	


public:
	ServerPacketHandler* _serverPacketHandler;

};



//////////////////

