#include "pch.h"
#include "ClientPacketHandler.h"
#include <vector>
#include <variant>
#include <regex>

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}


bool Handle_C_TEST(PacketSessionRef& session, Protocol::C_TEST& pkt)
{
	return true;
}

std::mutex cout_mutex;

bool Handle_C_MAIN(PacketSessionRef& session, Protocol::C_MAIN& pkt)
{
	
	    // json 데이터 처리 하도록 하겠습니다. 
		std::string str = pkt.data();
		nlohmann::json j = nlohmann::json::parse(str);
		if (j.is_discarded())
		{
			std::cerr << "JSON 파일 읽기 실패\n";
			return false;
		}

		// the number of the the pair of key -value
		int32 jsonSize = j.size();

	
		
		std::lock_guard<std::mutex> lock(cout_mutex);

		{

			int32 count = 0;
			
			//auto query = L"INSERT INTO [dbo].[ship_test] ([Motor], [Motor_torque], [Motor_temp], [Inverter_output_frequency], [System_time]) VALUES (?,?,?,?,?)";
			auto query = L"INSERT INTO [dbo].[ship_test_ver1]"
						L"("
						L"[01_INV_PHASE_A_CURRENT],"
						L"[02_INV_PHASE_B_CURRENT],"
						L"[03_INV_PHASE_C_CURRENT],"
						L"[04_INV_POST_FAULT],"
						L"[05_INV_RUN_FAULT],"
						L"[06_INV_GATE_DRIVER_BOARD_TEMP],"
						L"[07_INV_MODULE_A_TEMP],"
						L"[08_INV_MODULE_B_TEMP],"
						L"[09_INV_MODULE_C_TEMP],"
						L"[10_INV_POWER],"
						L"[11_INV_OUTPUT_VOLTAGE],"
						L"[12_MT_RPM],"
						L"[13_MT_TORQUE],"
						L"[14_MT_TEMP],"
						L"[15_Wind_speed],"
						L"[16_Wind_direction],"
						L"[17_latitude],"
						L"[18_longtitude],"
						L"[19_System-time]"
						L")"
						L" VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";



			DBConnection* dbConn = GDBConnectionPool->Pop();
			DBBind<19,0> dbBind(*dbConn, query);

			// json 데이터를 변환하기 위해서 벡터를 선언
			//dbconnection에서 들고 있을 거야
			struct KeyValuepair
			{
				nlohmann::json::value_t type = nlohmann::json::value_t::null;

				std::string keyValue = "";
				int32 int32_value = 0;
				int16 int16_value = 0;
				float fl_value = 0.f;
				std::string pValue = "";
				std::wstring wValue = L"";
				//TIMESTAMP_STRUCT* dataTime = nullptr;
			};
			std::vector<KeyValuepair> jsonVec(jsonSize);

			// 객체에 담기
			// 데이터베이스에 보내기
			// 다른 세션에 보내기

			
			for (auto it = j.begin(); it !=j.end(); ++it)
			{
				nlohmann::json::value_t jType = it.value().type();
				switch (jType)
					{
					case nlohmann::json::value_t::number_integer:
					{
						jsonVec[count].type = nlohmann::json::value_t::number_integer;
						jsonVec[count].int32_value = it.value().get<int32>();

						dbBind.BindParam(count, jsonVec[jsonVec.size() - 1].int32_value);
						count++;
						break;
					}
					case nlohmann::json::value_t::number_unsigned:
					{
						jsonVec[count].type = nlohmann::json::value_t::number_unsigned;
						jsonVec[count].int32_value = it.value().get<int32>();

						dbBind.BindParam(count, jsonVec[jsonVec.size() - 1].int32_value);
 						count++;
						break;
					}
					case nlohmann::json::value_t::number_float:
					{
						jsonVec[count].type = nlohmann::json::value_t::number_float;
						jsonVec[count].fl_value = static_cast<float>(it.value());

						dbBind.BindParam(count, jsonVec[count].fl_value);
						count++;
						break;
					}
					case nlohmann::json::value_t::string:
					{
						jsonVec[count].type = nlohmann::json::value_t::string;
						jsonVec[count].pValue = it.value().get<std::string>();
						const CHAR* str = jsonVec[count].pValue.c_str();

							jsonVec[count].wValue = JsonToConf::stringToWString(str);
							dbBind.BindParam(count, const_cast<WCHAR*>(jsonVec[count].wValue.c_str()));
							count++;
							break;
						
					}

				}

			};
 			ASSERT_CRASH(dbBind.Execute());
			GDBConnectionPool->Push(dbConn);

		}

	return true;
}

bool is_time(const std::string& str) {
	std::regex time_regex(R"(\d{2}:\d{2}:\d{2})");  // HH:mm:ss 형식의 정규 표현식
	return std::regex_match(str, time_regex);
}