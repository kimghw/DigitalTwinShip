#pragma once
#include "DBBind.h"
#include "pch.h"
#include "DBConnectionPool.h"
#include "Protocol.pb.h"

inline void replaceDegrees(std::string& coord);
inline void addBackslashBeforeQuotes(OUT std::string& input);
inline void MakeJsonString(std::string& str);
inline bool StringToJson(std::string& str, OUT nlohmann::json& jsonInput);
std::wstring stringToWString(const std::string& str);


void EDT0001_Battery_0001_ToDb(nlohmann::json& jsonInput);
void EDT0001_Battery_Pack_0002_ToDb(nlohmann::json& jsonInput);
void EDT0001_BAT_MODULE_0_0003_ToDb(nlohmann::json& jsonInput);
void EDT0001_BAT_MODULE_1_0004_ToDb(nlohmann::json& jsonInput);
void EDT0001_BAT_MODULE_2_0005_ToDb(nlohmann::json& jsonInput);
void EDT0001_BAT_MODULE_3_0006_ToDb(nlohmann::json& jsonInput);
void EDT0001_Environment_0007_ToDb(nlohmann::json& jsonInput);
void EDT0001_AIS_0008_ToDb(nlohmann::json& jsonInput);
void EDT0001_System_Time_0009_ToDb(nlohmann::json& jsonInput);
void EDT0001_MOTOR_0010_ToDb(nlohmann::json& jsonInput);
void EDT0001_INVERTER_0011_ToDb(nlohmann::json& jsonInput);

inline void MakeJsonString(std::string& str)
{
	// SCV , JSON 수정
	str.erase(std::remove(str.begin(), str.end(), '{'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '}'), str.end());
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	std::replace(str.begin(), str.end(), '-', '_');
	str.insert(0, "{");
	str.append("}");
	replaceDegrees(OUT str);
	//addBackslashBeforeQuotes(OUT str);
	//std::cout << str << endl;
}

inline bool StringToJson(std::string& str, nlohmann::json& jsonInput)
{

	try {
		jsonInput = nlohmann::json::parse(str);
		// JSON 파싱 후의 로직 처리
	}
	catch (const nlohmann::json::parse_error& e) {
		// JSON 파싱 예외 처리
		std::cerr << "JSON parsing error: " << e.what() << ", exception id: " << e.id << std::endl;
		return false;
	}
	catch (const nlohmann::json::type_error& e) {
		// 타입 관련 예외 처리
		std::cerr << "Type error: " << e.what() << ", exception id: " << e.id << std::endl;
		return false;
	}
	catch (const nlohmann::json::out_of_range& e) {
		// 범위를 벗어난 접근 예외 처리
		std::cerr << "Out of range error: " << e.what() << ", exception id: " << e.id << std::endl;
		return false;
	}
	catch (const nlohmann::json::other_error& e) {
		// 그 외의 모든 JSON 관련 예외 처리
		std::cerr << "Other error: " << e.what() << ", exception id: " << e.id << std::endl;
		return false;
	}
	catch (...) {
		// 기타 모든 예외 처리
		std::cerr << "An unknown error occurred" << std::endl;
		return false;
	}

	return true;
}
inline void replaceDegrees(std::string& coord)
{
	// Replace degree symbol with 'd'
	std::string degree_utf8 = "¡Æ";
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


}
inline void addBackslashBeforeQuotes(OUT std::string& input)
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
	input.swap(output);
}
inline std::wstring stringToWString(const std::string& str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	if (len == 0) return L"";  // º¯È¯ ½ÇÆÐ

	std::wstring ws(len - 1, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &ws[0], len);
	return ws;
}


class EDT0001_JsonHandler
{
public:
	EDT0001_JsonHandler(nlohmann::json inputjson); // 생성자
	~EDT0001_JsonHandler(); // 소멸자

private:
	nlohmann::json _EdtJson;
	Protocol::Battery _battery;
};

