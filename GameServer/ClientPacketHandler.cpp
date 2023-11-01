#include "pch.h"
#include "ClientPacketHandler.h"
#include <vector>
#include <variant>


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
			DBConnection* dbConn = GDBConnectionPool->Pop();
			//auto query = L"INSERT INTO [dbo].[ship_test] ([Motor], [Motor_torque], [Motor_temp], [Inverter_output_frequency], [System_time]) VALUES (?,?,?,?,?)";
			auto query = L"INSERT INTO [dbo].[ship_test] ([Inverter_output_frequency], [Motor], [Motor_torque], [Motor_temp],[System_time] ) VALUES (?,?,?,?,?)";
			DBBind<4,0> dbBind(*dbConn, query);

			// 데이터베이스로 보내기
			std::vector<KeyValuepair> jsonVec;
			jsonVec.resize(jsonSize);

			
			for (auto it = j.begin(); it !=j.end(); ++it)
			{
				nlohmann::json::value_t jType = it.value().type();
				switch (jType)
					{
					case nlohmann::json::value_t::number_integer:
					{
						jsonVec[count].type = nlohmann::json::value_t::number_integer;
						jsonVec[count].int_value = it.value().get<int32>();

						dbBind.BindParam(count, jsonVec[jsonVec.size() - 1].int_value);
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
						jsonVec[count].pvalue = it.value().get<std::string>();

						const CHAR* str = jsonVec[count].pvalue.c_str();
						jsonVec[count].pwvalue = JsonToConf::stringToWString(str);
						dbBind.BindParam(count, const_cast<WCHAR*>(jsonVec[jsonVec.size() - 1].pwvalue.c_str()));
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

