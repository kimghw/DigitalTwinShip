#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "BufferReader.h"
#include "ServerPacketHandler.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <random>
#include <sstream>
#include <chrono>
#include <iomanip>
#include "TestJson.h"

std::string current_time_to_string() {
	// 현재 시간을 std::chrono::system_clock으로부터 얻습니다.
	auto now = std::chrono::system_clock::now();
	time_t now_c = std::chrono::system_clock::to_time_t(now);

	// time_t를 tm 구조체로 변환합니다.
	tm now_tm;
	localtime_s(&now_tm, &now_c); // Windows에서는 localtime_s를 사용합니다. 
	// POSIX 시스템에서는 localtime_r을 사용하세요.

// stringstream을 사용하여 문자열로 포맷팅합니다.
	std::stringstream ss;
	ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
	return ss.str();
}

float dmsStrToDd(const std::string& dmsStr) {
	std::istringstream iss(dmsStr);
	float degrees, minutes, seconds;
	char direction;

	// 문자열을 공백을 기준으로 파싱
	if (!(iss >> degrees >> minutes >> seconds >> direction)) {
		throw std::invalid_argument("잘못된 형식의 문자열입니다.");
	}

	// 도분초를 십진수로 변환
	double dd = degrees + minutes / 60.0 + seconds / 3600.0;

	// 남쪽과 서쪽 방향의 경우 음수로 처리
	if (direction == 'S' || direction == 'W') {
		dd *= -1.0;
	}

	return dd;
}

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

