#pragma once
#include "pch.h"
#include "ServerPacketHandler.h"
#include <vector>
#include <variant>
#include <regex>
#include "Protocol.pb.h"
#include "DBConnection.h"


PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

bool Handle_EDT0001(PacketSessionRef& session, BYTE* buffer, int32 len)
{

	//EDT0001_PacketHandler pkt(buffer, len);
	//pkt.AddJsonToPbALL();
	//pkt.SendAllToDb();

	return false;
}

//std::mutex cout_mutex;

//bool Handle_EDT(PacketSessionRef& session, BYTE* buffer)
//{
//	
//	    // json 데이터 처리 하도록 하겠습니다. 
//		std::string str = pkt.data();
//		nlohmann::json j = nlohmann::json::parse(str);
//		Protocol::S_MAIN mainJson;
//
//		if (j.is_discarded())
//		{
//			std::cerr << "JSON 파일 읽기 실패\n";
//			return false;
//		}
//
//		// the number of the the pair of key -value
//		int32 jsonSize = j.size();
//	
//		Protocol::S_MAIN S_pkt;
//		
//		S_pkt.set_inv_phase_a_current(j["01_INV_PHASE_A_CURRENT"].get<int32>());
//
//		
//		std::lock_guard<std::mutex> lock(cout_mutex);
//		{
//			//auto query = L"INSERT INTO [dbo].[ship_test] ([Motor], [Motor_torque], [Motor_temp], [Inverter_output_frequency], [System_time]) VALUES (?,?,?,?,?)";
//			auto query = L"INSERT INTO [dbo].[ship_test_ver1]"
//						L"("
//						L"[01_INV_PHASE_A_CURRENT],"
//						L"[02_INV_PHASE_B_CURRENT],"
//						L"[03_INV_PHASE_C_CURRENT],"
//						L"[04_INV_POST_FAULT],"
//						L"[05_INV_RUN_FAULT],"
//						L"[06_INV_GATE_DRIVER_BOARD_TEMP],"
//						L"[07_INV_MODULE_A_TEMP],"
//						L"[08_INV_MODULE_B_TEMP],"
//						L"[09_INV_MODULE_C_TEMP],"
//						L"[10_INV_POWER],"
//						L"[11_INV_OUTPUT_VOLTAGE],"
//						L"[12_MT_RPM],"
//						L"[13_MT_TORQUE],"
//						L"[14_MT_TEMP],"
//						L"[15_Wind_speed],"
//						L"[16_Wind_direction],"
//						L"[17_latitude],"
//						L"[18_longtitude],"
//						L"[19_System-time]"
//						L")"
//						L" VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
//
//			DBConnection* dbConn = GDBConnectionPool->Pop();
//			DBBind<19,0> dbBind(*dbConn, query);
//
//			// json 데이터를 변환하기 위해서 벡터를 선언
//			//dbconnection에서 들고 있을 거야
//			struct KeyValuepair
//			{
//				nlohmann::json::value_t type = nlohmann::json::value_t::null;
//
//				std::string keyValue = "";
//				int32 int32_value = 0;
//				int16 int16_value = 0;
//				float fl_value = 0.f;
//				std::string pValue = "";
//				std::wstring wValue = L"";
//				//TIMESTAMP_STRUCT* dataTime = nullptr;
//			};
//			std::vector<KeyValuepair> jsonVec(jsonSize);
//
//			// 객체에 담기
//			// 데이터베이스에 보내기
//			// 다른 세션에 보내기
//
//			int32 count = 0;
//			for (auto it = j.begin(); it !=j.end(); ++it)
//			{
//				// 동일한 함수 반복해서 호출하지 말것
//				// switch문 안에 동일한 변수 사용 지양
//				nlohmann::json::value_t jType = it.value().type();
//				switch (jType)
//					{
//					case nlohmann::json::value_t::number_integer:
//					{
//						jsonVec[count].type = nlohmann::json::value_t::number_integer;
//						jsonVec[count].int32_value = it.value().get<int32>();
//
//						dbBind.BindParam(count, jsonVec[count].int32_value);
//						break;
//					}
//					case nlohmann::json::value_t::number_unsigned:
//					{
//						jsonVec[count].type = nlohmann::json::value_t::number_unsigned;
//						jsonVec[count].int32_value = it.value().get<int32>();
//
//						dbBind.BindParam(count, jsonVec[count].int32_value);
//						break;
//					}
//					case nlohmann::json::value_t::number_float:
//					{
//						jsonVec[count].type = nlohmann::json::value_t::number_float;
//						jsonVec[count].fl_value = static_cast<float>(it.value());
//
//						dbBind.BindParam(count, jsonVec[count].fl_value);
//						break;
//					}
//					case nlohmann::json::value_t::string:
//					{
//						jsonVec[count].type = nlohmann::json::value_t::string;
//						jsonVec[count].pValue = it.value().get<std::string>();
//						const CHAR* str = jsonVec[count].pValue.c_str();
//
//						jsonVec[count].wValue = JsonToConf::stringToWString(str);
//						dbBind.BindParam(count, const_cast<WCHAR*>(jsonVec[count].wValue.c_str()));
//						break;
//					}
//
//				}
//				count++;
//
//			};
//
//
// 			ASSERT_CRASH(dbBind.Execute());
//			GDBConnectionPool->Push(dbConn);
//
//		}
//
//	return true;
//}




bool Handle_Battery(PacketSessionRef& session, Protocol::Battery& pkt)
{
	return false;
}

bool Handle_Battery_Pack(PacketSessionRef& session, Protocol::Battery_Pack& pkt)
{
	return false;
}

bool Handle_BAT_MODULE_0(PacketSessionRef& session, Protocol::BAT_MODULE_0& pkt)
{
	return false;
}

bool Handle_BAT_MODULE_1(PacketSessionRef& session, Protocol::BAT_MODULE_1& pkt)
{
	return false;
}

bool Handle_BAT_MODULE_2(PacketSessionRef& session, Protocol::BAT_MODULE_2& pkt)
{
	return false;
}

bool Handle_BAT_MODULE_3(PacketSessionRef& session, Protocol::BAT_MODULE_3& pkt)
{
	return false;
}

bool Handle_Environment(PacketSessionRef& session, Protocol::Environment& pkt)
{
	return false;
}

bool Handle_AIS(PacketSessionRef& session, Protocol::AIS& pkt)
{
	return false;
}

bool Handle_System_Time(PacketSessionRef& session, Protocol::System_Time& pkt)
{
	return false;
}

bool Handle_MOTOR(PacketSessionRef& session, Protocol::MOTOR& pkt)
{
	return false;
}

bool Handle_INVERTER(PacketSessionRef& session, Protocol::INVERTER& pkt)
{
	return false;
}

