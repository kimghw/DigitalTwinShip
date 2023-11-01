#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "BufferReader.h"
#include "ServerPacketHandler.h"
#include "nlohmann/json.hpp"

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
		NetAddress(L"20.200.230.157", 8000),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager 등
		3);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
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

	Protocol::C_MAIN mainJson;
	nlohmann::json j;
	//nlohmann::json j = nlohmann::json::array();

	//j.push_back({ "Motor", 1.0f });
	//j.push_back({ "Motor_torque", 2.0f });
	//j.push_back({ "Motor_temp", 3.0f });
	//j.push_back({ "Inverter_output_frequency", 4.0f });
	//j.push_back({ "System_time", "job" });

	//j["SHIP_NUMBER"] = 7777;
	j["Motor"] = 1.0f;
	j["Motor_torque"] = 2.0f;
	j["Motor_temp"] = 3.0f;
	j["Inverter_output_frequency"] = 4.0f;
	j["System_time"] = "job";

	cout << j << endl;


	mainJson.set_data(j.dump());
	int size = mainJson.ByteSizeLong();
	cout << size << endl;
	//SessionRef session = service->CreateSession();


	while (true)
	{	
		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(mainJson);
		service->Broadcast(sendBuffer);
		//service->Broadcast(sendBuffer);
		this_thread::sleep_for(1s);
	}


	




	GThreadManager->Join();
}