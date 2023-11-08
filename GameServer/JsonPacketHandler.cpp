#pragma once
#include "pch.h"
#include "JsonPacketHandler.h"

void Send_Battery_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[Battery]"
    L"("
    L"[BAT_BPU_NEGATIVE_CONTACTOR],"
    L"[BAT_BPU_POSITIVE_CONTACTOR],"
    L"[BAT_BPU_PRE_CONTACTOR],"
    L"[BAT_PROTECTION_A],"
    L"[BAT_PROTECTION_B]"
    L")"
    L"VALUES(?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <5,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 BAT_BPU_NEGATIVE_CONTACTOR = jsonInput["BAT_BPU_NEGATIVE_CONTACTOR"].get<int32>();
    dbBind.BindParam(count++, BAT_BPU_NEGATIVE_CONTACTOR);
    
    int32 BAT_BPU_POSITIVE_CONTACTOR = jsonInput["BAT_BPU_POSITIVE_CONTACTOR"].get<int32>();
    dbBind.BindParam(count++, BAT_BPU_POSITIVE_CONTACTOR);
    
    //int32 BAT_BPU_PRE_CONTACTOR = jsonInput["BAT_BPU_PRE_CONTACTOR"].get<int32>();
    //dbBind.BindParam(count++, BAT_BPU_PRE_CONTACTOR);

    try {
        // JSON에서 "BAT_BPU_PRE_CONTACTOR" 값을 추출합니다.
        int32 BAT_BPU_PRE_CONTACTOR = jsonInput.at("BAT_BPU_PRE_CONTACTOR").get<int32>();
        dbBind.BindParam(count++, BAT_BPU_PRE_CONTACTOR);
    }
    catch (const nlohmann::json::out_of_range& e) {
        // "BAT_BPU_PRE_CONTACTOR" 키가 JSON에 존재하지 않을 경우 예외 처리합니다.

        std::cerr << "Key 'BAT_BPU_PRE_CONTACTOR' not found in JSON input: " << e.what() << '\n';
        int32 BAT_BPU_PRE_CONTACTOR = NULL;
        dbBind.BindParam(count++, BAT_BPU_PRE_CONTACTOR);
        // 여기서는 예외를 캐치하고 로그를 남긴 후,
        // 기본값을 사용하여 프로그램의 실행을 계속합니다.
    }
    catch (const nlohmann::json::type_error& e) {
        // "BAT_BPU_PRE_CONTACTOR" 값이 int32 형식이 아닐 경우 예외 처리합니다.
        std::cerr << "Type error in 'BAT_BPU_PRE_CONTACTOR' value: " << e.what() << '\n';
        // 타입 에러가 발생해도 프로그램은 기본값을 사용하여 계속 실행됩니다.
    }
    catch (const std::exception& e) {
        // 그 외 모든 std::exception 기반의 예외를 캐치합니다.
        std::cerr << "Unexpected error: " << e.what() << '\n';
        // 기본값을 사용하여 프로그램의 실행을 계속합니다.
    }
    
    int32 BAT_PROTECTION_A = jsonInput["BAT_PROTECTION_A"].get<int32>();
    dbBind.BindParam(count++, BAT_PROTECTION_A);
    
    int32 BAT_PROTECTION_B = jsonInput["BAT_PROTECTION_B"].get<int32>();
    dbBind.BindParam(count++, BAT_PROTECTION_B);
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    
}


