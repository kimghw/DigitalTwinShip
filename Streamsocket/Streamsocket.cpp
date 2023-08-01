// Streamsocket.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Networking.Sockets.h>
#include <winrt/Windows.Networking.h>
#include <winrt/Windows.Storage.Streams.h>
#include "ClientService.h"



using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage::Streams;

int main()
{
	winrt::init_apartment();

	HostName serverHost{ L"127.0.0.1" }; // Replace with the server IP address or hostname
	hstring serverPort{ L"7777" }; // Replace with the server port
	//Windows::Foundation::TimeSpan timeout{ 10000000L }; // 1 second timeout	

	using ClientServicerRef = std::shared_ptr<class ClientService>;
	ClientServicerRef clientservice = std::make_shared<ClientService>();

	clientservice->Start(serverHost, serverPort);

	while (true)
	{
	}


}


