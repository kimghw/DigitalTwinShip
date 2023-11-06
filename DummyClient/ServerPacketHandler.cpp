#include "pch.h"
#include "ServerPacketHandler.h"
#include <vector>
#include <variant>
#include <regex>
#include "Protocol.pb.h"
#include "DBConnection.h"
#include <nlohmann/json.hpp>

PacketHandlerFunc GPacketHandler[UINT16_MAX];
std::wstring stringToWString(const std::string& str);

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	return true;
}

bool Handle_C_TEST(PacketSessionRef& session, Protocol::C_TEST& pkt)
{
	return true;
}


bool Handle_S_TEST(PacketSessionRef& session, Protocol::S_TEST& pkt)
{
	//std::cout << pkt.id() << " : " << pkt.player() << std::endl;
	return true;
}

bool Handle_S_MAIN(PacketSessionRef& session, Protocol::S_MAIN& pkt)
{
	return true;
}

std::mutex cout_mutex;
bool Handle_C_MAIN(PacketSessionRef& session, Protocol::C_MAIN& pkt)
{
	
	    // json 데이터 처리 하도록 하겠습니다. 
		std::string str = pkt.data();
		nlohmann::json j = nlohmann::json::parse(str);
		Protocol::S_MAIN mainJson;

		if (j.is_discarded())
		{
			std::cerr << "JSON 파일 읽기 실패\n";
			return false;
		}

		// the number of the the pair of key -value
		int32 jsonSize = j.size();
	
		Protocol::S_MAIN S_pkt;
		
		S_pkt.set_inv_phase_a_current(j["01_INV_PHASE_A_CURRENT"].get<int32>());

		
		std::lock_guard<std::mutex> lock(cout_mutex);
		{
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

			int32 count = 0;
			for (auto it = j.begin(); it !=j.end(); ++it)
			{
				// 동일한 함수 반복해서 호출하지 말것
				// switch문 안에 동일한 변수 사용 지양
				nlohmann::json::value_t jType = it.value().type();
				switch (jType)
					{
					case nlohmann::json::value_t::number_integer:
					{
						jsonVec[count].type = nlohmann::json::value_t::number_integer;
						jsonVec[count].int32_value = it.value().get<int32>();

						dbBind.BindParam(count, jsonVec[count].int32_value);
						break;
					}
					case nlohmann::json::value_t::number_unsigned:
					{
						jsonVec[count].type = nlohmann::json::value_t::number_unsigned;
						jsonVec[count].int32_value = it.value().get<int32>();

						dbBind.BindParam(count, jsonVec[count].int32_value);
						break;
					}
					case nlohmann::json::value_t::number_float:
					{
						jsonVec[count].type = nlohmann::json::value_t::number_float;
						jsonVec[count].fl_value = static_cast<float>(it.value());

						dbBind.BindParam(count, jsonVec[count].fl_value);
						break;
					}
					case nlohmann::json::value_t::string:
					{
						jsonVec[count].type = nlohmann::json::value_t::string;
						jsonVec[count].pValue = it.value().get<std::string>();
						const CHAR* str = jsonVec[count].pValue.c_str();

						jsonVec[count].wValue = stringToWString(str);
						dbBind.BindParam(count, const_cast<WCHAR*>(jsonVec[count].wValue.c_str()));
						break;
					}

				}
				count++;

			};


 			ASSERT_CRASH(dbBind.Execute());
			GDBConnectionPool->Push(dbConn);

		}

	return true;
}


bool Handle_Json(PacketSessionRef& session, BYTE* buffer, int32 len)
{

	std::string str(buffer, buffer + len);


	// SCV , JSON ??
	str.insert(0, "[");
	str.append("]");
	replaceDegrees(OUT str);
	addBackslashBeforeQuotes(OUT str);

	nlohmann::json jsonInput = nlohmann::json::parse(str);
	if (jsonInput.is_discarded())
	{
		std::cerr << "JSON 파일 읽기 실패\n";
		return false;
	}

	std::cout << str << endl;

	// the number of the the pair of key -value
	int32 jsonSize = jsonInput.size();






	//std::lock_guard<std::mutex> lock(cout_mutex);
	{
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
		// ?? ?? ?????
		// ??, ????
		DBBind<19, 0> dbBind(*dbConn, query);

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


		int32 count = 0;
		// Change to the tree structure
		for (const auto& j : jsonInput)
		{
			for (auto it = j.begin(); it != j.end(); ++it)
			{

				nlohmann::json::value_t jType = it.value().type();
				switch (jType)
				{
				case nlohmann::json::value_t::number_integer:
				{
					jsonVec[count].type = nlohmann::json::value_t::number_integer;
					jsonVec[count].int32_value = it.value().get<int32>();

					dbBind.BindParam(count, jsonVec[count].int32_value);
					break;
				}
				case nlohmann::json::value_t::number_unsigned:
				{
					jsonVec[count].type = nlohmann::json::value_t::number_unsigned;
					jsonVec[count].int32_value = it.value().get<int32>();

					dbBind.BindParam(count, jsonVec[count].int32_value);
					break;
				}
				case nlohmann::json::value_t::number_float:
				{
					jsonVec[count].type = nlohmann::json::value_t::number_float;
					jsonVec[count].fl_value = static_cast<float>(it.value());

					dbBind.BindParam(count, jsonVec[count].fl_value);
					break;
				}
				case nlohmann::json::value_t::string:
				{
					jsonVec[count].type = nlohmann::json::value_t::string;
					jsonVec[count].pValue = it.value().get<std::string>();
					const CHAR* str = jsonVec[count].pValue.c_str();

					jsonVec[count].wValue = stringToWString(str);
					dbBind.BindParam(count, const_cast<WCHAR*>(jsonVec[count].wValue.c_str()));
					break;
				}

				}
				count++;

			};

		}



		ASSERT_CRASH(dbBind.Execute());
		GDBConnectionPool->Push(dbConn);

	}
	return true;
}


std::wstring stringToWString(const std::string& str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	if (len == 0) return L"";  // 변환 실패

	std::wstring ws(len - 1, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &ws[0], len);

	return ws;
}

void replaceDegrees(std::string& coord) {
	// Replace degree symbol with 'd'
	std::string degree_utf8 = "°"; // UTF-8 ???? ? ??
	size_t pos = coord.find(degree_utf8);
	while (pos != std::string::npos) {
		coord.replace(pos, degree_utf8.length(), "d");
		pos = coord.find(degree_utf8, pos + 1);
	}

	// Replace minute symbol (') with 'm'
	pos = coord.find("'");
	while (pos != std::string::npos) {
		coord.replace(pos, 1, "m");
		pos = coord.find("'", pos + 1);
	}

	// ??? ? ??(")? ???? ??? ?? ???? ????.
	// ????? ??? ???? ??? ?? ??? ? ????.
	// Replace second symbol (") with 's'
	//pos = coord.find("\"");
	//while (pos != std::string::npos) {
	//	coord.replace(pos, 1, "s");
	//	pos = coord.find("\"", pos + 1);
	//}
}
void addBackslashBeforeQuotes(OUT std::string& input) {
	std::string output;
	for (char c : input) {
		if (c == '"') {
			output += "\"";
		}
		else {
			output += c;
		}
	}
	input.swap(output); // ?? ??? ???? input? ?????.
}