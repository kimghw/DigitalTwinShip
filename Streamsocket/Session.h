#pragma once
#include <winrt/Windows.Foundation.h>

#include <winrt/Windows.Networking.h>
#include <winrt/Windows.Networking.Sockets.h>
#include <winrt/Windows.Storage.Streams.h>
#include "Protocol.pb.h" // This is the generated protobuf header
#include <functional>

struct Packetheader
{
	uint16_t size;
	uint16_t id;
};

class Session
{
private:
	winrt::Windows::Networking::Sockets::StreamSocket socket;
	winrt::Windows::Storage::Streams::DataReader reader{ nullptr };
	winrt::Windows::Storage::Streams::DataWriter writer{ nullptr };


public:
	using MessageReceivedHandler = std::function<void(const Protocol::S_TEST&)>;
	MessageReceivedHandler OnMessageReceived;

	winrt::Windows::Foundation::IAsyncAction ConnectAsync(const winrt::hstring& hostname, const winrt::hstring& port)
	{
		winrt::Windows::Networking::HostName serverHostName{ hostname };
		co_await socket.ConnectAsync(serverHostName, port);

		std::cout << "Connected to server" << std::endl;
		reader = winrt::Windows::Storage::Streams::DataReader{ socket.InputStream() };
		writer = winrt::Windows::Storage::Streams::DataWriter{ socket.OutputStream() };
	}

	winrt::Windows::Storage::Streams::DataWriter& GetWriter()
	{
		if (!writer) // 이렇게 변경합니다.
		{
			throw std::runtime_error("DataWriter has not been initialized.");
		}
		return writer;
	}



	winrt::Windows::Foundation::IAsyncAction SendAsync(const Protocol::S_TEST& pkt)
	{
		//std::string serializedMessage = message.SerializeAsString();
		//writer.WriteUInt32((uint32_t)serializedMessage.size());
		//writer.WriteBytes(winrt::array_view<const uint8_t>((const uint8_t*)serializedMessage.data(), serializedMessage.size()));
		//co_await writer.StoreAsync();
		//co_await writer.FlushAsync();
	}

	winrt::Windows::Foundation::IAsyncAction ListenForMessages()
	{
		while (true)
		{

			// Read the size of the message
			// the return value of LoadAsyn is the number of bytes loaded

			uint16_t messageSize = co_await reader.LoadAsync(sizeof(uint32_t));
			
			if (messageSize < sizeof(uint16_t))
				co_return;

			reader.ByteOrder(winrt::Windows::Storage::Streams::ByteOrder::LittleEndian);

			// Read the message size from the buffer
			// and Check the id of the packet

			messageSize = reader.ReadUInt16();
			uint16_t PKT_ID = reader.ReadUInt16();
			std::cout << "MessageSize : " << messageSize << std::endl;
			std::cout << "PKT_ID : " << PKT_ID << std::endl;



			uint32_t bytesRead = co_await reader.LoadAsync(messageSize - sizeof(Packetheader));
			/*if (bytesRead != messageSize)
				co_return;*/

			std::vector<uint8_t> buffer(bytesRead);
			reader.ReadBytes(winrt::array_view<uint8_t>(buffer));

			Protocol::S_TEST pkt;
			if (!pkt.ParseFromArray(buffer.data(), buffer.size()))
			{
				std::wcerr << L"Failed to parse received message." << std::endl;
				co_return;
			}

			std::wcout << L"Received message: " << pkt.player().c_str() << std::endl;
			std::cout << "Received message: " << pkt.id() << std::endl;
			//if (OnMessageReceived)
			//{
			//	OnMessageReceived(pkt);
			//}
		}
	}
};

