#pragma once
#include "pch.h"
#include "JsonPacketHandler.h"

﻿bool Send_ship_test_ver2_ToDb(nlohmann::json& jsonInput)
{
    // SP 방법 검토
    // 동적 쿼리
    auto query = L"INSERT INTO [dbo].[ship_test_ver2]"
        L"("L"[INV_PHASE_A_CURRENT],"
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
    DBBind <19,0> dbBind(*dbConn, query);
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
    
    std::string latitude = jsonInput["latitude"].get<std::string>();
    std::wstring wlatitude = stringToWString(latitude);
    WCHAR* pwlatitude = const_cast<WCHAR*>(wlatitude.c_str());
    dbBind.BindParam(count++, pwlatitude);
    
    std::string longitude = jsonInput["longitude"].get<std::string>();
    std::wstring wlongitude = stringToWString(longitude);
    WCHAR* pwlongitude = const_cast<WCHAR*>(wlongitude.c_str());
    dbBind.BindParam(count++, pwlongitude);
    
    std::string System_time = jsonInput["System_time"].get<std::string>();
    std::wstring wSystem_time = stringToWString(System_time);
    WCHAR* pwSystem_time = const_cast<WCHAR*>(wSystem_time.c_str());
    dbBind.BindParam(count++, pwSystem_time);
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    return true;
}

﻿bool Send_INVERTER_ToDb(nlohmann::json& jsonInput)
{
    // SP 방법 검토
    // 동적 쿼리
    auto query = L"INSERT INTO [dbo].[INVERTER]"
        L"("L"[INV_PHASE_A_CURRENT],"
    L"[INV_PHASE_B_CURRENT],"
    L"[INV_PHASE_C_CURRENT],"
    L"[INV_POST_FAULT],"
    L"[INV_RUN_FAULT],"
    L"[INV_GATE_DRIVER_BOARD_TEMP],"
    L"[INV_MODULE_A_TEMP],"
    L"[INV_MODULE_B_TEMP],"
    L"[INV_MODULE_C_TEMP],"
    L"[INV_POWER],"
    L"[INV_OUTPUT_VOLTAGE]"
    L")"
    L" VALUES (?,?,?,?,?,?,?,?,?,?,?)";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <11,0> dbBind(*dbConn, query);
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
    

    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);

    return true;
}