void Send_Battery_Pack_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[Battery_Pack]"
    L"(";
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
    L"[BAT_PACK_MIN_CELL_VOL_SBMS_INDEX]"
    L")"
    L"VALUES(?,?,?,?,?,?,?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <11,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 BAT_PACK_CURRENT = jsonInput["BAT_PACK_CURRENT"].get<int32>();
    dbBind.BindParam(count++, BAT_PACK_CURRENT);
    
    int32 BAT_PACK_SOC = jsonInput["BAT_PACK_SOC"].get<int32>();
    dbBind.BindParam(count++, BAT_PACK_SOC);
    
    int32 BAT_PACK_VOLTAGE = jsonInput["BAT_PACK_VOLTAGE"].get<int32>();
    dbBind.BindParam(count++, BAT_PACK_VOLTAGE);
    
    int32 BAT_PACK_MAX_TEMP = jsonInput["BAT_PACK_MAX_TEMP"].get<int32>();
    dbBind.BindParam(count++, BAT_PACK_MAX_TEMP);
    
    int32 BAT_PACK_MAX_TEMP_SBMS_INDEX = jsonInput["BAT_PACK_MAX_TEMP_SBMS_INDEX"].get<int32>();
    dbBind.BindParam(count++, BAT_PACK_MAX_TEMP_SBMS_INDEX);
    
    int32 BAT_PACK_MIN_TEMP = jsonInput["BAT_PACK_MIN_TEMP"].get<int32>();
    dbBind.BindParam(count++, BAT_PACK_MIN_TEMP);
    
    int32 BAT_PACK_MIN_TEMP_SBMS_INDEX = jsonInput["BAT_PACK_MIN_TEMP_SBMS_INDEX"].get<int32>();
    dbBind.BindParam(count++, BAT_PACK_MIN_TEMP_SBMS_INDEX);
    
    int32 BAT_PACK_MAX_CELL_VOL = jsonInput["BAT_PACK_MAX_CELL_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_PACK_MAX_CELL_VOL);
    
    int32 BAT_PACK_MAX_CELL_VOL_SBMS_INDEX = jsonInput["BAT_PACK_MAX_CELL_VOL_SBMS_INDEX"].get<int32>();
    dbBind.BindParam(count++, BAT_PACK_MAX_CELL_VOL_SBMS_INDEX);
    
    int32 BAT_PACK_MIN_CELL_VOL = jsonInput["BAT_PACK_MIN_CELL_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_PACK_MIN_CELL_VOL);
    
    int32 BAT_PACK_MIN_CELL_VOL_SBMS_INDEX = jsonInput["BAT_PACK_MIN_CELL_VOL_SBMS_INDEX"].get<int32>();
    dbBind.BindParam(count++, BAT_PACK_MIN_CELL_VOL_SBMS_INDEX);
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    
}


void Send_BAT_MODULE_0_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[BAT_MODULE_0]"
    L"(";
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
    L"[BAT_MODULE_CELL11_VOL]"
    L")"
    L"VALUES(?,?,?,?,?,?,?,?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <12,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 BAT_MODULE_CELL0_VOL = jsonInput["BAT_MODULE_CELL0_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE_CELL0_VOL);
    
    int32 BAT_MODULE_CELL1_VOL = jsonInput["BAT_MODULE_CELL1_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE_CELL1_VOL);
    
    int32 BAT_MODULE_CELL2_VOL = jsonInput["BAT_MODULE_CELL2_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE_CELL2_VOL);
    
    int32 BAT_MODULE_CELL3_VOL = jsonInput["BAT_MODULE_CELL3_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE_CELL3_VOL);
    
    int32 BAT_MODULE_CELL4_VOL = jsonInput["BAT_MODULE_CELL4_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE_CELL4_VOL);
    
    int32 BAT_MODULE_CELL5_VOL = jsonInput["BAT_MODULE_CELL5_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE_CELL5_VOL);
    
    int32 BAT_MODULE_CELL6_VOL = jsonInput["BAT_MODULE_CELL6_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE_CELL6_VOL);
    
    int32 BAT_MODULE_CELL7_VOL = jsonInput["BAT_MODULE_CELL7_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE_CELL7_VOL);
    
    int32 BAT_MODULE_CELL8_VOL = jsonInput["BAT_MODULE_CELL8_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE_CELL8_VOL);
    
    int32 BAT_MODULE_CELL9_VOL = jsonInput["BAT_MODULE_CELL9_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE_CELL9_VOL);
    
    int32 BAT_MODULE_CELL10_VOL = jsonInput["BAT_MODULE_CELL10_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE_CELL10_VOL);
    
    int32 BAT_MODULE_CELL11_VOL = jsonInput["BAT_MODULE_CELL11_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE_CELL11_VOL);
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    
}


void Send_BAT_MODULE_1_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[BAT_MODULE_1]"
    L"(";
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
    L"[BAT_MODULE1_CELL11_VOL]"
    L")"
    L"VALUES(?,?,?,?,?,?,?,?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <12,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 BAT_MODULE1_CELL0_VOL = jsonInput["BAT_MODULE1_CELL0_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE1_CELL0_VOL);
    
    int32 BAT_MODULE1_CELL1_VOL = jsonInput["BAT_MODULE1_CELL1_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE1_CELL1_VOL);
    
    int32 BAT_MODULE1_CELL2_VOL = jsonInput["BAT_MODULE1_CELL2_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE1_CELL2_VOL);
    
    int32 BAT_MODULE1_CELL3_VOL = jsonInput["BAT_MODULE1_CELL3_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE1_CELL3_VOL);
    
    int32 BAT_MODULE1_CELL4_VOL = jsonInput["BAT_MODULE1_CELL4_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE1_CELL4_VOL);
    
    int32 BAT_MODULE1_CELL5_VOL = jsonInput["BAT_MODULE1_CELL5_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE1_CELL5_VOL);
    
    int32 BAT_MODULE1_CELL6_VOL = jsonInput["BAT_MODULE1_CELL6_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE1_CELL6_VOL);
    
    int32 BAT_MODULE1_CELL7_VOL = jsonInput["BAT_MODULE1_CELL7_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE1_CELL7_VOL);
    
    int32 BAT_MODULE1_CELL8_VOL = jsonInput["BAT_MODULE1_CELL8_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE1_CELL8_VOL);
    
    int32 BAT_MODULE1_CELL9_VOL = jsonInput["BAT_MODULE1_CELL9_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE1_CELL9_VOL);
    
    int32 BAT_MODULE1_CELL10_VOL = jsonInput["BAT_MODULE1_CELL10_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE1_CELL10_VOL);
    
    int32 BAT_MODULE1_CELL11_VOL = jsonInput["BAT_MODULE1_CELL11_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE1_CELL11_VOL);
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    
}


void Send_BAT_MODULE_2_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[BAT_MODULE_2]"
    L"(";
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
    L"[BAT_MODULE2_CELL11_VOL]"
    L")"
    L"VALUES(?,?,?,?,?,?,?,?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <12,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 BAT_MODULE2_CELL0_VOL = jsonInput["BAT_MODULE2_CELL0_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE2_CELL0_VOL);
    
    int32 BAT_MODULE2_CELL1_VOL = jsonInput["BAT_MODULE2_CELL1_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE2_CELL1_VOL);
    
    int32 BAT_MODULE2_CELL2_VOL = jsonInput["BAT_MODULE2_CELL2_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE2_CELL2_VOL);
    
    int32 BAT_MODULE2_CELL3_VOL = jsonInput["BAT_MODULE2_CELL3_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE2_CELL3_VOL);
    
    int32 BAT_MODULE2_CELL4_VOL = jsonInput["BAT_MODULE2_CELL4_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE2_CELL4_VOL);
    
    int32 BAT_MODULE2_CELL5_VOL = jsonInput["BAT_MODULE2_CELL5_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE2_CELL5_VOL);
    
    int32 BAT_MODULE2_CELL6_VOL = jsonInput["BAT_MODULE2_CELL6_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE2_CELL6_VOL);
    
    int32 BAT_MODULE2_CELL7_VOL = jsonInput["BAT_MODULE2_CELL7_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE2_CELL7_VOL);
    
    int32 BAT_MODULE2_CELL8_VOL = jsonInput["BAT_MODULE2_CELL8_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE2_CELL8_VOL);
    
    int32 BAT_MODULE2_CELL9_VOL = jsonInput["BAT_MODULE2_CELL9_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE2_CELL9_VOL);
    
    int32 BAT_MODULE2_CELL10_VOL = jsonInput["BAT_MODULE2_CELL10_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE2_CELL10_VOL);
    
    int32 BAT_MODULE2_CELL11_VOL = jsonInput["BAT_MODULE2_CELL11_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE2_CELL11_VOL);
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    
}


void Send_BAT_MODULE_3_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[BAT_MODULE_3]"
    L"(";
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
    
    int32 BAT_MODULE3_CELL0_VOL = jsonInput["BAT_MODULE3_CELL0_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE3_CELL0_VOL);
    
    int32 BAT_MODULE3_CELL1_VOL = jsonInput["BAT_MODULE3_CELL1_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE3_CELL1_VOL);
    
    int32 BAT_MODULE3_CELL2_VOL = jsonInput["BAT_MODULE3_CELL2_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE3_CELL2_VOL);
    
    int32 BAT_MODULE3_CELL8_VOL = jsonInput["BAT_MODULE3_CELL8_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE3_CELL8_VOL);
    
    int32 BAT_MODULE3_CELL10_VOL = jsonInput["BAT_MODULE3_CELL10_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE3_CELL10_VOL);
    
    int32 BAT_MODULE3_CELL11_VOL = jsonInput["BAT_MODULE3_CELL11_VOL"].get<int32>();
    dbBind.BindParam(count++, BAT_MODULE3_CELL11_VOL);
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    
}


void Send_Environment_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[Environment]"
    L"(";
    L"[Wind_speed],"
    L"[Wind_direction]"
    L")"
    L"VALUES(?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <2,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 Wind_speed = jsonInput["Wind_speed"].get<int32>();
    dbBind.BindParam(count++, Wind_speed);
    
    int32 Wind_direction = jsonInput["Wind_direction"].get<int32>();
    dbBind.BindParam(count++, Wind_direction);
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    
}


void Send_AIS_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[AIS]"
    L"(";
    L"[latitude],"
    L"[longitude]"
    L")"
    L"VALUES(?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <2,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    std::string latitude = jsonInput["latitude"].get<std::string>();
    std::wstring wlatitude = stringToWString(latitude);
    WCHAR* pwlatitude = const_cast<WCHAR*>(wlatitude.c_str());
    dbBind.BindParam(count++, pwlatitude);
    
    std::string longitude = jsonInput["longitude"].get<std::string>();
    std::wstring wlongitude = stringToWString(longitude);
    WCHAR* pwlongitude = const_cast<WCHAR*>(wlongitude.c_str());
    dbBind.BindParam(count++, pwlongitude);
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    
}


void Send_System_Time_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[System_Time]"
    L"(";
    L"[System_time]"
    L")"
    L"VALUES(?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <1,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    std::string System_time = jsonInput["System_time"].get<std::string>();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    
}


void Send_MOTOR_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[MOTOR]"
    L"(";
    L"[MT_RPM],"
    L"[MT_TORQUE],"
    L"[MT_TEMP]"
    L")"
    L"VALUES(?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <3,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 MT_RPM = jsonInput["MT_RPM"].get<int32>();
    dbBind.BindParam(count++, MT_RPM);
    
    int32 MT_TORQUE = jsonInput["MT_TORQUE"].get<int32>();
    dbBind.BindParam(count++, MT_TORQUE);
    
    int32 MT_TEMP = jsonInput["MT_TEMP"].get<int32>();
    dbBind.BindParam(count++, MT_TEMP);
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    
}


void Send_INVERTER_ToDb(nlohmann::json& jsonInput)
{
    auto query = L"INSERT INTO [dbo].[INVERTER]"
    L"(";
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
    L"[INV_OUTPUT_VOLTAGE]"
    L")"
    L"VALUES(?,?,?,?,?,?,?,?,?,?,?);";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <11,0> dbBind(*dbConn, query);
    int32 count = 0;
    
    int32 INV_PHASE_A_CURRENT = jsonInput["INV_PHASE_A_CURRENT"].get<int32>();
    dbBind.BindParam(count++, INV_PHASE_A_CURRENT);
    
    int32 INV_PHASE_B_CURRENT = jsonInput["INV_PHASE_B_CURRENT"].get<int32>();
    dbBind.BindParam(count++, INV_PHASE_B_CURRENT);
    
    int32 INV_PHASE_C_CURRENT = jsonInput["INV_PHASE_C_CURRENT"].get<int32>();
    dbBind.BindParam(count++, INV_PHASE_C_CURRENT);
    
    int32 INV_POST_FAULT = jsonInput["INV_POST_FAULT"].get<int32>();
    dbBind.BindParam(count++, INV_POST_FAULT);
    
    int32 INV_GATE_DRIVER_BOARD_TEMP = jsonInput["INV_GATE_DRIVER_BOARD_TEMP"].get<int32>();
    dbBind.BindParam(count++, INV_GATE_DRIVER_BOARD_TEMP);
    
    int32 INV_MODULE_A_TEMP = jsonInput["INV_MODULE_A_TEMP"].get<int32>();
    dbBind.BindParam(count++, INV_MODULE_A_TEMP);
    
    int32 INV_RUN_FAULT = jsonInput["INV_RUN_FAULT"].get<int32>();
    dbBind.BindParam(count++, INV_RUN_FAULT);
    
    int32 INV_MODULE_B_TEMP = jsonInput["INV_MODULE_B_TEMP"].get<int32>();
    dbBind.BindParam(count++, INV_MODULE_B_TEMP);
    
    int32 INV_MODULE_C_TEMP = jsonInput["INV_MODULE_C_TEMP"].get<int32>();
    dbBind.BindParam(count++, INV_MODULE_C_TEMP);
    
    int32 INV_POWER = jsonInput["INV_POWER"].get<int32>();
    dbBind.BindParam(count++, INV_POWER);
    
    int32 INV_OUTPUT_VOLTAGE = jsonInput["INV_OUTPUT_VOLTAGE"].get<int32>();
    dbBind.BindParam(count++, INV_OUTPUT_VOLTAGE);
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    
}


