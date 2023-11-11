#pragma once
#include "pch.h"
#include "JsonPacketHandler.h"
#include "Protocol.pb.h"
#include "EDT0001_PacketHandler.h"

void JsonToProtobuf_Battery(nlohmann::json& jsonInput, OUT Protocol::Battery PKT)
{
    ValidateAndAssgine_BAT_BPU_NEGATIVE_CONTACTOR(jsonInput, PKT);

}

void ValidateAndAssgine_BAT_BPU_NEGATIVE_CONTACTOR(nlohmann::json& jsonInput, Protocol::Battery& PKT)
{
    int32 BAT_BPU_NEGATIVE_CONTACTOR = 0;
    try {
        PKT.set_bat_bpu_negative_contactor( jsonInput["BAT_BPU_NEGATIVE_CONTACTOR"].get<int32>() );
        //jsonInput["BAT_BPU_NEGATIVE_CONTACTOR"].get<int32>();
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_BPU_NEGATIVE_CONTACTOR' not found in JSON input:" << e.what() << '\n';
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'BAT_BPU_NEGATIVE_CONTACTOR' value:" << e.what() << '\n';
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
    }
}





void EDT0001_Battery_0001_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[]"
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

    
    // 01/06. BAT_BPU_NEGATIVE_CONTACTOR to Database
    //     Table name : Battery, Column name : BAT_BPU_NEGATIVE_CONTACTOR, Type : INT
    int32 BAT_BPU_NEGATIVE_CONTACTOR = 0;
    try {
        BAT_BPU_NEGATIVE_CONTACTOR = jsonInput["BAT_BPU_NEGATIVE_CONTACTOR"].get<int32>();
        dbBind.BindParam(count++,BAT_BPU_NEGATIVE_CONTACTOR);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_BPU_NEGATIVE_CONTACTOR' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_BPU_NEGATIVE_CONTACTOR);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_BPU_NEGATIVE_CONTACTOR' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_BPU_NEGATIVE_CONTACTOR);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_BPU_NEGATIVE_CONTACTOR);
    }
    // 02/06. BAT_BPU_POSITIVE_CONTACTOR to Database
    //     Table name : Battery, Column name : BAT_BPU_POSITIVE_CONTACTOR, Type : INT
    int32 BAT_BPU_POSITIVE_CONTACTOR = 0;
    try {
        BAT_BPU_POSITIVE_CONTACTOR = jsonInput["BAT_BPU_POSITIVE_CONTACTOR"].get<int32>();
        dbBind.BindParam(count++,BAT_BPU_POSITIVE_CONTACTOR);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_BPU_POSITIVE_CONTACTOR' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_BPU_POSITIVE_CONTACTOR);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_BPU_POSITIVE_CONTACTOR' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_BPU_POSITIVE_CONTACTOR);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_BPU_POSITIVE_CONTACTOR);
    }
    // 03/06. BAT_BPU_PRE_CONTACTOR to Database
    //     Table name : Battery, Column name : BAT_BPU_PRE_CONTACTOR, Type : INT
    int32 BAT_BPU_PRE_CONTACTOR = 0;
    try {
        BAT_BPU_PRE_CONTACTOR = jsonInput["BAT_BPU_PRE_CONTACTOR"].get<int32>();
        dbBind.BindParam(count++,BAT_BPU_PRE_CONTACTOR);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_BPU_PRE_CONTACTOR' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_BPU_PRE_CONTACTOR);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_BPU_PRE_CONTACTOR' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_BPU_PRE_CONTACTOR);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_BPU_PRE_CONTACTOR);
    }
    // 04/06. BAT_PROTECTION_A to Database
    //     Table name : Battery, Column name : BAT_PROTECTION_A, Type : INT
    int32 BAT_PROTECTION_A = 0;
    try {
        BAT_PROTECTION_A = jsonInput["BAT_PROTECTION_A"].get<int32>();
        dbBind.BindParam(count++,BAT_PROTECTION_A);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PROTECTION_A' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PROTECTION_A);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PROTECTION_A' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PROTECTION_A);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PROTECTION_A);
    }
    // 05/06. BAT_PROTECTION_B to Database
    //     Table name : Battery, Column name : BAT_PROTECTION_B, Type : INT
    int32 BAT_PROTECTION_B = 0;
    try {
        BAT_PROTECTION_B = jsonInput["BAT_PROTECTION_B"].get<int32>();
        dbBind.BindParam(count++,BAT_PROTECTION_B);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PROTECTION_B' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PROTECTION_B);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PROTECTION_B' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PROTECTION_B);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PROTECTION_B);
    }
    // 06/06. System_time to Database
    //     Table name : Battery, Column name : System_time, Type : NVARCHAR
    std::wstring wSystem_time = L"No input";
    WCHAR* pwSystem_time = nullptr;
    try {
        std::string System_time = jsonInput["System_time"].get<std::string>();
        wSystem_time = stringToWString(System_time);
        pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'System_time' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'System_time' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}

