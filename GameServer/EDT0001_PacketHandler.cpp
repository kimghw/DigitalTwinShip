#pragma once
#include "pch.h"
#include "JsonPacketHandler.h"
#include "EDT0001.pb.h"
#include "EDT0001_PacketHandler.h"
#include "Tools.h"
#include "MessageSubjectManager.h"

const int EDT0001_PacketHandler::DEFAULT_INT = 0;
const float EDT0001_PacketHandler::DEFAULT_FLOAT = 0.0f;
const double EDT0001_PacketHandler::DEFAULT_DOUBLE = 0.0;
const std::string EDT0001_PacketHandler::DEFAULT_STRING = "0";

EDT0001_PacketHandler::EDT0001_PacketHandler(BYTE* buffer, int32 len) : _str(buffer, buffer + len)
{
    SanitizeAndFormatAsJSON(_str);
 }

EDT0001_PacketHandler::~EDT0001_PacketHandler()
{
}

void EDT0001_PacketHandler::SanitizeAndFormatAsJSON(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), '{'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '}'), str.end());
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    std::replace(str.begin(), str.end(), '-', '_');
    str.insert(0, "{");
    str.append("}");
    replaceDegrees(OUT str);

    AssignBackslashBeforeQuotes(str);
    ParseJsonFromStr();
}

void EDT0001_PacketHandler::replaceDegrees(std::string& str)
{
    // Replace degree symbol with 'd'
    std::string degree_utf8 = "¡Æ";
    size_t pos = str.find(degree_utf8);
    while (pos != std::string::npos) {
        str.replace(pos, degree_utf8.length(), "d");
        pos = str.find(degree_utf8, pos + 1);
    }

    // Replace minute symbol (') with 'm'
    pos = str.find("'");
    while (pos != std::string::npos) {
        str.replace(pos, 1, "m");
        pos = str.find("'", pos + 1);
    }

    AssignBackslashBeforeQuotes(str);
}

void EDT0001_PacketHandler::AssignBackslashBeforeQuotes(OUT std::string& str)
{
    std::string output;
    for (char c : str) {
        if (c == '"') 
            output += "\"";
        else 
            output += c;
    }
    str.swap(output);
}

std::wstring EDT0001_PacketHandler::stringToWString(const std::string& str)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    if (len == 0) return L"";  // º¯È¯ ½ÇÆÐ

    std::wstring wstring(len - 1, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstring[0], len);
    return wstring;
}

