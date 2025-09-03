#pragma once
#include "pch.h"
#include "ClientPacketHandler.h"
#include <vector>
#include <variant>
#include <regex>
#include "Protocol.pb.h"
#include "DBConnection.h"
#include "JsonPacketHandler.h"
#include "EDT0001_PacketHandler.h"
#include <chrono>
#include <iostream>
#include "DataSessionManager.h"
#include "MessageSubjectManager.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_PKT_TEST(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	

	EDT0001_PacketHandler pkt(buffer, len);

	pkt.Assign_JsonToPbALL(); 


	pkt.Insert_AllPbToDb();




	return false;
}

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

bool Handle_EDT0001(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	
	// Pasrsing the buffer and save the result in the protobuf<T>
	EDT0001_PacketHandler pkt(buffer, len);
	pkt.Assign_JsonToPbALL();
	pkt.Insert_AllPbToDb();

	// Send data to all which are connected with this server
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(pkt._battery);
	GSessionManager.Broadcast(sendBuffer);

	set<DataSessionRef> sessions = GSessionManager.GetAllSession();
	//for (const auto& session : sessions)
	//{

	//	for (const auto& sss : _pEventPublishers)
	//	{
	//		SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(pkt._battery);
	//	}

	//	session->Send(sendBuffer);
	//}



	return false;
}

bool Handle_MRSchema(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	return false;
}

bool Handle_Battery(PacketSessionRef& session, EDT0001::Battery& pkt)
{
	return false;
}

bool Handle_Battery_Pack(PacketSessionRef& session, EDT0001::Battery_Pack& pkt)
{
	return false;
}

bool Handle_BAT_MODULE_0(PacketSessionRef& session, EDT0001::BAT_MODULE_0& pkt)
{
	return false;
}

bool Handle_BAT_MODULE_1(PacketSessionRef& session, EDT0001::BAT_MODULE_1& pkt)
{
	return false;
}

bool Handle_BAT_MODULE_2(PacketSessionRef& session, EDT0001::BAT_MODULE_2& pkt)
{
	return false;
}

bool Handle_BAT_MODULE_3(PacketSessionRef& session, EDT0001::BAT_MODULE_3& pkt)
{
	return false;
}

bool Handle_Environment(PacketSessionRef& session, EDT0001::Environment& pkt)
{
	return false;
}

bool Handle_AIS(PacketSessionRef& session, EDT0001::AIS& pkt)
{
	return false;
}

bool Handle_System_Time(PacketSessionRef& session, EDT0001::System_Time& pkt)
{
	return false;
}

bool Handle_MOTOR(PacketSessionRef& session, EDT0001::MOTOR& pkt)
{
	return false;
}

bool Handle_INVERTER(PacketSessionRef& session, EDT0001::INVERTER& pkt)
{
	return false;
}

bool Handle_Network(PacketSessionRef& session, EDT0001::Network& pkt)
{
	return false;
}

bool Handle_SaveAsBytes(PacketSessionRef& session, EDT0001::SaveAsBytes& pkt)
{
	return false;
}

bool Handle_C_Position(PacketSessionRef& session, MRSchema::C_Position& pkt)
{
	//std::cout << "C_Position is incomming" << std::endl;
	
    	std::cout << "Log :" << pkt.id() <<":" << pkt.xpos() << std::endl;

	//SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(pkt);
	//GSessionManager.Broadcast(sendBuffer);

	return false;
}

bool Handle_XRCPUIMAGE(PacketSessionRef& session, MRSchema::XRCPUIMAGE& pkt)
{	
	std::cout << "XRCPUIMAGE is incomming" << std::endl;

	return true;
}

//std::mutex cout_mutex;

//bool Handle_EDT(PacketSessionRef& session, BYTE* buffer)
//{
//	
//	    // json µ¥ÀÌÅÍ Ã³¸® ÇÏµµ·Ï ÇÏ°Ú½À´Ï´Ù. 
//		std::string str = pkt.data();
//		nlohmann::json j = nlohmann::json::parse(str);
//		Protocol::S_MAIN mainJson;
//
//		if (j.is_discarded())
//		{
//			std::cerr << "JSON ÆÄÀÏ ÀÐ±â ½ÇÆÐ\n";
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
//			// json µ¥ÀÌÅÍ¸¦ º¯È¯ÇÏ±â À§ÇØ¼­ º¤ÅÍ¸¦ ¼±¾ð
//			//dbconnection¿¡¼­ µé°í ÀÖÀ» °Å¾ß
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
//			// °´Ã¼¿¡ ´ã±â
//			// µ¥ÀÌÅÍº£ÀÌ½º¿¡ º¸³»±â
//			// ´Ù¸¥ ¼¼¼Ç¿¡ º¸³»±â
//
//			int32 count = 0;
//			for (auto it = j.begin(); it !=j.end(); ++it)
//			{
//				// µ¿ÀÏÇÑ ÇÔ¼ö ¹Ýº¹ÇØ¼­ È£ÃâÇÏÁö ¸»°Í
//				// switch¹® ¾È¿¡ µ¿ÀÏÇÑ º¯¼ö »ç¿ë Áö¾ç
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



