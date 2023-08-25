#include <iostream>
#include <winrt/Windows.Foundation.h>
#include "Session.h"






// Usage example
int main()
{
	// initialize ....
	winrt::init_apartment();

	std::shared_ptr<Session> clientSession = std::make_shared<Session>();

	clientSession->OnMessageReceived = [](const Protocol::S_TEST& message) {
		std::wcout << L"Received message: " << message.player().c_str() << std::endl;
	};

	try
	{
		// Use the both of IP address and hostname from the server project
		clientSession->ConnectAsync(L"127.0.0.1", L"7777").get();
		std::this_thread::sleep_for(std::chrono::seconds(3)); // Just a dummy delay to keep the program running
	}
	catch (const winrt::hresult_error& ex)
	{
		std::wcerr << L"Error: " << ex.message().c_str() << std::endl;
	}



	// This will be called within a thread
	try
	{
		clientSession->ListenForMessages(); // Start listening without blocking
		std::this_thread::sleep_for(std::chrono::seconds(100)); // Just a dummy delay to keep the program running
	}
	catch (const winrt::hresult_error& ex)
	{
		std::wcerr << L"Error: " << ex.message().c_str() << std::endl;
	}
	

	return 0;
}
