#pragma once
#include "pch.h"
#include "JsonPacketHandler.h"


void MakeJsonString(std::string& str)
{
	// SCV , JSON 수정
	str.erase(std::remove(str.begin(), str.end(), '{'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '}'), str.end());
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	std::replace(str.begin(), str.end(), '-', '_');
	str.insert(0, "{");
	str.append("}");
	replaceDegrees(OUT str);
	addBackslashBeforeQuotes(OUT str);

}

bool StringToJson(std::string& str, nlohmann::json& jsonInput)
{
	jsonInput = nlohmann::json::parse(str);
	if (jsonInput.is_discarded())
	{
		std::cerr << "JSON ÆÄÀÏ ÀÐ±â ½ÇÆÐ\n";
		return false;
	}

	return true;
}

// 0. json 파일을 파싱한다.
// 1. json의 테이블 수 만큼 함수를 만듭니다.
// 1.1 함수 이름/ 컨벤션은 InsertJsonDataToAaa 이다.
// 2. Columns 객수 만큰 바인딩 함수를 생성한다.
// 3. MakeProtobuf

bool SendJsonToDb(nlohmann::json& jsonInput)
{
	//SP 방법 검토
	//동적 쿼리
	auto query = L"INSERT INTO [dbo].[ship_test_ver1]"
		L"("
		L"[INV_PHASE_A_CURRENT],"
		L"[INV_PHASE_B_CURRENT],"
		L"[INV_PHASE_C_CURRENT],"
		L"[INV_POST_FAULT],"
		L"[INV_RUN_FAULT],"
		L"[INV_GATE_DRIVER_BOARD_TEMP],"
		L"[INV_MODULE_A_TEMP],"
		L"[INV_MODULE_B_TEMP],"
		L"[INV_MODULE_C_TEMP],"
		L"[INV_POWER],"
		L"[INV_OUTPUT_VOLTAGE],"
		L"[MT_RPM],"
		L"[MT_TORQUE],"
		L"[MT_TEMP],"
		L"[Wind_speed],"
		L"[Wind_direction],"
		L"[latitude],"
		L"[longitude],"
		L"[System_time]"
		L")"
		L" VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

	

	DBConnection* dbConn = GDBConnectionPool->Pop();
	DBBind<19, 0> dbBind(*dbConn, query);
	int32 count = 0;

	int32 INV_PHASE_A_CURRENT = jsonInput["INV_PHASE_A_CURRENT"].get<int32>();
	dbBind.BindParam(count++, INV_PHASE_A_CURRENT);

	int32 INV_PHASE_B_CURRENT = jsonInput["INV_PHASE_B_CURRENT"].get<int32>();
	dbBind.BindParam(count++, INV_PHASE_B_CURRENT);

	int32 INV_PHASE_C_CURRENT = jsonInput["INV_PHASE_C_CURRENT"].get<int32>();
	dbBind.BindParam(count++, INV_PHASE_C_CURRENT);

	float INV_POST_FAULT = jsonInput["INV_POST_FAULT"].get<float>();
	dbBind.BindParam(count++, INV_POST_FAULT);

	float INV_RUN_FAULT = jsonInput["INV_RUN_FAULT"].get<float>();
	dbBind.BindParam(count++, INV_RUN_FAULT);

	int32 INV_GATE_DRIVER_BOARD_TEMP = jsonInput["INV_GATE_DRIVER_BOARD_TEMP"].get<int32>();
	dbBind.BindParam(count++, INV_GATE_DRIVER_BOARD_TEMP);

	int32 INV_MODULE_A_TEMP = jsonInput["INV_MODULE_A_TEMP"].get<int32>();
	dbBind.BindParam(count++, INV_MODULE_A_TEMP);

	int32 INV_MODULE_B_TEMP = jsonInput["INV_MODULE_B_TEMP"].get<int32>();
	dbBind.BindParam(count++, INV_MODULE_B_TEMP);

	int32 INV_MODULE_C_TEMP = jsonInput["INV_MODULE_C_TEMP"].get<int32>();
	dbBind.BindParam(count++, INV_MODULE_C_TEMP);

	int32 INV_POWER = jsonInput["INV_POWER"].get<int32>();
	dbBind.BindParam(count++, INV_POWER);

	int32 INV_OUTPUT_VOLTAGE = jsonInput["INV_OUTPUT_VOLTAGE"].get<int32>();
	dbBind.BindParam(count++, INV_OUTPUT_VOLTAGE);

	int32 MT_RPM = jsonInput["MT_RPM"].get<int32>();
	dbBind.BindParam(count++, MT_RPM);

	int32 MT_TORQUE = jsonInput["MT_TORQUE"].get<int32>();
	dbBind.BindParam(count++, MT_TORQUE);

	int32 MT_TEMP = jsonInput["MT_TEMP"].get<int32>();
	dbBind.BindParam(count++, MT_TEMP);

	int32 Wind_speed = jsonInput["Wind_speed"].get<int32>();
	dbBind.BindParam(count++, Wind_speed);

	int32 Wind_direction = jsonInput["Wind_direction"].get<int32>();
	dbBind.BindParam(count++, Wind_direction);

	string latitude = jsonInput["latitude"].get<string>();
	wstring wlatitude = stringToWString(latitude);
	const WCHAR* pwlatitude = const_cast<WCHAR*>(wlatitude.c_str());
	int32 wlatitude_size = wlatitude.length() * sizeof(WCHAR);
	dbBind.BindParam(count++, pwlatitude, wlatitude_size);

	
	string longtitude = jsonInput["longitude"].get<string>();
	wstring wlongtitude = stringToWString(longtitude);
	const WCHAR* pwlongtitude = const_cast<WCHAR*>(wlongtitude.c_str());
	int32 wlongtitude_size = wlongtitude.length()*sizeof(WCHAR);
	dbBind.BindParam(count++, pwlongtitude, wlongtitude_size);

	string System_time = jsonInput["System_time"].get<string>();
	wstring wSystem_time = stringToWString(System_time);
	const WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
	int32 wSystem_time_size = wSystem_time.length()*sizeof(WCHAR);
	dbBind.BindParam(count++, pwSystem_time, wSystem_time_size);

	ASSERT_CRASH(dbBind.Execute());
	GDBConnectionPool->Push(dbConn);

	std::wcout << wlongtitude << endl;
	return true;
}


void replaceDegrees(std::string& coord) 
{
	// Replace degree symbol with 'd'
	std::string degree_utf8 = "¡Æ"; // UTF-8 인코딩된 도 기호
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

	// 여기서 초 기호(")를 교체하는 코드가 주석 처리되어 있습니다.
	// 필요하다면 주석을 해제하고 아래와 같이 수정할 수 있습니다.
	// Replace second symbol (") with 's'
	//pos = coord.find("\"");
	//while (pos != std::string::npos) {
	//	coord.replace(pos, 1, "s");
	//	pos = coord.find("\"", pos + 1);
	//}
}
void addBackslashBeforeQuotes(OUT std::string& input) 
{
	std::string output;
	for (char c : input) {
		if (c == '"') {
			output += "\"";
		}
		else {
			output += c;
		}
	}
	input.swap(output); // 스왑 함수를 사용하여 input을 수정합니다.
}

std::wstring stringToWString(const std::string& str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	if (len == 0) return L"";  // º¯È¯ ½ÇÆÐ

	std::wstring ws(len - 1, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &ws[0], len);
	return ws;
}