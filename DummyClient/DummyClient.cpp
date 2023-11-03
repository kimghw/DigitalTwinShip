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
		//PacketSessionRef session = GetPacketSessionRef();

		//First, check what kind of packet is comming
		// and then, call the function that handles the packet
		//ServerPacketHandler::HandlePacket(session, buffer, len);


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
		NetAddress(L"127.0.0.1", 6340),
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
	j["01_INV_PHASE_A_CURRENT"] = 1;
	j["02_INV_PHASE_B_CURRENT"] = 1;
	j["03_INV_PHASE_C_CURRENT"] = 1;
	j["04_INV_POST_FAULT"] = 32.0f;
	j["05_INV_RUN_FAULT"] = 32.0f;
	j["06_INV_GATE_DRIVER_BOARD_TEMP"] = 1;
	j["07_INV_MODULE_A_TEMP"] = 1;
	j["08_INV_MODULE_B_TEMP"] = 1;
	j["09_INV_MODULE_C_TEMP"] = 1;
	j["10_INV_POWER"] = 1;
	j["11_INV_OUTPUT_VOLTAGE"] = 1;
	j["12_MT_RPM"] = 1;
	j["13_MT_TORQUE"] = 1;
	j["14_MT_TEMP"] = 1;
	j["15_Wind_speed"] = 1;
	j["16_Wind_direction"] = 1;
	j["17_latitude"] = "Hello";
	j["18_longtitude"] = "Hello";
	j["19_System-time"] = "Hello....very good";


	cout << j << endl;
	std::string json_string = j.dump();





	//mainJson.set_data(j.dump());
	//int size = mainJson.ByteSizeLong();
	//cout << size << endl;
    const char* ptrJson = json_string.c_str();
	cout << ptrJson << endl;

	while (true)
	{	
		//auto sendBuffer = ServerPacketHandler::MakeSendBuffer(mainJson);
		
		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(ptrJson);
		service->Broadcast(sendBuffer);
		this_thread::sleep_for(0.1s);


	}


	




	GThreadManager->Join();
}