bool EDT0001_PacketHandler::ParseJsonFromStr()
{

    try {
        _EdtJson = nlohmann::json::parse(_str);
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
    //string 삭제
    _str = "";
    //buffer 삭제
    return true;
}


template<typename T>
void EDT0001_PacketHandler::ValidateJson(const std::string& key, const T& defaultValue)
{
    try {
        _EdtJson.at(key).get<T>();
        //jsonInput["BAT_BPU_NEGATIVE_CONTACTOR"].get<int32>();
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key '" << key << "' is not found in JSON input:" << e.what() << '\n';
        _EdtJson[key] = defaultValue;
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type of '" << key << "' error in value:" << e.what() << '\n';
        _EdtJson[key] = defaultValue;
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error in '" << key << "' : " << e.what() << '\n';
        _EdtJson[key] = defaultValue;
    }
}

void EDT0001_PacketHandler::Assign_JsonToPbALL()
{ 
  Assign_JsonToPb_Battery(_battery);
  MessageSubjectManager::GetInstance().SetMessageUpdate(_battery, EDT::Battery);
  Assign_JsonToPb_Battery_Pack(_battery_pack);
  Assign_JsonToPb_BAT_MODULE_0(_bat_module_0);
  Assign_JsonToPb_BAT_MODULE_1(_bat_module_1);
  Assign_JsonToPb_BAT_MODULE_2(_bat_module_2);
  Assign_JsonToPb_BAT_MODULE_3(_bat_module_3);
  Assign_JsonToPb_Environment(_environment);
  Assign_JsonToPb_AIS(_ais);
  Assign_JsonToPb_System_Time(_system_time);
  Assign_JsonToPb_MOTOR(_motor);
  Assign_JsonToPb_INVERTER(_inverter);
  Assign_JsonToPb_Network(_network);
  Assign_JsonToPb_SaveAsBytes(_saveasbytes);
  }

//AssignJsonToPb//
void EDT0001_PacketHandler::Assign_JsonToPb_Battery(EDT0001::Battery& battery)
{
        
    ValidateJson<int32>("BAT_BPU_NEGATIVE_CONTACTOR", DEFAULT_INT);
    int32 value_BAT_BPU_NEGATIVE_CONTACTOR = _EdtJson.at("BAT_BPU_NEGATIVE_CONTACTOR");
    battery.set_bat_bpu_negative_contactor(value_BAT_BPU_NEGATIVE_CONTACTOR);
        
    ValidateJson<int32>("BAT_BPU_POSITIVE_CONTACTOR", DEFAULT_INT);
    int32 value_BAT_BPU_POSITIVE_CONTACTOR = _EdtJson.at("BAT_BPU_POSITIVE_CONTACTOR");
    battery.set_bat_bpu_positive_contactor(value_BAT_BPU_POSITIVE_CONTACTOR);
        
    ValidateJson<int32>("BAT_BPU_PRE_CONTACTOR", DEFAULT_INT);
    int32 value_BAT_BPU_PRE_CONTACTOR = _EdtJson.at("BAT_BPU_PRE_CONTACTOR");
    battery.set_bat_bpu_pre_contactor(value_BAT_BPU_PRE_CONTACTOR);
        
    ValidateJson<int32>("BAT_PROTECTION_A", DEFAULT_INT);
    int32 value_BAT_PROTECTION_A = _EdtJson.at("BAT_PROTECTION_A");
    battery.set_bat_protection_a(value_BAT_PROTECTION_A);
        
    ValidateJson<int32>("BAT_PROTECTION_B", DEFAULT_INT);
    int32 value_BAT_PROTECTION_B = _EdtJson.at("BAT_PROTECTION_B");
    battery.set_bat_protection_b(value_BAT_PROTECTION_B);
        
    ValidateJson<string>("System_time", DEFAULT_STRING);
    string value_System_time = _EdtJson.at("System_time");
    battery.set_system_time(value_System_time);
        
}

void EDT0001_PacketHandler::Assign_JsonToPb_Battery_Pack(EDT0001::Battery_Pack& battery_pack)
{
        
    ValidateJson<int32>("BAT_PACK_CURRENT", DEFAULT_INT);
    int32 value_BAT_PACK_CURRENT = _EdtJson.at("BAT_PACK_CURRENT");
    battery_pack.set_bat_pack_current(value_BAT_PACK_CURRENT);
        
    ValidateJson<int32>("BAT_PACK_SOC", DEFAULT_INT);
    int32 value_BAT_PACK_SOC = _EdtJson.at("BAT_PACK_SOC");
    battery_pack.set_bat_pack_soc(value_BAT_PACK_SOC);
        
    ValidateJson<int32>("BAT_PACK_VOLTAGE", DEFAULT_INT);
    int32 value_BAT_PACK_VOLTAGE = _EdtJson.at("BAT_PACK_VOLTAGE");
    battery_pack.set_bat_pack_voltage(value_BAT_PACK_VOLTAGE);
        
    ValidateJson<int32>("BAT_PACK_MAX_TEMP", DEFAULT_INT);
    int32 value_BAT_PACK_MAX_TEMP = _EdtJson.at("BAT_PACK_MAX_TEMP");
    battery_pack.set_bat_pack_max_temp(value_BAT_PACK_MAX_TEMP);
        
    ValidateJson<int32>("BAT_PACK_MAX_TEMP_SBMS_INDEX", DEFAULT_INT);
    int32 value_BAT_PACK_MAX_TEMP_SBMS_INDEX = _EdtJson.at("BAT_PACK_MAX_TEMP_SBMS_INDEX");
    battery_pack.set_bat_pack_max_temp_sbms_index(value_BAT_PACK_MAX_TEMP_SBMS_INDEX);
        
    ValidateJson<int32>("BAT_PACK_MIN_TEMP", DEFAULT_INT);
    int32 value_BAT_PACK_MIN_TEMP = _EdtJson.at("BAT_PACK_MIN_TEMP");
    battery_pack.set_bat_pack_min_temp(value_BAT_PACK_MIN_TEMP);
        
    ValidateJson<int32>("BAT_PACK_MIN_TEMP_SBMS_INDEX", DEFAULT_INT);
    int32 value_BAT_PACK_MIN_TEMP_SBMS_INDEX = _EdtJson.at("BAT_PACK_MIN_TEMP_SBMS_INDEX");
    battery_pack.set_bat_pack_min_temp_sbms_index(value_BAT_PACK_MIN_TEMP_SBMS_INDEX);
        
    ValidateJson<int32>("BAT_PACK_MAX_CELL_VOL", DEFAULT_INT);
    int32 value_BAT_PACK_MAX_CELL_VOL = _EdtJson.at("BAT_PACK_MAX_CELL_VOL");
    battery_pack.set_bat_pack_max_cell_vol(value_BAT_PACK_MAX_CELL_VOL);
        
    ValidateJson<int32>("BAT_PACK_MAX_CELL_VOL_SBMS_INDEX", DEFAULT_INT);
    int32 value_BAT_PACK_MAX_CELL_VOL_SBMS_INDEX = _EdtJson.at("BAT_PACK_MAX_CELL_VOL_SBMS_INDEX");
    battery_pack.set_bat_pack_max_cell_vol_sbms_index(value_BAT_PACK_MAX_CELL_VOL_SBMS_INDEX);
        
    ValidateJson<int32>("BAT_PACK_MIN_CELL_VOL", DEFAULT_INT);
    int32 value_BAT_PACK_MIN_CELL_VOL = _EdtJson.at("BAT_PACK_MIN_CELL_VOL");
    battery_pack.set_bat_pack_min_cell_vol(value_BAT_PACK_MIN_CELL_VOL);
        
    ValidateJson<int32>("BAT_PACK_MIN_CELL_VOL_SBMS_INDEX", DEFAULT_INT);
    int32 value_BAT_PACK_MIN_CELL_VOL_SBMS_INDEX = _EdtJson.at("BAT_PACK_MIN_CELL_VOL_SBMS_INDEX");
    battery_pack.set_bat_pack_min_cell_vol_sbms_index(value_BAT_PACK_MIN_CELL_VOL_SBMS_INDEX);
        
    ValidateJson<string>("System_time", DEFAULT_STRING);
    string value_System_time = _EdtJson.at("System_time");
    battery_pack.set_system_time(value_System_time);
        
}

void EDT0001_PacketHandler::Assign_JsonToPb_BAT_MODULE_0(EDT0001::BAT_MODULE_0& bat_module_0)
{
        
    ValidateJson<int32>("BAT_MODULE_CELL0_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE_CELL0_VOL = _EdtJson.at("BAT_MODULE_CELL0_VOL");
    bat_module_0.set_bat_module_cell0_vol(value_BAT_MODULE_CELL0_VOL);
        
    ValidateJson<int32>("BAT_MODULE_CELL1_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE_CELL1_VOL = _EdtJson.at("BAT_MODULE_CELL1_VOL");
    bat_module_0.set_bat_module_cell1_vol(value_BAT_MODULE_CELL1_VOL);
        
    ValidateJson<int32>("BAT_MODULE_CELL2_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE_CELL2_VOL = _EdtJson.at("BAT_MODULE_CELL2_VOL");
    bat_module_0.set_bat_module_cell2_vol(value_BAT_MODULE_CELL2_VOL);
        
    ValidateJson<int32>("BAT_MODULE_CELL3_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE_CELL3_VOL = _EdtJson.at("BAT_MODULE_CELL3_VOL");
    bat_module_0.set_bat_module_cell3_vol(value_BAT_MODULE_CELL3_VOL);
        
    ValidateJson<int32>("BAT_MODULE_CELL4_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE_CELL4_VOL = _EdtJson.at("BAT_MODULE_CELL4_VOL");
    bat_module_0.set_bat_module_cell4_vol(value_BAT_MODULE_CELL4_VOL);
        
    ValidateJson<int32>("BAT_MODULE_CELL5_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE_CELL5_VOL = _EdtJson.at("BAT_MODULE_CELL5_VOL");
    bat_module_0.set_bat_module_cell5_vol(value_BAT_MODULE_CELL5_VOL);
        
    ValidateJson<int32>("BAT_MODULE_CELL6_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE_CELL6_VOL = _EdtJson.at("BAT_MODULE_CELL6_VOL");
    bat_module_0.set_bat_module_cell6_vol(value_BAT_MODULE_CELL6_VOL);
        
    ValidateJson<int32>("BAT_MODULE_CELL7_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE_CELL7_VOL = _EdtJson.at("BAT_MODULE_CELL7_VOL");
    bat_module_0.set_bat_module_cell7_vol(value_BAT_MODULE_CELL7_VOL);
        
    ValidateJson<int32>("BAT_MODULE_CELL8_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE_CELL8_VOL = _EdtJson.at("BAT_MODULE_CELL8_VOL");
    bat_module_0.set_bat_module_cell8_vol(value_BAT_MODULE_CELL8_VOL);
        
    ValidateJson<int32>("BAT_MODULE_CELL9_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE_CELL9_VOL = _EdtJson.at("BAT_MODULE_CELL9_VOL");
    bat_module_0.set_bat_module_cell9_vol(value_BAT_MODULE_CELL9_VOL);
        
    ValidateJson<int32>("BAT_MODULE_CELL10_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE_CELL10_VOL = _EdtJson.at("BAT_MODULE_CELL10_VOL");
    bat_module_0.set_bat_module_cell10_vol(value_BAT_MODULE_CELL10_VOL);
        
    ValidateJson<int32>("BAT_MODULE_CELL11_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE_CELL11_VOL = _EdtJson.at("BAT_MODULE_CELL11_VOL");
    bat_module_0.set_bat_module_cell11_vol(value_BAT_MODULE_CELL11_VOL);
        
    ValidateJson<string>("System_time", DEFAULT_STRING);
    string value_System_time = _EdtJson.at("System_time");
    bat_module_0.set_system_time(value_System_time);
        
}

void EDT0001_PacketHandler::Assign_JsonToPb_BAT_MODULE_1(EDT0001::BAT_MODULE_1& bat_module_1)
{
        
    ValidateJson<int32>("BAT_MODULE1_CELL0_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE1_CELL0_VOL = _EdtJson.at("BAT_MODULE1_CELL0_VOL");
    bat_module_1.set_bat_module1_cell0_vol(value_BAT_MODULE1_CELL0_VOL);
        
    ValidateJson<int32>("BAT_MODULE1_CELL1_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE1_CELL1_VOL = _EdtJson.at("BAT_MODULE1_CELL1_VOL");
    bat_module_1.set_bat_module1_cell1_vol(value_BAT_MODULE1_CELL1_VOL);
        
    ValidateJson<int32>("BAT_MODULE1_CELL2_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE1_CELL2_VOL = _EdtJson.at("BAT_MODULE1_CELL2_VOL");
    bat_module_1.set_bat_module1_cell2_vol(value_BAT_MODULE1_CELL2_VOL);
        
    ValidateJson<int32>("BAT_MODULE1_CELL3_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE1_CELL3_VOL = _EdtJson.at("BAT_MODULE1_CELL3_VOL");
    bat_module_1.set_bat_module1_cell3_vol(value_BAT_MODULE1_CELL3_VOL);
        
    ValidateJson<int32>("BAT_MODULE1_CELL4_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE1_CELL4_VOL = _EdtJson.at("BAT_MODULE1_CELL4_VOL");
    bat_module_1.set_bat_module1_cell4_vol(value_BAT_MODULE1_CELL4_VOL);
        
    ValidateJson<int32>("BAT_MODULE1_CELL5_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE1_CELL5_VOL = _EdtJson.at("BAT_MODULE1_CELL5_VOL");
    bat_module_1.set_bat_module1_cell5_vol(value_BAT_MODULE1_CELL5_VOL);
        
    ValidateJson<int32>("BAT_MODULE1_CELL6_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE1_CELL6_VOL = _EdtJson.at("BAT_MODULE1_CELL6_VOL");
    bat_module_1.set_bat_module1_cell6_vol(value_BAT_MODULE1_CELL6_VOL);
        
    ValidateJson<int32>("BAT_MODULE1_CELL7_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE1_CELL7_VOL = _EdtJson.at("BAT_MODULE1_CELL7_VOL");
    bat_module_1.set_bat_module1_cell7_vol(value_BAT_MODULE1_CELL7_VOL);
        
    ValidateJson<int32>("BAT_MODULE1_CELL8_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE1_CELL8_VOL = _EdtJson.at("BAT_MODULE1_CELL8_VOL");
    bat_module_1.set_bat_module1_cell8_vol(value_BAT_MODULE1_CELL8_VOL);
        
    ValidateJson<int32>("BAT_MODULE1_CELL9_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE1_CELL9_VOL = _EdtJson.at("BAT_MODULE1_CELL9_VOL");
    bat_module_1.set_bat_module1_cell9_vol(value_BAT_MODULE1_CELL9_VOL);
        
    ValidateJson<int32>("BAT_MODULE1_CELL10_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE1_CELL10_VOL = _EdtJson.at("BAT_MODULE1_CELL10_VOL");
    bat_module_1.set_bat_module1_cell10_vol(value_BAT_MODULE1_CELL10_VOL);
        
    ValidateJson<int32>("BAT_MODULE1_CELL11_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE1_CELL11_VOL = _EdtJson.at("BAT_MODULE1_CELL11_VOL");
    bat_module_1.set_bat_module1_cell11_vol(value_BAT_MODULE1_CELL11_VOL);
        
    ValidateJson<string>("System_time", DEFAULT_STRING);
    string value_System_time = _EdtJson.at("System_time");
    bat_module_1.set_system_time(value_System_time);
        
}

void EDT0001_PacketHandler::Assign_JsonToPb_BAT_MODULE_2(EDT0001::BAT_MODULE_2& bat_module_2)
{
        
    ValidateJson<int32>("BAT_MODULE2_CELL0_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE2_CELL0_VOL = _EdtJson.at("BAT_MODULE2_CELL0_VOL");
    bat_module_2.set_bat_module2_cell0_vol(value_BAT_MODULE2_CELL0_VOL);
        
    ValidateJson<int32>("BAT_MODULE2_CELL1_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE2_CELL1_VOL = _EdtJson.at("BAT_MODULE2_CELL1_VOL");
    bat_module_2.set_bat_module2_cell1_vol(value_BAT_MODULE2_CELL1_VOL);
        
    ValidateJson<int32>("BAT_MODULE2_CELL2_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE2_CELL2_VOL = _EdtJson.at("BAT_MODULE2_CELL2_VOL");
    bat_module_2.set_bat_module2_cell2_vol(value_BAT_MODULE2_CELL2_VOL);
        
    ValidateJson<int32>("BAT_MODULE2_CELL3_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE2_CELL3_VOL = _EdtJson.at("BAT_MODULE2_CELL3_VOL");
    bat_module_2.set_bat_module2_cell3_vol(value_BAT_MODULE2_CELL3_VOL);
        
    ValidateJson<int32>("BAT_MODULE2_CELL4_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE2_CELL4_VOL = _EdtJson.at("BAT_MODULE2_CELL4_VOL");
    bat_module_2.set_bat_module2_cell4_vol(value_BAT_MODULE2_CELL4_VOL);
        
    ValidateJson<int32>("BAT_MODULE2_CELL5_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE2_CELL5_VOL = _EdtJson.at("BAT_MODULE2_CELL5_VOL");
    bat_module_2.set_bat_module2_cell5_vol(value_BAT_MODULE2_CELL5_VOL);
        
    ValidateJson<int32>("BAT_MODULE2_CELL6_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE2_CELL6_VOL = _EdtJson.at("BAT_MODULE2_CELL6_VOL");
    bat_module_2.set_bat_module2_cell6_vol(value_BAT_MODULE2_CELL6_VOL);
        
    ValidateJson<int32>("BAT_MODULE2_CELL7_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE2_CELL7_VOL = _EdtJson.at("BAT_MODULE2_CELL7_VOL");
    bat_module_2.set_bat_module2_cell7_vol(value_BAT_MODULE2_CELL7_VOL);
        
    ValidateJson<int32>("BAT_MODULE2_CELL8_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE2_CELL8_VOL = _EdtJson.at("BAT_MODULE2_CELL8_VOL");
    bat_module_2.set_bat_module2_cell8_vol(value_BAT_MODULE2_CELL8_VOL);
        
    ValidateJson<int32>("BAT_MODULE2_CELL9_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE2_CELL9_VOL = _EdtJson.at("BAT_MODULE2_CELL9_VOL");
    bat_module_2.set_bat_module2_cell9_vol(value_BAT_MODULE2_CELL9_VOL);
        
    ValidateJson<int32>("BAT_MODULE2_CELL10_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE2_CELL10_VOL = _EdtJson.at("BAT_MODULE2_CELL10_VOL");
    bat_module_2.set_bat_module2_cell10_vol(value_BAT_MODULE2_CELL10_VOL);
        
    ValidateJson<int32>("BAT_MODULE2_CELL11_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE2_CELL11_VOL = _EdtJson.at("BAT_MODULE2_CELL11_VOL");
    bat_module_2.set_bat_module2_cell11_vol(value_BAT_MODULE2_CELL11_VOL);
        
    ValidateJson<string>("System_time", DEFAULT_STRING);
    string value_System_time = _EdtJson.at("System_time");
    bat_module_2.set_system_time(value_System_time);
        
}

void EDT0001_PacketHandler::Assign_JsonToPb_BAT_MODULE_3(EDT0001::BAT_MODULE_3& bat_module_3)
{
        
    ValidateJson<int32>("BAT_MODULE3_CELL0_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE3_CELL0_VOL = _EdtJson.at("BAT_MODULE3_CELL0_VOL");
    bat_module_3.set_bat_module3_cell0_vol(value_BAT_MODULE3_CELL0_VOL);
        
    ValidateJson<int32>("BAT_MODULE3_CELL1_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE3_CELL1_VOL = _EdtJson.at("BAT_MODULE3_CELL1_VOL");
    bat_module_3.set_bat_module3_cell1_vol(value_BAT_MODULE3_CELL1_VOL);
        
    ValidateJson<int32>("BAT_MODULE3_CELL2_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE3_CELL2_VOL = _EdtJson.at("BAT_MODULE3_CELL2_VOL");
    bat_module_3.set_bat_module3_cell2_vol(value_BAT_MODULE3_CELL2_VOL);
        
    ValidateJson<int32>("BAT_MODULE3_CELL8_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE3_CELL8_VOL = _EdtJson.at("BAT_MODULE3_CELL8_VOL");
    bat_module_3.set_bat_module3_cell8_vol(value_BAT_MODULE3_CELL8_VOL);
        
    ValidateJson<int32>("BAT_MODULE3_CELL10_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE3_CELL10_VOL = _EdtJson.at("BAT_MODULE3_CELL10_VOL");
    bat_module_3.set_bat_module3_cell10_vol(value_BAT_MODULE3_CELL10_VOL);
        
    ValidateJson<int32>("BAT_MODULE3_CELL11_VOL", DEFAULT_INT);
    int32 value_BAT_MODULE3_CELL11_VOL = _EdtJson.at("BAT_MODULE3_CELL11_VOL");
    bat_module_3.set_bat_module3_cell11_vol(value_BAT_MODULE3_CELL11_VOL);
        
}

void EDT0001_PacketHandler::Assign_JsonToPb_Environment(EDT0001::Environment& environment)
{
        
    ValidateJson<int32>("Wind_speed", DEFAULT_INT);
    int32 value_Wind_speed = _EdtJson.at("Wind_speed");
    environment.set_wind_speed(value_Wind_speed);
        
    ValidateJson<int32>("Wind_direction", DEFAULT_INT);
    int32 value_Wind_direction = _EdtJson.at("Wind_direction");
    environment.set_wind_direction(value_Wind_direction);
        
    ValidateJson<string>("System_time", DEFAULT_STRING);
    string value_System_time = _EdtJson.at("System_time");
    environment.set_system_time(value_System_time);
        
}

void EDT0001_PacketHandler::Assign_JsonToPb_AIS(EDT0001::AIS& ais)
{
        
     ValidateJson<int32>("SHIPID", DEFAULT_INT);
    int32 value_SHIPID = _EdtJson.at("SHIPID");
    ais.set_shipid(value_SHIPID);
        
    ValidateJson<float>("latitude", DEFAULT_FLOAT);
    float value_latitude = _EdtJson.at("latitude");
    //float value_latitude = _EdtJson.at("latitude"));
    ais.set_latitude(value_latitude);
        
    ValidateJson<float>("longitude", DEFAULT_FLOAT);
    float value_longitude = _EdtJson.at("longitude");
    //float value_longitude = dmsStrToDd(_EdtJson.at("longitude"));
    ais.set_longitude(value_longitude);
        
    ValidateJson<string>("System_time", DEFAULT_STRING);
    string value_System_time = _EdtJson.at("System_time");
    ais.set_system_time(value_System_time);
        
}

void EDT0001_PacketHandler::Assign_JsonToPb_System_Time(EDT0001::System_Time& system_time)
{
        
    ValidateJson<string>("System_time", DEFAULT_STRING);
    string value_System_time = _EdtJson.at("System_time");
    system_time.set_system_time(value_System_time);
        
}

void EDT0001_PacketHandler::Assign_JsonToPb_MOTOR(EDT0001::MOTOR& motor)
{
        
    ValidateJson<int32>("MT_RPM", DEFAULT_INT);
    int32 value_MT_RPM = _EdtJson.at("MT_RPM");
    motor.set_mt_rpm(value_MT_RPM);
        
    ValidateJson<int32>("MT_TORQUE", DEFAULT_INT);
    int32 value_MT_TORQUE = _EdtJson.at("MT_TORQUE");
    motor.set_mt_torque(value_MT_TORQUE);
        
    ValidateJson<int32>("MT_TEMP", DEFAULT_INT);
    int32 value_MT_TEMP = _EdtJson.at("MT_TEMP");
    motor.set_mt_temp(value_MT_TEMP);
        
    ValidateJson<string>("System_time", DEFAULT_STRING);
    string value_System_time = _EdtJson.at("System_time");
    motor.set_system_time(value_System_time);
        
}

void EDT0001_PacketHandler::Assign_JsonToPb_INVERTER(EDT0001::INVERTER& inverter)
{
        
    ValidateJson<int32>("INV_PHASE_A_CURRENT", DEFAULT_INT);
    int32 value_INV_PHASE_A_CURRENT = _EdtJson.at("INV_PHASE_A_CURRENT");
    inverter.set_inv_phase_a_current(value_INV_PHASE_A_CURRENT);
        
    ValidateJson<int32>("INV_PHASE_B_CURRENT", DEFAULT_INT);
    int32 value_INV_PHASE_B_CURRENT = _EdtJson.at("INV_PHASE_B_CURRENT");
    inverter.set_inv_phase_b_current(value_INV_PHASE_B_CURRENT);
        
    ValidateJson<int32>("INV_PHASE_C_CURRENT", DEFAULT_INT);
    int32 value_INV_PHASE_C_CURRENT = _EdtJson.at("INV_PHASE_C_CURRENT");
    inverter.set_inv_phase_c_current(value_INV_PHASE_C_CURRENT);
        
    ValidateJson<int32>("INV_POST_FAULT", DEFAULT_INT);
    int32 value_INV_POST_FAULT = _EdtJson.at("INV_POST_FAULT");
    inverter.set_inv_post_fault(value_INV_POST_FAULT);
        
    ValidateJson<int32>("INV_GATE_DRIVER_BOARD_TEMP", DEFAULT_INT);
    int32 value_INV_GATE_DRIVER_BOARD_TEMP = _EdtJson.at("INV_GATE_DRIVER_BOARD_TEMP");
    inverter.set_inv_gate_driver_board_temp(value_INV_GATE_DRIVER_BOARD_TEMP);
        
    ValidateJson<int32>("INV_MODULE_A_TEMP", DEFAULT_INT);
    int32 value_INV_MODULE_A_TEMP = _EdtJson.at("INV_MODULE_A_TEMP");
    inverter.set_inv_module_a_temp(value_INV_MODULE_A_TEMP);
        
    ValidateJson<int32>("INV_RUN_FAULT", DEFAULT_INT);
    int32 value_INV_RUN_FAULT = _EdtJson.at("INV_RUN_FAULT");
    inverter.set_inv_run_fault(value_INV_RUN_FAULT);
        
    ValidateJson<int32>("INV_MODULE_B_TEMP", DEFAULT_INT);
    int32 value_INV_MODULE_B_TEMP = _EdtJson.at("INV_MODULE_B_TEMP");
    inverter.set_inv_module_b_temp(value_INV_MODULE_B_TEMP);
        
    ValidateJson<int32>("INV_MODULE_C_TEMP", DEFAULT_INT);
    int32 value_INV_MODULE_C_TEMP = _EdtJson.at("INV_MODULE_C_TEMP");
    inverter.set_inv_module_c_temp(value_INV_MODULE_C_TEMP);
        
    ValidateJson<int32>("INV_POWER", DEFAULT_INT);
    int32 value_INV_POWER = _EdtJson.at("INV_POWER");
    inverter.set_inv_power(value_INV_POWER);
        
    ValidateJson<int32>("INV_OUTPUT_VOLTAGE", DEFAULT_INT);
    int32 value_INV_OUTPUT_VOLTAGE = _EdtJson.at("INV_OUTPUT_VOLTAGE");
    inverter.set_inv_output_voltage(value_INV_OUTPUT_VOLTAGE);
        
    ValidateJson<string>("System_time", DEFAULT_STRING);
    string value_System_time = _EdtJson.at("System_time");
    inverter.set_system_time(value_System_time);
        
}

void EDT0001_PacketHandler::Assign_JsonToPb_Network(EDT0001::Network& network)
{
        
    ValidateJson<int32>("Status_Network", DEFAULT_INT);
    int32 value_Status_Network = _EdtJson.at("Status_Network");
    network.set_status_network(value_Status_Network);
        
    ValidateJson<string>("System_time", DEFAULT_STRING);
    string value_System_time = _EdtJson.at("System_time");
    network.set_system_time(value_System_time);
        
}

void EDT0001_PacketHandler::Assign_JsonToPb_SaveAsBytes(EDT0001::SaveAsBytes& saveasbytes)
{
        
    ValidateJson<int32>("Bytes", DEFAULT_INT);
    int32 value_Bytes = _EdtJson.at("Bytes");
    saveasbytes.set_bytes(value_Bytes);
        
    ValidateJson<string>("System_time", DEFAULT_STRING);
    string value_System_time = _EdtJson.at("System_time");
    saveasbytes.set_system_time(value_System_time);
        
}


EDT0001::Battery EDT0001_PacketHandler::get_Battery() {return _battery;}
EDT0001::Battery_Pack EDT0001_PacketHandler::get_Battery_Pack() {return _battery_pack;}
EDT0001::BAT_MODULE_0 EDT0001_PacketHandler::get_BAT_MODULE_0() {return _bat_module_0;}
EDT0001::BAT_MODULE_1 EDT0001_PacketHandler::get_BAT_MODULE_1() {return _bat_module_1;}
EDT0001::BAT_MODULE_2 EDT0001_PacketHandler::get_BAT_MODULE_2() {return _bat_module_2;}
EDT0001::BAT_MODULE_3 EDT0001_PacketHandler::get_BAT_MODULE_3() {return _bat_module_3;}
EDT0001::Environment EDT0001_PacketHandler::get_Environment() {return _environment;}
EDT0001::AIS EDT0001_PacketHandler::get_AIS() {return _ais;}
EDT0001::System_Time EDT0001_PacketHandler::get_System_Time() {return _system_time;}
EDT0001::MOTOR EDT0001_PacketHandler::get_MOTOR() {return _motor;}
EDT0001::INVERTER EDT0001_PacketHandler::get_INVERTER() {return _inverter;}
EDT0001::Network EDT0001_PacketHandler::get_Network() {return _network;}
EDT0001::SaveAsBytes EDT0001_PacketHandler::get_SaveAsBytes() {return _saveasbytes;}



//SendAllToDb//
void EDT0001_PacketHandler::Insert_AllPbToDb()
{
    Insert_Battery_ToDb(_battery);
    Insert_Battery_Pack_ToDb(_battery_pack);
    Insert_BAT_MODULE_0_ToDb(_bat_module_0);
    Insert_BAT_MODULE_1_ToDb(_bat_module_1);
    Insert_BAT_MODULE_2_ToDb(_bat_module_2);
    Insert_BAT_MODULE_3_ToDb(_bat_module_3);
    Insert_Environment_ToDb(_environment);
    Insert_AIS_ToDb(_ais);
    Insert_System_Time_ToDb(_system_time);
    Insert_MOTOR_ToDb(_motor);
    Insert_INVERTER_ToDb(_inverter);
    Insert_Network_ToDb(_network);
    Insert_SaveAsBytes_ToDb(_saveasbytes);
}


void EDT0001_PacketHandler::Insert_Battery_ToDb(EDT0001::Battery battery)
{
    auto query = L"INSERT INTO [dbo].[Battery]"
        L"("
        L"[BAT_BPU_NEGATIVE_CONTACTOR],"
        L"[BAT_BPU_POSITIVE_CONTACTOR],"
        L"[BAT_BPU_PRE_CONTACTOR],"
        L"[BAT_PROTECTION_A],"
        L"[BAT_PROTECTION_B],"
        L"[System_time]"
        L")"
        L"VALUES(?,?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <6,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 BAT_BPU_NEGATIVE_CONTACTOR = static_cast<int32>(battery.bat_bpu_negative_contactor());
    dbBind.BindParam(count++, BAT_BPU_NEGATIVE_CONTACTOR);
    
    int32 BAT_BPU_POSITIVE_CONTACTOR = static_cast<int32>(battery.bat_bpu_positive_contactor());
    dbBind.BindParam(count++, BAT_BPU_POSITIVE_CONTACTOR);
    
    int32 BAT_BPU_PRE_CONTACTOR = static_cast<int32>(battery.bat_bpu_pre_contactor());
    dbBind.BindParam(count++, BAT_BPU_PRE_CONTACTOR);
    
    int32 BAT_PROTECTION_A = static_cast<int32>(battery.bat_protection_a());
    dbBind.BindParam(count++, BAT_PROTECTION_A);
    
    int32 BAT_PROTECTION_B = static_cast<int32>(battery.bat_protection_b());
    dbBind.BindParam(count++, BAT_PROTECTION_B);
    
    std::string System_time = battery.system_time();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
void EDT0001_PacketHandler::Insert_Battery_Pack_ToDb(EDT0001::Battery_Pack battery_pack)
{
    auto query = L"INSERT INTO [dbo].[Battery_Pack]"
        L"("
        L"[BAT_PACK_CURRENT],"
        L"[BAT_PACK_SOC],"
        L"[BAT_PACK_VOLTAGE],"
        L"[BAT_PACK_MAX_TEMP],"
        L"[BAT_PACK_MAX_TEMP_SBMS_INDEX],"
        L"[BAT_PACK_MIN_TEMP],"
        L"[BAT_PACK_MIN_TEMP_SBMS_INDEX],"
        L"[BAT_PACK_MAX_CELL_VOL],"
        L"[BAT_PACK_MAX_CELL_VOL_SBMS_INDEX],"
        L"[BAT_PACK_MIN_CELL_VOL],"
        L"[BAT_PACK_MIN_CELL_VOL_SBMS_INDEX],"
        L"[System_time]"
        L")"
        L"VALUES(?,?,?,?,?,?,?,?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <12,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 BAT_PACK_CURRENT = static_cast<int32>(battery_pack.bat_pack_current());
    dbBind.BindParam(count++, BAT_PACK_CURRENT);
    
    int32 BAT_PACK_SOC = static_cast<int32>(battery_pack.bat_pack_soc());
    dbBind.BindParam(count++, BAT_PACK_SOC);
    
    int32 BAT_PACK_VOLTAGE = static_cast<int32>(battery_pack.bat_pack_voltage());
    dbBind.BindParam(count++, BAT_PACK_VOLTAGE);
    
    int32 BAT_PACK_MAX_TEMP = static_cast<int32>(battery_pack.bat_pack_max_temp());
    dbBind.BindParam(count++, BAT_PACK_MAX_TEMP);
    
    int32 BAT_PACK_MAX_TEMP_SBMS_INDEX = static_cast<int32>(battery_pack.bat_pack_max_temp_sbms_index());
    dbBind.BindParam(count++, BAT_PACK_MAX_TEMP_SBMS_INDEX);
    
    int32 BAT_PACK_MIN_TEMP = static_cast<int32>(battery_pack.bat_pack_min_temp());
    dbBind.BindParam(count++, BAT_PACK_MIN_TEMP);
    
    int32 BAT_PACK_MIN_TEMP_SBMS_INDEX = static_cast<int32>(battery_pack.bat_pack_min_temp_sbms_index());
    dbBind.BindParam(count++, BAT_PACK_MIN_TEMP_SBMS_INDEX);
    
    int32 BAT_PACK_MAX_CELL_VOL = static_cast<int32>(battery_pack.bat_pack_max_cell_vol());
    dbBind.BindParam(count++, BAT_PACK_MAX_CELL_VOL);
    
    int32 BAT_PACK_MAX_CELL_VOL_SBMS_INDEX = static_cast<int32>(battery_pack.bat_pack_max_cell_vol_sbms_index());
    dbBind.BindParam(count++, BAT_PACK_MAX_CELL_VOL_SBMS_INDEX);
    
    int32 BAT_PACK_MIN_CELL_VOL = static_cast<int32>(battery_pack.bat_pack_min_cell_vol());
    dbBind.BindParam(count++, BAT_PACK_MIN_CELL_VOL);
    
    int32 BAT_PACK_MIN_CELL_VOL_SBMS_INDEX = static_cast<int32>(battery_pack.bat_pack_min_cell_vol_sbms_index());
    dbBind.BindParam(count++, BAT_PACK_MIN_CELL_VOL_SBMS_INDEX);
    
    std::string System_time = battery_pack.system_time();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
void EDT0001_PacketHandler::Insert_BAT_MODULE_0_ToDb(EDT0001::BAT_MODULE_0 bat_module_0)
{
    auto query = L"INSERT INTO [dbo].[BAT_MODULE_0]"
        L"("
        L"[BAT_MODULE_CELL0_VOL],"
        L"[BAT_MODULE_CELL1_VOL],"
        L"[BAT_MODULE_CELL2_VOL],"
        L"[BAT_MODULE_CELL3_VOL],"
        L"[BAT_MODULE_CELL4_VOL],"
        L"[BAT_MODULE_CELL5_VOL],"
        L"[BAT_MODULE_CELL6_VOL],"
        L"[BAT_MODULE_CELL7_VOL],"
        L"[BAT_MODULE_CELL8_VOL],"
        L"[BAT_MODULE_CELL9_VOL],"
        L"[BAT_MODULE_CELL10_VOL],"
        L"[BAT_MODULE_CELL11_VOL],"
        L"[System_time]"
        L")"
        L"VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <13,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 BAT_MODULE_CELL0_VOL = static_cast<int32>(bat_module_0.bat_module_cell0_vol());
    dbBind.BindParam(count++, BAT_MODULE_CELL0_VOL);
    
    int32 BAT_MODULE_CELL1_VOL = static_cast<int32>(bat_module_0.bat_module_cell1_vol());
    dbBind.BindParam(count++, BAT_MODULE_CELL1_VOL);
    
    int32 BAT_MODULE_CELL2_VOL = static_cast<int32>(bat_module_0.bat_module_cell2_vol());
    dbBind.BindParam(count++, BAT_MODULE_CELL2_VOL);
    
    int32 BAT_MODULE_CELL3_VOL = static_cast<int32>(bat_module_0.bat_module_cell3_vol());
    dbBind.BindParam(count++, BAT_MODULE_CELL3_VOL);
    
    int32 BAT_MODULE_CELL4_VOL = static_cast<int32>(bat_module_0.bat_module_cell4_vol());
    dbBind.BindParam(count++, BAT_MODULE_CELL4_VOL);
    
    int32 BAT_MODULE_CELL5_VOL = static_cast<int32>(bat_module_0.bat_module_cell5_vol());
    dbBind.BindParam(count++, BAT_MODULE_CELL5_VOL);
    
    int32 BAT_MODULE_CELL6_VOL = static_cast<int32>(bat_module_0.bat_module_cell6_vol());
    dbBind.BindParam(count++, BAT_MODULE_CELL6_VOL);
    
    int32 BAT_MODULE_CELL7_VOL = static_cast<int32>(bat_module_0.bat_module_cell7_vol());
    dbBind.BindParam(count++, BAT_MODULE_CELL7_VOL);
    
    int32 BAT_MODULE_CELL8_VOL = static_cast<int32>(bat_module_0.bat_module_cell8_vol());
    dbBind.BindParam(count++, BAT_MODULE_CELL8_VOL);
    
    int32 BAT_MODULE_CELL9_VOL = static_cast<int32>(bat_module_0.bat_module_cell9_vol());
    dbBind.BindParam(count++, BAT_MODULE_CELL9_VOL);
    
    int32 BAT_MODULE_CELL10_VOL = static_cast<int32>(bat_module_0.bat_module_cell10_vol());
    dbBind.BindParam(count++, BAT_MODULE_CELL10_VOL);
    
    int32 BAT_MODULE_CELL11_VOL = static_cast<int32>(bat_module_0.bat_module_cell11_vol());
    dbBind.BindParam(count++, BAT_MODULE_CELL11_VOL);
    
    std::string System_time = bat_module_0.system_time();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
void EDT0001_PacketHandler::Insert_BAT_MODULE_1_ToDb(EDT0001::BAT_MODULE_1 bat_module_1)
{
    auto query = L"INSERT INTO [dbo].[BAT_MODULE_1]"
        L"("
        L"[BAT_MODULE1_CELL0_VOL],"
        L"[BAT_MODULE1_CELL1_VOL],"
        L"[BAT_MODULE1_CELL2_VOL],"
        L"[BAT_MODULE1_CELL3_VOL],"
        L"[BAT_MODULE1_CELL4_VOL],"
        L"[BAT_MODULE1_CELL5_VOL],"
        L"[BAT_MODULE1_CELL6_VOL],"
        L"[BAT_MODULE1_CELL7_VOL],"
        L"[BAT_MODULE1_CELL8_VOL],"
        L"[BAT_MODULE1_CELL9_VOL],"
        L"[BAT_MODULE1_CELL10_VOL],"
        L"[BAT_MODULE1_CELL11_VOL],"
        L"[System_time]"
        L")"
        L"VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <13,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 BAT_MODULE1_CELL0_VOL = static_cast<int32>(bat_module_1.bat_module1_cell0_vol());
    dbBind.BindParam(count++, BAT_MODULE1_CELL0_VOL);
    
    int32 BAT_MODULE1_CELL1_VOL = static_cast<int32>(bat_module_1.bat_module1_cell1_vol());
    dbBind.BindParam(count++, BAT_MODULE1_CELL1_VOL);
    
    int32 BAT_MODULE1_CELL2_VOL = static_cast<int32>(bat_module_1.bat_module1_cell2_vol());
    dbBind.BindParam(count++, BAT_MODULE1_CELL2_VOL);
    
    int32 BAT_MODULE1_CELL3_VOL = static_cast<int32>(bat_module_1.bat_module1_cell3_vol());
    dbBind.BindParam(count++, BAT_MODULE1_CELL3_VOL);
    
    int32 BAT_MODULE1_CELL4_VOL = static_cast<int32>(bat_module_1.bat_module1_cell4_vol());
    dbBind.BindParam(count++, BAT_MODULE1_CELL4_VOL);
    
    int32 BAT_MODULE1_CELL5_VOL = static_cast<int32>(bat_module_1.bat_module1_cell5_vol());
    dbBind.BindParam(count++, BAT_MODULE1_CELL5_VOL);
    
    int32 BAT_MODULE1_CELL6_VOL = static_cast<int32>(bat_module_1.bat_module1_cell6_vol());
    dbBind.BindParam(count++, BAT_MODULE1_CELL6_VOL);
    
    int32 BAT_MODULE1_CELL7_VOL = static_cast<int32>(bat_module_1.bat_module1_cell7_vol());
    dbBind.BindParam(count++, BAT_MODULE1_CELL7_VOL);
    
    int32 BAT_MODULE1_CELL8_VOL = static_cast<int32>(bat_module_1.bat_module1_cell8_vol());
    dbBind.BindParam(count++, BAT_MODULE1_CELL8_VOL);
    
    int32 BAT_MODULE1_CELL9_VOL = static_cast<int32>(bat_module_1.bat_module1_cell9_vol());
    dbBind.BindParam(count++, BAT_MODULE1_CELL9_VOL);
    
    int32 BAT_MODULE1_CELL10_VOL = static_cast<int32>(bat_module_1.bat_module1_cell10_vol());
    dbBind.BindParam(count++, BAT_MODULE1_CELL10_VOL);
    
    int32 BAT_MODULE1_CELL11_VOL = static_cast<int32>(bat_module_1.bat_module1_cell11_vol());
    dbBind.BindParam(count++, BAT_MODULE1_CELL11_VOL);
    
    std::string System_time = bat_module_1.system_time();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
void EDT0001_PacketHandler::Insert_BAT_MODULE_2_ToDb(EDT0001::BAT_MODULE_2 bat_module_2)
{
    auto query = L"INSERT INTO [dbo].[BAT_MODULE_2]"
        L"("
        L"[BAT_MODULE2_CELL0_VOL],"
        L"[BAT_MODULE2_CELL1_VOL],"
        L"[BAT_MODULE2_CELL2_VOL],"
        L"[BAT_MODULE2_CELL3_VOL],"
        L"[BAT_MODULE2_CELL4_VOL],"
        L"[BAT_MODULE2_CELL5_VOL],"
        L"[BAT_MODULE2_CELL6_VOL],"
        L"[BAT_MODULE2_CELL7_VOL],"
        L"[BAT_MODULE2_CELL8_VOL],"
        L"[BAT_MODULE2_CELL9_VOL],"
        L"[BAT_MODULE2_CELL10_VOL],"
        L"[BAT_MODULE2_CELL11_VOL],"
        L"[System_time]"
        L")"
        L"VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <13,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 BAT_MODULE2_CELL0_VOL = static_cast<int32>(bat_module_2.bat_module2_cell0_vol());
    dbBind.BindParam(count++, BAT_MODULE2_CELL0_VOL);
    
    int32 BAT_MODULE2_CELL1_VOL = static_cast<int32>(bat_module_2.bat_module2_cell1_vol());
    dbBind.BindParam(count++, BAT_MODULE2_CELL1_VOL);
    
    int32 BAT_MODULE2_CELL2_VOL = static_cast<int32>(bat_module_2.bat_module2_cell2_vol());
    dbBind.BindParam(count++, BAT_MODULE2_CELL2_VOL);
    
    int32 BAT_MODULE2_CELL3_VOL = static_cast<int32>(bat_module_2.bat_module2_cell3_vol());
    dbBind.BindParam(count++, BAT_MODULE2_CELL3_VOL);
    
    int32 BAT_MODULE2_CELL4_VOL = static_cast<int32>(bat_module_2.bat_module2_cell4_vol());
    dbBind.BindParam(count++, BAT_MODULE2_CELL4_VOL);
    
    int32 BAT_MODULE2_CELL5_VOL = static_cast<int32>(bat_module_2.bat_module2_cell5_vol());
    dbBind.BindParam(count++, BAT_MODULE2_CELL5_VOL);
    
    int32 BAT_MODULE2_CELL6_VOL = static_cast<int32>(bat_module_2.bat_module2_cell6_vol());
    dbBind.BindParam(count++, BAT_MODULE2_CELL6_VOL);
    
    int32 BAT_MODULE2_CELL7_VOL = static_cast<int32>(bat_module_2.bat_module2_cell7_vol());
    dbBind.BindParam(count++, BAT_MODULE2_CELL7_VOL);
    
    int32 BAT_MODULE2_CELL8_VOL = static_cast<int32>(bat_module_2.bat_module2_cell8_vol());
    dbBind.BindParam(count++, BAT_MODULE2_CELL8_VOL);
    
    int32 BAT_MODULE2_CELL9_VOL = static_cast<int32>(bat_module_2.bat_module2_cell9_vol());
    dbBind.BindParam(count++, BAT_MODULE2_CELL9_VOL);
    
    int32 BAT_MODULE2_CELL10_VOL = static_cast<int32>(bat_module_2.bat_module2_cell10_vol());
    dbBind.BindParam(count++, BAT_MODULE2_CELL10_VOL);
    
    int32 BAT_MODULE2_CELL11_VOL = static_cast<int32>(bat_module_2.bat_module2_cell11_vol());
    dbBind.BindParam(count++, BAT_MODULE2_CELL11_VOL);
    
    std::string System_time = bat_module_2.system_time();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
void EDT0001_PacketHandler::Insert_BAT_MODULE_3_ToDb(EDT0001::BAT_MODULE_3 bat_module_3)
{
    auto query = L"INSERT INTO [dbo].[BAT_MODULE_3]"
        L"("
        L"[BAT_MODULE3_CELL0_VOL],"
        L"[BAT_MODULE3_CELL1_VOL],"
        L"[BAT_MODULE3_CELL2_VOL],"
        L"[BAT_MODULE3_CELL8_VOL],"
        L"[BAT_MODULE3_CELL10_VOL],"
        L"[BAT_MODULE3_CELL11_VOL]"
        L")"
        L"VALUES(?,?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <6,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 BAT_MODULE3_CELL0_VOL = static_cast<int32>(bat_module_3.bat_module3_cell0_vol());
    dbBind.BindParam(count++, BAT_MODULE3_CELL0_VOL);
    
    int32 BAT_MODULE3_CELL1_VOL = static_cast<int32>(bat_module_3.bat_module3_cell1_vol());
    dbBind.BindParam(count++, BAT_MODULE3_CELL1_VOL);
    
    int32 BAT_MODULE3_CELL2_VOL = static_cast<int32>(bat_module_3.bat_module3_cell2_vol());
    dbBind.BindParam(count++, BAT_MODULE3_CELL2_VOL);
    
    int32 BAT_MODULE3_CELL8_VOL = static_cast<int32>(bat_module_3.bat_module3_cell8_vol());
    dbBind.BindParam(count++, BAT_MODULE3_CELL8_VOL);
    
    int32 BAT_MODULE3_CELL10_VOL = static_cast<int32>(bat_module_3.bat_module3_cell10_vol());
    dbBind.BindParam(count++, BAT_MODULE3_CELL10_VOL);
    
    int32 BAT_MODULE3_CELL11_VOL = static_cast<int32>(bat_module_3.bat_module3_cell11_vol());
    dbBind.BindParam(count++, BAT_MODULE3_CELL11_VOL);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
void EDT0001_PacketHandler::Insert_Environment_ToDb(EDT0001::Environment environment)
{
    auto query = L"INSERT INTO [dbo].[Environment]"
        L"("
        L"[Wind_speed],"
        L"[Wind_direction],"
        L"[System_time]"
        L")"
        L"VALUES(?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <3,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 Wind_speed = static_cast<int32>(environment.wind_speed());
    dbBind.BindParam(count++, Wind_speed);
    
    int32 Wind_direction = static_cast<int32>(environment.wind_direction());
    dbBind.BindParam(count++, Wind_direction);
    
    std::string System_time = environment.system_time();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
void EDT0001_PacketHandler::Insert_AIS_ToDb(EDT0001::AIS ais)
{
    auto query = L"INSERT INTO [dbo].[AIS]"
        L"("
        L"[SHIPID],"
        L"[latitude],"
        L"[longitude],"
        L"[System_time]"
        L")"
        L"VALUES(?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <4,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 SHIPID = static_cast<int32>(ais.shipid());
    dbBind.BindParam(count++, SHIPID);
    
   
    float latitude = static_cast<float>(ais.latitude());
    dbBind.BindParam(count++, latitude);
    
    float longitude = static_cast<float>(ais.longitude());
    dbBind.BindParam(count++, longitude);
    
    std::string System_time = ais.system_time();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
void EDT0001_PacketHandler::Insert_System_Time_ToDb(EDT0001::System_Time system_time)
{
    auto query = L"INSERT INTO [dbo].[System_Time]"
        L"("
        L"[System_time]"
        L")"
        L"VALUES(?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <1,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    std::string System_time = system_time.system_time();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
void EDT0001_PacketHandler::Insert_MOTOR_ToDb(EDT0001::MOTOR motor)
{
    auto query = L"INSERT INTO [dbo].[MOTOR]"
        L"("
        L"[MT_RPM],"
        L"[MT_TORQUE],"
        L"[MT_TEMP],"
        L"[System_time]"
        L")"
        L"VALUES(?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <4,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 MT_RPM = static_cast<int32>(motor.mt_rpm());
    dbBind.BindParam(count++, MT_RPM);
    
    int32 MT_TORQUE = static_cast<int32>(motor.mt_torque());
    dbBind.BindParam(count++, MT_TORQUE);
    
    int32 MT_TEMP = static_cast<int32>(motor.mt_temp());
    dbBind.BindParam(count++, MT_TEMP);
    
    std::string System_time = motor.system_time();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
void EDT0001_PacketHandler::Insert_INVERTER_ToDb(EDT0001::INVERTER inverter)
{
    auto query = L"INSERT INTO [dbo].[INVERTER]"
        L"("
        L"[INV_PHASE_A_CURRENT],"
        L"[INV_PHASE_B_CURRENT],"
        L"[INV_PHASE_C_CURRENT],"
        L"[INV_POST_FAULT],"
        L"[INV_GATE_DRIVER_BOARD_TEMP],"
        L"[INV_MODULE_A_TEMP],"
        L"[INV_RUN_FAULT],"
        L"[INV_MODULE_B_TEMP],"
        L"[INV_MODULE_C_TEMP],"
        L"[INV_POWER],"
        L"[INV_OUTPUT_VOLTAGE],"
        L"[System_time]"
        L")"
        L"VALUES(?,?,?,?,?,?,?,?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <12,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 INV_PHASE_A_CURRENT = static_cast<int32>(inverter.inv_phase_a_current());
    dbBind.BindParam(count++, INV_PHASE_A_CURRENT);
    
    int32 INV_PHASE_B_CURRENT = static_cast<int32>(inverter.inv_phase_b_current());
    dbBind.BindParam(count++, INV_PHASE_B_CURRENT);
    
    int32 INV_PHASE_C_CURRENT = static_cast<int32>(inverter.inv_phase_c_current());
    dbBind.BindParam(count++, INV_PHASE_C_CURRENT);
    
    int32 INV_POST_FAULT = static_cast<int32>(inverter.inv_post_fault());
    dbBind.BindParam(count++, INV_POST_FAULT);
    
    int32 INV_GATE_DRIVER_BOARD_TEMP = static_cast<int32>(inverter.inv_gate_driver_board_temp());
    dbBind.BindParam(count++, INV_GATE_DRIVER_BOARD_TEMP);
    
    int32 INV_MODULE_A_TEMP = static_cast<int32>(inverter.inv_module_a_temp());
    dbBind.BindParam(count++, INV_MODULE_A_TEMP);
    
    int32 INV_RUN_FAULT = static_cast<int32>(inverter.inv_run_fault());
    dbBind.BindParam(count++, INV_RUN_FAULT);
    
    int32 INV_MODULE_B_TEMP = static_cast<int32>(inverter.inv_module_b_temp());
    dbBind.BindParam(count++, INV_MODULE_B_TEMP);
    
    int32 INV_MODULE_C_TEMP = static_cast<int32>(inverter.inv_module_c_temp());
    dbBind.BindParam(count++, INV_MODULE_C_TEMP);
    
    int32 INV_POWER = static_cast<int32>(inverter.inv_power());
    dbBind.BindParam(count++, INV_POWER);
    
    int32 INV_OUTPUT_VOLTAGE = static_cast<int32>(inverter.inv_output_voltage());
    dbBind.BindParam(count++, INV_OUTPUT_VOLTAGE);
    
    std::string System_time = inverter.system_time();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
void EDT0001_PacketHandler::Insert_Network_ToDb(EDT0001::Network network)
{
    auto query = L"INSERT INTO [dbo].[Network]"
        L"("
        L"[Status_Network],"
        L"[System_time]"
        L")"
        L"VALUES(?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <2,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 Status_Network = static_cast<int32>(network.status_network());
    dbBind.BindParam(count++, Status_Network);
    
    std::string System_time = network.system_time();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
void EDT0001_PacketHandler::Insert_SaveAsBytes_ToDb(EDT0001::SaveAsBytes saveasbytes)
{
    auto query = L"INSERT INTO [dbo].[SaveAsBytes]"
        L"("
        L"[Bytes],"
        L"[System_time]"
        L")"
        L"VALUES(?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <2,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 Bytes = static_cast<int32>(saveasbytes.bytes());
    dbBind.BindParam(count++, Bytes);
    
    std::string System_time = saveasbytes.system_time();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}