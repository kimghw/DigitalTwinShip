#include "ClientService.h"

using namespace winrt;
using namespace std;

ClientService::ClientService()
{

}


ClientService::~ClientService()
{

}

IAsyncAction ClientService::Start(HostName& serverHost, hstring& serverPort)
{

	_serverHost = serverHost;
	_serverPort = serverPort;

	// Create a stream socket and connect to the server.
	_socket = StreamSocket();
	// Socket checks the connection health
	_socket.Control().KeepAlive(true);
	// data will be sent as soon as possible without waiting for the buffer to fill up
	_socket.Control().NoDelay(true);
	_socket.Control().QualityOfService(SocketQualityOfService::LowLatency);
	//_socket.Control().IgnorableServerCertificateErrors().Append(ChainValidationResult::Untrusted);
	//_socket.Control().IgnorableServerCertificateErrors().Append(ChainValidationResult::InvalidName);
	
    // ServerConnect
	try
	{
		co_await _socket.ConnectAsync(_serverHost, _serverPort);
		RegisterRecvEvent(_socket, _recvBufSize);

		cout << "Connected to server" << endl;
		cout << "DataReader is being created..." << endl;

	}
	catch (const hresult_error& ex)
	{
		winrt::hstring message = ex.message();
		OutputDebugStringW(message.c_str());
	}

	

}

bool ClientService::RegisterRecvEvent(StreamSocket& socket, uint8_t recvBufSize)
{
	const unsigned int maxLength = recvBufSize;

	DataReader reader{ socket.InputStream() };
	reader.InputStreamOptions(winrt::Windows::Storage::Streams::InputStreamOptions::Partial);
	auto operation = reader.LoadAsync(maxLength);
	operation.Completed([this, reader, maxLength](IAsyncOperation<uint32_t> const& operation, AsyncStatus status) {
		// This code will be executed when the operation is completed
		if (status == AsyncStatus::Completed) {

			uint32_t bytesRead = operation.GetResults();
			std::vector<uint8_t> recvBuffer(maxLength);
			reader.ReadBytes(recvBuffer);

			if (bytesRead > 0) {
				// Process the received data
				ProcessRecvEvent(recvBuffer.data(), bytesRead);
				//_reader.ReadBytes()
			}
		}
		else {
			// Handle the error
		}
	});

	return true;
	
}

IAsyncAction ClientService::RegisterAsync(StreamSocket& socket, uint8_t recvBufSize)
{
	const unsigned int maxLength = recvBufSize;
	// Using the socket, Initialize the reader with the input stream of a 'StreamSocket'
	DataReader reader{ socket.InputStream() };
	reader.InputStreamOptions(winrt::Windows::Storage::Streams::InputStreamOptions::Partial);

	try
	{
		// LoadAsyn  returns the number of bytes that have been read
		uint32_t bytesRead = co_await reader.LoadAsync(maxLength);
		if (bytesRead > 0)
		{
			
			// DataReader does not provide a way to read the data as a byte array
			// Read all the data as an 'IBuffer' from the DataReader's internal buffer
			// The keyword 'auto' is used because the the method 'ReadBuffer' returns an 'IBuffer'
			auto ibuffer = reader.ReadBuffer(bytesRead);
			// Convert the 'IBuffer' to a 'std::vector<uint8_t>' using the helper function 'BufferToVector'
			std::vector<uint8_t> recvVecBuffer(bytesRead);
			BufferToVector(ibuffer, OUT recvVecBuffer);

			// Process the received data
			ProcessRecvEvent(recvVecBuffer.data(), recvVecBuffer.size());
		}
	}
	catch (winrt::hresult_error  const& ex)
	{
		std::wcout << L"Error: " << ex.message().c_str() << std::endl;
	}

}

// Buffer to vector helper function
// This method casuse more resources to return the vector object.
// It will cause lock racing condition if the buffer is a member of the class 
// because the buffer is shared with other threads.
bool ClientService::BufferToVector(IBuffer& buffer, OUT std::vector<uint8_t>& recvBuffer)
{
	auto dataReader = DataReader::FromBuffer(buffer);
	//std::vector<uint8_t> data(buffer.Length());
	// array_view<uint_8>(data) 은 'data'의 레퍼런스를 넘겨서 데이터를 채워준다.
	dataReader.ReadBytes(array_view<uint8_t>(recvBuffer));
	return true;
}


bool ClientService::ProcessRecvEvent(uint8_t* buffer, uint8_t recvBufSize)
{

	return true;
}