void EDT0001_Battery_Pack_0002_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[]"
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

    
    // 01/12. BAT_PACK_CURRENT to Database
    //     Table name : Battery_Pack, Column name : BAT_PACK_CURRENT, Type : INT
    int32 BAT_PACK_CURRENT = 0;
    try {
        BAT_PACK_CURRENT = jsonInput["BAT_PACK_CURRENT"].get<int32>();
        dbBind.BindParam(count++,BAT_PACK_CURRENT);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PACK_CURRENT' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_CURRENT);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PACK_CURRENT' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_CURRENT);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_CURRENT);
    }
    // 02/12. BAT_PACK_SOC to Database
    //     Table name : Battery_Pack, Column name : BAT_PACK_SOC, Type : INT
    int32 BAT_PACK_SOC = 0;
    try {
        BAT_PACK_SOC = jsonInput["BAT_PACK_SOC"].get<int32>();
        dbBind.BindParam(count++,BAT_PACK_SOC);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PACK_SOC' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_SOC);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PACK_SOC' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_SOC);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_SOC);
    }
    // 03/12. BAT_PACK_VOLTAGE to Database
    //     Table name : Battery_Pack, Column name : BAT_PACK_VOLTAGE, Type : INT
    int32 BAT_PACK_VOLTAGE = 0;
    try {
        BAT_PACK_VOLTAGE = jsonInput["BAT_PACK_VOLTAGE"].get<int32>();
        dbBind.BindParam(count++,BAT_PACK_VOLTAGE);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PACK_VOLTAGE' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_VOLTAGE);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PACK_VOLTAGE' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_VOLTAGE);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_VOLTAGE);
    }
    // 04/12. BAT_PACK_MAX_TEMP to Database
    //     Table name : Battery_Pack, Column name : BAT_PACK_MAX_TEMP, Type : INT
    int32 BAT_PACK_MAX_TEMP = 0;
    try {
        BAT_PACK_MAX_TEMP = jsonInput["BAT_PACK_MAX_TEMP"].get<int32>();
        dbBind.BindParam(count++,BAT_PACK_MAX_TEMP);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PACK_MAX_TEMP' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MAX_TEMP);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PACK_MAX_TEMP' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MAX_TEMP);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MAX_TEMP);
    }
    // 05/12. BAT_PACK_MAX_TEMP_SBMS_INDEX to Database
    //     Table name : Battery_Pack, Column name : BAT_PACK_MAX_TEMP_SBMS_INDEX, Type : INT
    int32 BAT_PACK_MAX_TEMP_SBMS_INDEX = 0;
    try {
        BAT_PACK_MAX_TEMP_SBMS_INDEX = jsonInput["BAT_PACK_MAX_TEMP_SBMS_INDEX"].get<int32>();
        dbBind.BindParam(count++,BAT_PACK_MAX_TEMP_SBMS_INDEX);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PACK_MAX_TEMP_SBMS_INDEX' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MAX_TEMP_SBMS_INDEX);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PACK_MAX_TEMP_SBMS_INDEX' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MAX_TEMP_SBMS_INDEX);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MAX_TEMP_SBMS_INDEX);
    }
    // 06/12. BAT_PACK_MIN_TEMP to Database
    //     Table name : Battery_Pack, Column name : BAT_PACK_MIN_TEMP, Type : INT
    int32 BAT_PACK_MIN_TEMP = 0;
    try {
        BAT_PACK_MIN_TEMP = jsonInput["BAT_PACK_MIN_TEMP"].get<int32>();
        dbBind.BindParam(count++,BAT_PACK_MIN_TEMP);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PACK_MIN_TEMP' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MIN_TEMP);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PACK_MIN_TEMP' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MIN_TEMP);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MIN_TEMP);
    }
    // 07/12. BAT_PACK_MIN_TEMP_SBMS_INDEX to Database
    //     Table name : Battery_Pack, Column name : BAT_PACK_MIN_TEMP_SBMS_INDEX, Type : INT
    int32 BAT_PACK_MIN_TEMP_SBMS_INDEX = 0;
    try {
        BAT_PACK_MIN_TEMP_SBMS_INDEX = jsonInput["BAT_PACK_MIN_TEMP_SBMS_INDEX"].get<int32>();
        dbBind.BindParam(count++,BAT_PACK_MIN_TEMP_SBMS_INDEX);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PACK_MIN_TEMP_SBMS_INDEX' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MIN_TEMP_SBMS_INDEX);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PACK_MIN_TEMP_SBMS_INDEX' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MIN_TEMP_SBMS_INDEX);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MIN_TEMP_SBMS_INDEX);
    }
    // 08/12. BAT_PACK_MAX_CELL_VOL to Database
    //     Table name : Battery_Pack, Column name : BAT_PACK_MAX_CELL_VOL, Type : INT
    int32 BAT_PACK_MAX_CELL_VOL = 0;
    try {
        BAT_PACK_MAX_CELL_VOL = jsonInput["BAT_PACK_MAX_CELL_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_PACK_MAX_CELL_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PACK_MAX_CELL_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MAX_CELL_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PACK_MAX_CELL_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MAX_CELL_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MAX_CELL_VOL);
    }
    // 09/12. BAT_PACK_MAX_CELL_VOL_SBMS_INDEX to Database
    //     Table name : Battery_Pack, Column name : BAT_PACK_MAX_CELL_VOL_SBMS_INDEX, Type : INT
    int32 BAT_PACK_MAX_CELL_VOL_SBMS_INDEX = 0;
    try {
        BAT_PACK_MAX_CELL_VOL_SBMS_INDEX = jsonInput["BAT_PACK_MAX_CELL_VOL_SBMS_INDEX"].get<int32>();
        dbBind.BindParam(count++,BAT_PACK_MAX_CELL_VOL_SBMS_INDEX);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PACK_MAX_CELL_VOL_SBMS_INDEX' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MAX_CELL_VOL_SBMS_INDEX);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PACK_MAX_CELL_VOL_SBMS_INDEX' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MAX_CELL_VOL_SBMS_INDEX);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MAX_CELL_VOL_SBMS_INDEX);
    }
    // 10/12. BAT_PACK_MIN_CELL_VOL to Database
    //     Table name : Battery_Pack, Column name : BAT_PACK_MIN_CELL_VOL, Type : INT
    int32 BAT_PACK_MIN_CELL_VOL = 0;
    try {
        BAT_PACK_MIN_CELL_VOL = jsonInput["BAT_PACK_MIN_CELL_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_PACK_MIN_CELL_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PACK_MIN_CELL_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MIN_CELL_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PACK_MIN_CELL_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MIN_CELL_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MIN_CELL_VOL);
    }
    // 11/12. BAT_PACK_MIN_CELL_VOL_SBMS_INDEX to Database
    //     Table name : Battery_Pack, Column name : BAT_PACK_MIN_CELL_VOL_SBMS_INDEX, Type : INT
    int32 BAT_PACK_MIN_CELL_VOL_SBMS_INDEX = 0;
    try {
        BAT_PACK_MIN_CELL_VOL_SBMS_INDEX = jsonInput["BAT_PACK_MIN_CELL_VOL_SBMS_INDEX"].get<int32>();
        dbBind.BindParam(count++,BAT_PACK_MIN_CELL_VOL_SBMS_INDEX);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_PACK_MIN_CELL_VOL_SBMS_INDEX' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MIN_CELL_VOL_SBMS_INDEX);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_PACK_MIN_CELL_VOL_SBMS_INDEX' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MIN_CELL_VOL_SBMS_INDEX);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_PACK_MIN_CELL_VOL_SBMS_INDEX);
    }
    // 12/12. System_time to Database
    //     Table name : Battery_Pack, Column name : System_time, Type : NVARCHAR
    std::wstring wSystem_time = L"No input";
    WCHAR* pwSystem_time = nullptr;
    try {
        std::string System_time = jsonInput["System_time"].get<std::string>();
        wSystem_time = stringToWString(System_time);
        pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'System_time' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'System_time' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}