// Azure : 20.200.230.157
// 내부 : 127.0.0.1
int main()
{
	ServerPacketHandler::Init();

	ClientServiceRef service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 6340),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager 등
		1);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 1; i++)
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

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	// 1부터 100 사이의 균일 분포를 가지는 난수 생성기

	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	// tm 구조체 초기화
	std::tm now_tm = {};

	localtime_s(&now_tm, &now_c);

	// stringstream을 사용하여 시간 포맷팅
	std::stringstream ss;
	ss << std::put_time(&now_tm, "%H%M%S");

	// 문자열로 변환
	std::string current_time_str = ss.str();

	cout << j << endl;
	std::string json_string = j.dump();


	string test_string = R"({"INV_POST_FAULT":0,"INV_RUN_FAULT":0,"INV_GATE_DRIVER_BOARD_TEMP":33,"INV_MODULE_A_TEMP":18,"INV_MODULE_B_TEMP":19,"INV_MODULE_C_TEMP":18,"INV_PHASE_A_CURRENT":0,"INV_PHASE_B_CURRENT":0,"INV_PHASE_C_CURRENT":0,"MT_TORQUE":0,"MT_RPM":0,"MT_TEMP":18,"Wind_speed":32,"Wind_direction":1832,"BAT_PACK_CURRENT":0,"INV_OUTPUT_VOLTAGE":351,"INV_POWER":0,"BAT_PACK_VOLTAGE":350,"BAT_PACK_MAX_CELL_VOL":3651,"BAT_PACK_MIN_CELL_VOL":3638,"BAT_MODULE_CELL0_VOL":3649,"BAT_MODULE_CELL1_VOL":3649,"BAT_MODULE_CELL2_VOL":3648,"BAT_MODULE_CELL3_VOL":3648,"BAT_MODULE_CELL4_VOL":3648,"BAT_MODULE_CELL5_VOL":3649,"BAT_MODULE_CELL6_VOL":3649,"BAT_MODULE_CELL7_VOL":3648,"BAT_MODULE_CELL8_VOL":3648,"BAT_MODULE_CELL9_VOL":3649,"BAT_MODULE_CELL10_VOL":3649,"BAT_MODULE_CELL11_VOL":3648,"BAT_MODULE1_CELL0_VOL":3650,"BAT_MODULE1_CELL1_VOL":3650,"BAT_MODULE1_CELL2_VOL":3649,"BAT_MODULE1_CELL3_VOL":3649,"BAT_MODULE1_CELL4_VOL":3649,"BAT_MODULE1_CELL5_VOL":3649,"BAT_MODULE1_CELL6_VOL":3649,"BAT_MODULE1_CELL7_VOL":3649,"BAT_MODULE1_CELL8_VOL":3649,"BAT_MODULE1_CELL9_VOL":3649,"BAT_MODULE1_CELL10_VOL":3648,"BAT_MODULE1_CELL11_VOL":3648,"BAT_MODULE2_CELL0_VOL":3649,"BAT_MODULE2_CELL1_VOL":3648,"BAT_MODULE2_CELL2_VOL":3648,"BAT_MODULE2_CELL3_VOL":3648,"BAT_MODULE2_CELL4_VOL":3648,"BAT_MODULE2_CELL5_VOL":3648,"BAT_MODULE2_CELL6_VOL":3648,"BAT_MODULE2_CELL7_VOL":3648,"BAT_MODULE2_CELL8_VOL":3648,"BAT_MODULE2_CELL9_VOL":3648,"BAT_MODULE2_CELL10_VOL":3648,"BAT_MODULE2_CELL11_VOL":3646,"BAT_MODULE3_CELL0_VOL":3649,"BAT_MODULE3_CELL1_VOL":3648,"BAT_MODULE3_CELL2_VOL":3648,"BAT_MODULE3_CELL3_VOL":3649,"BAT_MODULE3_CELL4_VOL":3648,"BAT_MODULE3_CELL5_VOL":3644,"BAT_MODULE3_CELL6_VOL":3649,"BAT_MODULE3_CELL7_VOL":3648,"BAT_MODULE3_CELL8_VOL":3648,"BAT_MODULE3_CELL9_VOL":3648,"BAT_MODULE3_CELL10_VOL":3649,"BAT_MODULE3_CELL11_VOL":3650,"BAT_BPU_NEGATIVE_CONTACTOR":1,"BAT_BPU_POSITIVE_CONTACTOR":1,"BAT_PROTECTION_A":0,"BAT_PROTECTION_B":0,"BAT_PACK_SOC":100,"BAT_PACK_MAX_TEMP_SBMS_INDEX":7,"BAT_PACK_MIN_TEMP_SBMS_INDEX":1,"BAT_PACK_MAX_CELL_VOL_SBMS_INDEX":5,"BAT_PACK_MIN_CELL_VOL_SBMS_INDEX":6,"BAT_PACK_MAX_TEMP":12,"BAT_PACK_MIN_TEMP":9,"latitude":"35d04m36.768sN","longitude":"129d05s16g110E","System_time":"10:25:53","Speed_over_ground_in_knots":0.100000})";
	nlohmann::json json_obj = nlohmann::json::parse(test_string);

	//mainJson.set_data(j.dump());
	//int size = mainJson.ByteSizeLong();
	//cout << size << endl;



	while (true)
	{	
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 100); // 예시로 0에서 100 사이의 정수
		std::pair<string, string> randomCoordinates = TestJson::generateRandomCoordinates();




		for (auto& element : json_obj.items()) {
			// 랜덤 값 생성
			int random_value = dis(gen);


			if (element.key() == "System_time")
			{
				element.value() = current_time_to_string();
			}
			else if (element.key() == "latitude")
			{
				element.value() = dmsStrToDd(randomCoordinates.first);
				//element.value() = randomCoordinates.first;
			}
			else if (element.key() == "longitude")
			{
				element.value() = dmsStrToDd(randomCoordinates.second);
				//element.value() = randomCoordinates.second;
			}
			else
			{
			// 랜덤 값으로 업데이트
			element.value() = random_value;

			}
		}
		std::string updated_string = json_obj.dump();
		std::cout << "Updated JSON: " << updated_string << std::endl;

		//auto sendBuffer = ServerPacketHandler::MakeSendBuffer(mainJson);
		
		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(updated_string.c_str());
		service->Broadcast(sendBuffer);
		this_thread::sleep_for(1s);
	}


	




	GThreadManager->Join();
}