void EDT0001_BAT_MODULE_0_0003_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[]"
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

    
    // 01/13. BAT_MODULE_CELL0_VOL to Database
    //     Table name : BAT_MODULE_0, Column name : BAT_MODULE_CELL0_VOL, Type : INT
    int32 BAT_MODULE_CELL0_VOL = 0;
    try {
        BAT_MODULE_CELL0_VOL = jsonInput["BAT_MODULE_CELL0_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE_CELL0_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE_CELL0_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL0_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE_CELL0_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL0_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL0_VOL);
    }
    // 02/13. BAT_MODULE_CELL1_VOL to Database
    //     Table name : BAT_MODULE_0, Column name : BAT_MODULE_CELL1_VOL, Type : INT
    int32 BAT_MODULE_CELL1_VOL = 0;
    try {
        BAT_MODULE_CELL1_VOL = jsonInput["BAT_MODULE_CELL1_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE_CELL1_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE_CELL1_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL1_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE_CELL1_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL1_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL1_VOL);
    }
    // 03/13. BAT_MODULE_CELL2_VOL to Database
    //     Table name : BAT_MODULE_0, Column name : BAT_MODULE_CELL2_VOL, Type : INT
    int32 BAT_MODULE_CELL2_VOL = 0;
    try {
        BAT_MODULE_CELL2_VOL = jsonInput["BAT_MODULE_CELL2_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE_CELL2_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE_CELL2_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL2_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE_CELL2_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL2_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL2_VOL);
    }
    // 04/13. BAT_MODULE_CELL3_VOL to Database
    //     Table name : BAT_MODULE_0, Column name : BAT_MODULE_CELL3_VOL, Type : INT
    int32 BAT_MODULE_CELL3_VOL = 0;
    try {
        BAT_MODULE_CELL3_VOL = jsonInput["BAT_MODULE_CELL3_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE_CELL3_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE_CELL3_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL3_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE_CELL3_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL3_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL3_VOL);
    }
    // 05/13. BAT_MODULE_CELL4_VOL to Database
    //     Table name : BAT_MODULE_0, Column name : BAT_MODULE_CELL4_VOL, Type : INT
    int32 BAT_MODULE_CELL4_VOL = 0;
    try {
        BAT_MODULE_CELL4_VOL = jsonInput["BAT_MODULE_CELL4_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE_CELL4_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE_CELL4_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL4_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE_CELL4_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL4_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL4_VOL);
    }
    // 06/13. BAT_MODULE_CELL5_VOL to Database
    //     Table name : BAT_MODULE_0, Column name : BAT_MODULE_CELL5_VOL, Type : INT
    int32 BAT_MODULE_CELL5_VOL = 0;
    try {
        BAT_MODULE_CELL5_VOL = jsonInput["BAT_MODULE_CELL5_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE_CELL5_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE_CELL5_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL5_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE_CELL5_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL5_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL5_VOL);
    }
    // 07/13. BAT_MODULE_CELL6_VOL to Database
    //     Table name : BAT_MODULE_0, Column name : BAT_MODULE_CELL6_VOL, Type : INT
    int32 BAT_MODULE_CELL6_VOL = 0;
    try {
        BAT_MODULE_CELL6_VOL = jsonInput["BAT_MODULE_CELL6_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE_CELL6_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE_CELL6_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL6_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE_CELL6_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL6_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL6_VOL);
    }
    // 08/13. BAT_MODULE_CELL7_VOL to Database
    //     Table name : BAT_MODULE_0, Column name : BAT_MODULE_CELL7_VOL, Type : INT
    int32 BAT_MODULE_CELL7_VOL = 0;
    try {
        BAT_MODULE_CELL7_VOL = jsonInput["BAT_MODULE_CELL7_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE_CELL7_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE_CELL7_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL7_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE_CELL7_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL7_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL7_VOL);
    }
    // 09/13. BAT_MODULE_CELL8_VOL to Database
    //     Table name : BAT_MODULE_0, Column name : BAT_MODULE_CELL8_VOL, Type : INT
    int32 BAT_MODULE_CELL8_VOL = 0;
    try {
        BAT_MODULE_CELL8_VOL = jsonInput["BAT_MODULE_CELL8_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE_CELL8_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE_CELL8_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL8_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE_CELL8_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL8_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL8_VOL);
    }
    // 10/13. BAT_MODULE_CELL9_VOL to Database
    //     Table name : BAT_MODULE_0, Column name : BAT_MODULE_CELL9_VOL, Type : INT
    int32 BAT_MODULE_CELL9_VOL = 0;
    try {
        BAT_MODULE_CELL9_VOL = jsonInput["BAT_MODULE_CELL9_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE_CELL9_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE_CELL9_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL9_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE_CELL9_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL9_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL9_VOL);
    }
    // 11/13. BAT_MODULE_CELL10_VOL to Database
    //     Table name : BAT_MODULE_0, Column name : BAT_MODULE_CELL10_VOL, Type : INT
    int32 BAT_MODULE_CELL10_VOL = 0;
    try {
        BAT_MODULE_CELL10_VOL = jsonInput["BAT_MODULE_CELL10_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE_CELL10_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE_CELL10_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL10_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE_CELL10_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL10_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL10_VOL);
    }
    // 12/13. BAT_MODULE_CELL11_VOL to Database
    //     Table name : BAT_MODULE_0, Column name : BAT_MODULE_CELL11_VOL, Type : INT
    int32 BAT_MODULE_CELL11_VOL = 0;
    try {
        BAT_MODULE_CELL11_VOL = jsonInput["BAT_MODULE_CELL11_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE_CELL11_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE_CELL11_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL11_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE_CELL11_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL11_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE_CELL11_VOL);
    }
    // 13/13. System_time to Database
    //     Table name : BAT_MODULE_0, Column name : System_time, Type : NVARCHAR
    std::wstring wSystem_time = L"No input";
    WCHAR* pwSystem_time = nullptr;
    try {
        std::string System_time = jsonInput["System_time"].get<std::string>();
        wSystem_time = stringToWString(System_time);
        pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'System_time' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'System_time' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}

void EDT0001_BAT_MODULE_1_0004_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[]"
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

    
    // 01/13. BAT_MODULE1_CELL0_VOL to Database
    //     Table name : BAT_MODULE_1, Column name : BAT_MODULE1_CELL0_VOL, Type : INT
    int32 BAT_MODULE1_CELL0_VOL = 0;
    try {
        BAT_MODULE1_CELL0_VOL = jsonInput["BAT_MODULE1_CELL0_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE1_CELL0_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE1_CELL0_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL0_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE1_CELL0_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL0_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL0_VOL);
    }
    // 02/13. BAT_MODULE1_CELL1_VOL to Database
    //     Table name : BAT_MODULE_1, Column name : BAT_MODULE1_CELL1_VOL, Type : INT
    int32 BAT_MODULE1_CELL1_VOL = 0;
    try {
        BAT_MODULE1_CELL1_VOL = jsonInput["BAT_MODULE1_CELL1_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE1_CELL1_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE1_CELL1_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL1_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE1_CELL1_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL1_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL1_VOL);
    }
    // 03/13. BAT_MODULE1_CELL2_VOL to Database
    //     Table name : BAT_MODULE_1, Column name : BAT_MODULE1_CELL2_VOL, Type : INT
    int32 BAT_MODULE1_CELL2_VOL = 0;
    try {
        BAT_MODULE1_CELL2_VOL = jsonInput["BAT_MODULE1_CELL2_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE1_CELL2_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE1_CELL2_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL2_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE1_CELL2_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL2_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL2_VOL);
    }
    // 04/13. BAT_MODULE1_CELL3_VOL to Database
    //     Table name : BAT_MODULE_1, Column name : BAT_MODULE1_CELL3_VOL, Type : INT
    int32 BAT_MODULE1_CELL3_VOL = 0;
    try {
        BAT_MODULE1_CELL3_VOL = jsonInput["BAT_MODULE1_CELL3_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE1_CELL3_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE1_CELL3_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL3_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE1_CELL3_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL3_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL3_VOL);
    }
    // 05/13. BAT_MODULE1_CELL4_VOL to Database
    //     Table name : BAT_MODULE_1, Column name : BAT_MODULE1_CELL4_VOL, Type : INT
    int32 BAT_MODULE1_CELL4_VOL = 0;
    try {
        BAT_MODULE1_CELL4_VOL = jsonInput["BAT_MODULE1_CELL4_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE1_CELL4_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE1_CELL4_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL4_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE1_CELL4_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL4_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL4_VOL);
    }
    // 06/13. BAT_MODULE1_CELL5_VOL to Database
    //     Table name : BAT_MODULE_1, Column name : BAT_MODULE1_CELL5_VOL, Type : INT
    int32 BAT_MODULE1_CELL5_VOL = 0;
    try {
        BAT_MODULE1_CELL5_VOL = jsonInput["BAT_MODULE1_CELL5_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE1_CELL5_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE1_CELL5_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL5_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE1_CELL5_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL5_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL5_VOL);
    }
    // 07/13. BAT_MODULE1_CELL6_VOL to Database
    //     Table name : BAT_MODULE_1, Column name : BAT_MODULE1_CELL6_VOL, Type : INT
    int32 BAT_MODULE1_CELL6_VOL = 0;
    try {
        BAT_MODULE1_CELL6_VOL = jsonInput["BAT_MODULE1_CELL6_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE1_CELL6_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE1_CELL6_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL6_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE1_CELL6_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL6_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL6_VOL);
    }
    // 08/13. BAT_MODULE1_CELL7_VOL to Database
    //     Table name : BAT_MODULE_1, Column name : BAT_MODULE1_CELL7_VOL, Type : INT
    int32 BAT_MODULE1_CELL7_VOL = 0;
    try {
        BAT_MODULE1_CELL7_VOL = jsonInput["BAT_MODULE1_CELL7_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE1_CELL7_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE1_CELL7_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL7_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE1_CELL7_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL7_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL7_VOL);
    }
    // 09/13. BAT_MODULE1_CELL8_VOL to Database
    //     Table name : BAT_MODULE_1, Column name : BAT_MODULE1_CELL8_VOL, Type : INT
    int32 BAT_MODULE1_CELL8_VOL = 0;
    try {
        BAT_MODULE1_CELL8_VOL = jsonInput["BAT_MODULE1_CELL8_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE1_CELL8_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE1_CELL8_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL8_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE1_CELL8_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL8_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL8_VOL);
    }
    // 10/13. BAT_MODULE1_CELL9_VOL to Database
    //     Table name : BAT_MODULE_1, Column name : BAT_MODULE1_CELL9_VOL, Type : INT
    int32 BAT_MODULE1_CELL9_VOL = 0;
    try {
        BAT_MODULE1_CELL9_VOL = jsonInput["BAT_MODULE1_CELL9_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE1_CELL9_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE1_CELL9_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL9_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE1_CELL9_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL9_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL9_VOL);
    }
    // 11/13. BAT_MODULE1_CELL10_VOL to Database
    //     Table name : BAT_MODULE_1, Column name : BAT_MODULE1_CELL10_VOL, Type : INT
    int32 BAT_MODULE1_CELL10_VOL = 0;
    try {
        BAT_MODULE1_CELL10_VOL = jsonInput["BAT_MODULE1_CELL10_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE1_CELL10_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE1_CELL10_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL10_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE1_CELL10_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL10_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL10_VOL);
    }
    // 12/13. BAT_MODULE1_CELL11_VOL to Database
    //     Table name : BAT_MODULE_1, Column name : BAT_MODULE1_CELL11_VOL, Type : INT
    int32 BAT_MODULE1_CELL11_VOL = 0;
    try {
        BAT_MODULE1_CELL11_VOL = jsonInput["BAT_MODULE1_CELL11_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE1_CELL11_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE1_CELL11_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL11_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE1_CELL11_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL11_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE1_CELL11_VOL);
    }
    // 13/13. System_time to Database
    //     Table name : BAT_MODULE_1, Column name : System_time, Type : NVARCHAR
    std::wstring wSystem_time = L"No input";
    WCHAR* pwSystem_time = nullptr;
    try {
        std::string System_time = jsonInput["System_time"].get<std::string>();
        wSystem_time = stringToWString(System_time);
        pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'System_time' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'System_time' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}

void EDT0001_BAT_MODULE_2_0005_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[]"
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

    
    // 01/13. BAT_MODULE2_CELL0_VOL to Database
    //     Table name : BAT_MODULE_2, Column name : BAT_MODULE2_CELL0_VOL, Type : INT
    int32 BAT_MODULE2_CELL0_VOL = 0;
    try {
        BAT_MODULE2_CELL0_VOL = jsonInput["BAT_MODULE2_CELL0_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE2_CELL0_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE2_CELL0_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL0_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE2_CELL0_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL0_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL0_VOL);
    }
    // 02/13. BAT_MODULE2_CELL1_VOL to Database
    //     Table name : BAT_MODULE_2, Column name : BAT_MODULE2_CELL1_VOL, Type : INT
    int32 BAT_MODULE2_CELL1_VOL = 0;
    try {
        BAT_MODULE2_CELL1_VOL = jsonInput["BAT_MODULE2_CELL1_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE2_CELL1_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE2_CELL1_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL1_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE2_CELL1_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL1_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL1_VOL);
    }
    // 03/13. BAT_MODULE2_CELL2_VOL to Database
    //     Table name : BAT_MODULE_2, Column name : BAT_MODULE2_CELL2_VOL, Type : INT
    int32 BAT_MODULE2_CELL2_VOL = 0;
    try {
        BAT_MODULE2_CELL2_VOL = jsonInput["BAT_MODULE2_CELL2_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE2_CELL2_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE2_CELL2_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL2_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE2_CELL2_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL2_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL2_VOL);
    }
    // 04/13. BAT_MODULE2_CELL3_VOL to Database
    //     Table name : BAT_MODULE_2, Column name : BAT_MODULE2_CELL3_VOL, Type : INT
    int32 BAT_MODULE2_CELL3_VOL = 0;
    try {
        BAT_MODULE2_CELL3_VOL = jsonInput["BAT_MODULE2_CELL3_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE2_CELL3_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE2_CELL3_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL3_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE2_CELL3_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL3_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL3_VOL);
    }
    // 05/13. BAT_MODULE2_CELL4_VOL to Database
    //     Table name : BAT_MODULE_2, Column name : BAT_MODULE2_CELL4_VOL, Type : INT
    int32 BAT_MODULE2_CELL4_VOL = 0;
    try {
        BAT_MODULE2_CELL4_VOL = jsonInput["BAT_MODULE2_CELL4_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE2_CELL4_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE2_CELL4_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL4_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE2_CELL4_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL4_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL4_VOL);
    }
    // 06/13. BAT_MODULE2_CELL5_VOL to Database
    //     Table name : BAT_MODULE_2, Column name : BAT_MODULE2_CELL5_VOL, Type : INT
    int32 BAT_MODULE2_CELL5_VOL = 0;
    try {
        BAT_MODULE2_CELL5_VOL = jsonInput["BAT_MODULE2_CELL5_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE2_CELL5_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE2_CELL5_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL5_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE2_CELL5_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL5_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL5_VOL);
    }
    // 07/13. BAT_MODULE2_CELL6_VOL to Database
    //     Table name : BAT_MODULE_2, Column name : BAT_MODULE2_CELL6_VOL, Type : INT
    int32 BAT_MODULE2_CELL6_VOL = 0;
    try {
        BAT_MODULE2_CELL6_VOL = jsonInput["BAT_MODULE2_CELL6_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE2_CELL6_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE2_CELL6_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL6_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE2_CELL6_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL6_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL6_VOL);
    }
    // 08/13. BAT_MODULE2_CELL7_VOL to Database
    //     Table name : BAT_MODULE_2, Column name : BAT_MODULE2_CELL7_VOL, Type : INT
    int32 BAT_MODULE2_CELL7_VOL = 0;
    try {
        BAT_MODULE2_CELL7_VOL = jsonInput["BAT_MODULE2_CELL7_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE2_CELL7_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE2_CELL7_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL7_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE2_CELL7_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL7_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL7_VOL);
    }
    // 09/13. BAT_MODULE2_CELL8_VOL to Database
    //     Table name : BAT_MODULE_2, Column name : BAT_MODULE2_CELL8_VOL, Type : INT
    int32 BAT_MODULE2_CELL8_VOL = 0;
    try {
        BAT_MODULE2_CELL8_VOL = jsonInput["BAT_MODULE2_CELL8_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE2_CELL8_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE2_CELL8_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL8_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE2_CELL8_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL8_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL8_VOL);
    }
    // 10/13. BAT_MODULE2_CELL9_VOL to Database
    //     Table name : BAT_MODULE_2, Column name : BAT_MODULE2_CELL9_VOL, Type : INT
    int32 BAT_MODULE2_CELL9_VOL = 0;
    try {
        BAT_MODULE2_CELL9_VOL = jsonInput["BAT_MODULE2_CELL9_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE2_CELL9_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE2_CELL9_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL9_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE2_CELL9_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL9_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL9_VOL);
    }
    // 11/13. BAT_MODULE2_CELL10_VOL to Database
    //     Table name : BAT_MODULE_2, Column name : BAT_MODULE2_CELL10_VOL, Type : INT
    int32 BAT_MODULE2_CELL10_VOL = 0;
    try {
        BAT_MODULE2_CELL10_VOL = jsonInput["BAT_MODULE2_CELL10_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE2_CELL10_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE2_CELL10_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL10_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE2_CELL10_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL10_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL10_VOL);
    }
    // 12/13. BAT_MODULE2_CELL11_VOL to Database
    //     Table name : BAT_MODULE_2, Column name : BAT_MODULE2_CELL11_VOL, Type : INT
    int32 BAT_MODULE2_CELL11_VOL = 0;
    try {
        BAT_MODULE2_CELL11_VOL = jsonInput["BAT_MODULE2_CELL11_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE2_CELL11_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE2_CELL11_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL11_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE2_CELL11_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL11_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE2_CELL11_VOL);
    }
    // 13/13. System_time to Database
    //     Table name : BAT_MODULE_2, Column name : System_time, Type : NVARCHAR
    std::wstring wSystem_time = L"No input";
    WCHAR* pwSystem_time = nullptr;
    try {
        std::string System_time = jsonInput["System_time"].get<std::string>();
        wSystem_time = stringToWString(System_time);
        pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'System_time' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'System_time' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}

void EDT0001_BAT_MODULE_3_0006_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[]"
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

    
    // 01/06. BAT_MODULE3_CELL0_VOL to Database
    //     Table name : BAT_MODULE_3, Column name : BAT_MODULE3_CELL0_VOL, Type : INT
    int32 BAT_MODULE3_CELL0_VOL = 0;
    try {
        BAT_MODULE3_CELL0_VOL = jsonInput["BAT_MODULE3_CELL0_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE3_CELL0_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE3_CELL0_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL0_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE3_CELL0_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL0_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL0_VOL);
    }
    // 02/06. BAT_MODULE3_CELL1_VOL to Database
    //     Table name : BAT_MODULE_3, Column name : BAT_MODULE3_CELL1_VOL, Type : INT
    int32 BAT_MODULE3_CELL1_VOL = 0;
    try {
        BAT_MODULE3_CELL1_VOL = jsonInput["BAT_MODULE3_CELL1_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE3_CELL1_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE3_CELL1_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL1_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE3_CELL1_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL1_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL1_VOL);
    }
    // 03/06. BAT_MODULE3_CELL2_VOL to Database
    //     Table name : BAT_MODULE_3, Column name : BAT_MODULE3_CELL2_VOL, Type : INT
    int32 BAT_MODULE3_CELL2_VOL = 0;
    try {
        BAT_MODULE3_CELL2_VOL = jsonInput["BAT_MODULE3_CELL2_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE3_CELL2_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE3_CELL2_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL2_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE3_CELL2_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL2_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL2_VOL);
    }
    // 04/06. BAT_MODULE3_CELL8_VOL to Database
    //     Table name : BAT_MODULE_3, Column name : BAT_MODULE3_CELL8_VOL, Type : INT
    int32 BAT_MODULE3_CELL8_VOL = 0;
    try {
        BAT_MODULE3_CELL8_VOL = jsonInput["BAT_MODULE3_CELL8_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE3_CELL8_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE3_CELL8_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL8_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE3_CELL8_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL8_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL8_VOL);
    }
    // 05/06. BAT_MODULE3_CELL10_VOL to Database
    //     Table name : BAT_MODULE_3, Column name : BAT_MODULE3_CELL10_VOL, Type : INT
    int32 BAT_MODULE3_CELL10_VOL = 0;
    try {
        BAT_MODULE3_CELL10_VOL = jsonInput["BAT_MODULE3_CELL10_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE3_CELL10_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE3_CELL10_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL10_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE3_CELL10_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL10_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL10_VOL);
    }
    // 06/06. BAT_MODULE3_CELL11_VOL to Database
    //     Table name : BAT_MODULE_3, Column name : BAT_MODULE3_CELL11_VOL, Type : INT
    int32 BAT_MODULE3_CELL11_VOL = 0;
    try {
        BAT_MODULE3_CELL11_VOL = jsonInput["BAT_MODULE3_CELL11_VOL"].get<int32>();
        dbBind.BindParam(count++,BAT_MODULE3_CELL11_VOL);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'BAT_MODULE3_CELL11_VOL' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL11_VOL);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'BAT_MODULE3_CELL11_VOL' value:" << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL11_VOL);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,BAT_MODULE3_CELL11_VOL);
    }

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}

void EDT0001_Environment_0007_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[]"
    L"("
    L"[Wind_speed],"
    L"[Wind_direction],"
    L"[System_time]"
    L")"
    L"VALUES(?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <3,0> dbBind(*dbConn, query);
    int32 count = 0;

    
    // 01/03. Wind_speed to Database
    //     Table name : Environment, Column name : Wind_speed, Type : INT
    int32 Wind_speed = 0;
    try {
        Wind_speed = jsonInput["Wind_speed"].get<int32>();
        dbBind.BindParam(count++,Wind_speed);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'Wind_speed' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,Wind_speed);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'Wind_speed' value:" << e.what() << '\n';
        dbBind.BindParam(count++,Wind_speed);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,Wind_speed);
    }
    // 02/03. Wind_direction to Database
    //     Table name : Environment, Column name : Wind_direction, Type : INT
    int32 Wind_direction = 0;
    try {
        Wind_direction = jsonInput["Wind_direction"].get<int32>();
        dbBind.BindParam(count++,Wind_direction);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'Wind_direction' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,Wind_direction);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'Wind_direction' value:" << e.what() << '\n';
        dbBind.BindParam(count++,Wind_direction);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,Wind_direction);
    }
    // 03/03. System_time to Database
    //     Table name : Environment, Column name : System_time, Type : NVARCHAR
    std::wstring wSystem_time = L"No input";
    WCHAR* pwSystem_time = nullptr;
    try {
        std::string System_time = jsonInput["System_time"].get<std::string>();
        wSystem_time = stringToWString(System_time);
        pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'System_time' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'System_time' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}

void EDT0001_AIS_0008_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[]"
    L"("
    L"[latitude],"
    L"[longitude],"
    L"[System_time]"
    L")"
    L"VALUES(?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <3,0> dbBind(*dbConn, query);
    int32 count = 0;

    
    // 01/03. latitude to Database
    //     Table name : AIS, Column name : latitude, Type : NVARCHAR
    std::wstring wlatitude = L"No input";
    WCHAR* pwlatitude = nullptr;
    try {
        std::string latitude = jsonInput["latitude"].get<std::string>();
        wlatitude = stringToWString(latitude);
        pwlatitude = const_cast<WCHAR*>(wlatitude.c_str());
        dbBind.BindParam(count++, pwlatitude);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'latitude' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pwlatitude);
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'latitude' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pwlatitude);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pwlatitude);
    }
    // 02/03. longitude to Database
    //     Table name : AIS, Column name : longitude, Type : NVARCHAR
    std::wstring wlongitude = L"No input";
    WCHAR* pwlongitude = nullptr;
    try {
        std::string longitude = jsonInput["longitude"].get<std::string>();
        wlongitude = stringToWString(longitude);
        pwlongitude = const_cast<WCHAR*>(wlongitude.c_str());
        dbBind.BindParam(count++, pwlongitude);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'longitude' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pwlongitude);
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'longitude' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pwlongitude);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pwlongitude);
    }
    // 03/03. System_time to Database
    //     Table name : AIS, Column name : System_time, Type : NVARCHAR
    std::wstring wSystem_time = L"No input";
    WCHAR* pwSystem_time = nullptr;
    try {
        std::string System_time = jsonInput["System_time"].get<std::string>();
        wSystem_time = stringToWString(System_time);
        pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'System_time' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'System_time' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}

void EDT0001_System_Time_0009_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[]"
    L"("
    L"[System_time]"
    L")"
    L"VALUES(?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <1,0> dbBind(*dbConn, query);
    int32 count = 0;

    
    // 01/01. System_time to Database
    //     Table name : System_Time, Column name : System_time, Type : NVARCHAR
    std::wstring wSystem_time = L"No input";
    WCHAR* pwSystem_time = nullptr;
    try {
        std::string System_time = jsonInput["System_time"].get<std::string>();
        wSystem_time = stringToWString(System_time);
        pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'System_time' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'System_time' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}

void EDT0001_MOTOR_0010_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[]"
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

    
    // 01/04. MT_RPM to Database
    //     Table name : MOTOR, Column name : MT_RPM, Type : INT
    int32 MT_RPM = 0;
    try {
        MT_RPM = jsonInput["MT_RPM"].get<int32>();
        dbBind.BindParam(count++,MT_RPM);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'MT_RPM' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,MT_RPM);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'MT_RPM' value:" << e.what() << '\n';
        dbBind.BindParam(count++,MT_RPM);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,MT_RPM);
    }
    // 02/04. MT_TORQUE to Database
    //     Table name : MOTOR, Column name : MT_TORQUE, Type : INT
    int32 MT_TORQUE = 0;
    try {
        MT_TORQUE = jsonInput["MT_TORQUE"].get<int32>();
        dbBind.BindParam(count++,MT_TORQUE);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'MT_TORQUE' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,MT_TORQUE);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'MT_TORQUE' value:" << e.what() << '\n';
        dbBind.BindParam(count++,MT_TORQUE);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,MT_TORQUE);
    }
    // 03/04. MT_TEMP to Database
    //     Table name : MOTOR, Column name : MT_TEMP, Type : INT
    int32 MT_TEMP = 0;
    try {
        MT_TEMP = jsonInput["MT_TEMP"].get<int32>();
        dbBind.BindParam(count++,MT_TEMP);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'MT_TEMP' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,MT_TEMP);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'MT_TEMP' value:" << e.what() << '\n';
        dbBind.BindParam(count++,MT_TEMP);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,MT_TEMP);
    }
    // 04/04. System_time to Database
    //     Table name : MOTOR, Column name : System_time, Type : NVARCHAR
    std::wstring wSystem_time = L"No input";
    WCHAR* pwSystem_time = nullptr;
    try {
        std::string System_time = jsonInput["System_time"].get<std::string>();
        wSystem_time = stringToWString(System_time);
        pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'System_time' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'System_time' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}

void EDT0001_INVERTER_0011_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[]"
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

    
    // 01/12. INV_PHASE_A_CURRENT to Database
    //     Table name : INVERTER, Column name : INV_PHASE_A_CURRENT, Type : INT
    int32 INV_PHASE_A_CURRENT = 0;
    try {
        INV_PHASE_A_CURRENT = jsonInput["INV_PHASE_A_CURRENT"].get<int32>();
        dbBind.BindParam(count++,INV_PHASE_A_CURRENT);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'INV_PHASE_A_CURRENT' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_PHASE_A_CURRENT);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'INV_PHASE_A_CURRENT' value:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_PHASE_A_CURRENT);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,INV_PHASE_A_CURRENT);
    }
    // 02/12. INV_PHASE_B_CURRENT to Database
    //     Table name : INVERTER, Column name : INV_PHASE_B_CURRENT, Type : INT
    int32 INV_PHASE_B_CURRENT = 0;
    try {
        INV_PHASE_B_CURRENT = jsonInput["INV_PHASE_B_CURRENT"].get<int32>();
        dbBind.BindParam(count++,INV_PHASE_B_CURRENT);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'INV_PHASE_B_CURRENT' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_PHASE_B_CURRENT);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'INV_PHASE_B_CURRENT' value:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_PHASE_B_CURRENT);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,INV_PHASE_B_CURRENT);
    }
    // 03/12. INV_PHASE_C_CURRENT to Database
    //     Table name : INVERTER, Column name : INV_PHASE_C_CURRENT, Type : INT
    int32 INV_PHASE_C_CURRENT = 0;
    try {
        INV_PHASE_C_CURRENT = jsonInput["INV_PHASE_C_CURRENT"].get<int32>();
        dbBind.BindParam(count++,INV_PHASE_C_CURRENT);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'INV_PHASE_C_CURRENT' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_PHASE_C_CURRENT);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'INV_PHASE_C_CURRENT' value:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_PHASE_C_CURRENT);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,INV_PHASE_C_CURRENT);
    }
    // 04/12. INV_POST_FAULT to Database
    //     Table name : INVERTER, Column name : INV_POST_FAULT, Type : INT
    int32 INV_POST_FAULT = 0;
    try {
        INV_POST_FAULT = jsonInput["INV_POST_FAULT"].get<int32>();
        dbBind.BindParam(count++,INV_POST_FAULT);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'INV_POST_FAULT' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_POST_FAULT);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'INV_POST_FAULT' value:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_POST_FAULT);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,INV_POST_FAULT);
    }
    // 05/12. INV_GATE_DRIVER_BOARD_TEMP to Database
    //     Table name : INVERTER, Column name : INV_GATE_DRIVER_BOARD_TEMP, Type : INT
    int32 INV_GATE_DRIVER_BOARD_TEMP = 0;
    try {
        INV_GATE_DRIVER_BOARD_TEMP = jsonInput["INV_GATE_DRIVER_BOARD_TEMP"].get<int32>();
        dbBind.BindParam(count++,INV_GATE_DRIVER_BOARD_TEMP);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'INV_GATE_DRIVER_BOARD_TEMP' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_GATE_DRIVER_BOARD_TEMP);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'INV_GATE_DRIVER_BOARD_TEMP' value:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_GATE_DRIVER_BOARD_TEMP);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,INV_GATE_DRIVER_BOARD_TEMP);
    }
    // 06/12. INV_MODULE_A_TEMP to Database
    //     Table name : INVERTER, Column name : INV_MODULE_A_TEMP, Type : INT
    int32 INV_MODULE_A_TEMP = 0;
    try {
        INV_MODULE_A_TEMP = jsonInput["INV_MODULE_A_TEMP"].get<int32>();
        dbBind.BindParam(count++,INV_MODULE_A_TEMP);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'INV_MODULE_A_TEMP' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_MODULE_A_TEMP);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'INV_MODULE_A_TEMP' value:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_MODULE_A_TEMP);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,INV_MODULE_A_TEMP);
    }
    // 07/12. INV_RUN_FAULT to Database
    //     Table name : INVERTER, Column name : INV_RUN_FAULT, Type : INT
    int32 INV_RUN_FAULT = 0;
    try {
        INV_RUN_FAULT = jsonInput["INV_RUN_FAULT"].get<int32>();
        dbBind.BindParam(count++,INV_RUN_FAULT);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'INV_RUN_FAULT' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_RUN_FAULT);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'INV_RUN_FAULT' value:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_RUN_FAULT);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,INV_RUN_FAULT);
    }
    // 08/12. INV_MODULE_B_TEMP to Database
    //     Table name : INVERTER, Column name : INV_MODULE_B_TEMP, Type : INT
    int32 INV_MODULE_B_TEMP = 0;
    try {
        INV_MODULE_B_TEMP = jsonInput["INV_MODULE_B_TEMP"].get<int32>();
        dbBind.BindParam(count++,INV_MODULE_B_TEMP);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'INV_MODULE_B_TEMP' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_MODULE_B_TEMP);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'INV_MODULE_B_TEMP' value:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_MODULE_B_TEMP);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,INV_MODULE_B_TEMP);
    }
    // 09/12. INV_MODULE_C_TEMP to Database
    //     Table name : INVERTER, Column name : INV_MODULE_C_TEMP, Type : INT
    int32 INV_MODULE_C_TEMP = 0;
    try {
        INV_MODULE_C_TEMP = jsonInput["INV_MODULE_C_TEMP"].get<int32>();
        dbBind.BindParam(count++,INV_MODULE_C_TEMP);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'INV_MODULE_C_TEMP' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_MODULE_C_TEMP);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'INV_MODULE_C_TEMP' value:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_MODULE_C_TEMP);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,INV_MODULE_C_TEMP);
    }
    // 10/12. INV_POWER to Database
    //     Table name : INVERTER, Column name : INV_POWER, Type : INT
    int32 INV_POWER = 0;
    try {
        INV_POWER = jsonInput["INV_POWER"].get<int32>();
        dbBind.BindParam(count++,INV_POWER);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'INV_POWER' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_POWER);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'INV_POWER' value:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_POWER);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,INV_POWER);
    }
    // 11/12. INV_OUTPUT_VOLTAGE to Database
    //     Table name : INVERTER, Column name : INV_OUTPUT_VOLTAGE, Type : INT
    int32 INV_OUTPUT_VOLTAGE = 0;
    try {
        INV_OUTPUT_VOLTAGE = jsonInput["INV_OUTPUT_VOLTAGE"].get<int32>();
        dbBind.BindParam(count++,INV_OUTPUT_VOLTAGE);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'INV_OUTPUT_VOLTAGE' not found in JSON input:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_OUTPUT_VOLTAGE);
    }
    catch (const nlohmann::json::type_error&   e) {
        std::cerr << "Type error in 'INV_OUTPUT_VOLTAGE' value:" << e.what() << '\n';
        dbBind.BindParam(count++,INV_OUTPUT_VOLTAGE);
    }
    catch (const nlohmann::json::exception&    e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++,INV_OUTPUT_VOLTAGE);
    }
    // 12/12. System_time to Database
    //     Table name : INVERTER, Column name : System_time, Type : NVARCHAR
    std::wstring wSystem_time = L"No input";
    WCHAR* pwSystem_time = nullptr;
    try {
        std::string System_time = jsonInput["System_time"].get<std::string>();
        wSystem_time = stringToWString(System_time);
        pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::out_of_range& e) {
        std::cerr << "Key 'System_time' not found in JSON input: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error in 'System_time' value: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        dbBind.BindParam(count++, pwSystem_time);
    }

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}

EDT0001_JsonHandler::EDT0001_JsonHandler(nlohmann::json inputjson) : _EdtJson(inputjson)
{

}

EDT0001_JsonHandler::~EDT0001_JsonHandler()
{
}
