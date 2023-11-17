#pragma once
#include "DBBind.h"
#include "pch.h"
#include "DBConnectionPool.h"
#include "Protocol.pb.h"


class EDT0001_PacketHandler
{
public:
	EDT0001_PacketHandler(BYTE* buffer, int32 len); // 생성자
	~EDT0001_PacketHandler(); // 소멸자

private:
	
	void SanitizeAndFormatAsJSON(std::string& str);
	void replaceDegrees(std::string& str);
	void addBackslashBeforeQuotes(std::string& str);
	
	bool ParseJsonFromStr();

	template<typename T>
	void ValidateJson(const std::string& key, const T& defaultValue);


	//StoreTheJson
	void AddJsonToPbALL();
	
	void AddJsonToPb_Battery(Protocol::Battery battery);
	
	void AddJsonToPb_Battery_Pack(Protocol::Battery_Pack battery_pack);
	
	void AddJsonToPb_BAT_MODULE_0(Protocol::BAT_MODULE_0 bat_module_0);
	
	void AddJsonToPb_BAT_MODULE_1(Protocol::BAT_MODULE_1 bat_module_1);
	
	void AddJsonToPb_BAT_MODULE_2(Protocol::BAT_MODULE_2 bat_module_2);
	
	void AddJsonToPb_BAT_MODULE_3(Protocol::BAT_MODULE_3 bat_module_3);
	
	void AddJsonToPb_Environment(Protocol::Environment environment);
	
	void AddJsonToPb_AIS(Protocol::AIS ais);
	
	void AddJsonToPb_System_Time(Protocol::System_Time system_time);
	
	void AddJsonToPb_MOTOR(Protocol::MOTOR motor);
	
	void AddJsonToPb_INVERTER(Protocol::INVERTER inverter);
	

	std::wstring stringToWString(const std::string& str);


	//nlohmann::json ParseJsonFromBuffer(BYTE* buffer, int32 len);


	//Send to Database
	void SendAllToDb();
	
	void EDT0001_Battery_ToDb(Protocol::Battery battery);
	
	void EDT0001_Battery_Pack_ToDb(Protocol::Battery_Pack battery_pack);
	
	void EDT0001_BAT_MODULE_0_ToDb(Protocol::BAT_MODULE_0 bat_module_0);
	
	void EDT0001_BAT_MODULE_1_ToDb(Protocol::BAT_MODULE_1 bat_module_1);
	
	void EDT0001_BAT_MODULE_2_ToDb(Protocol::BAT_MODULE_2 bat_module_2);
	
	void EDT0001_BAT_MODULE_3_ToDb(Protocol::BAT_MODULE_3 bat_module_3);
	
	void EDT0001_Environment_ToDb(Protocol::Environment environment);
	
	void EDT0001_AIS_ToDb(Protocol::AIS ais);
	
	void EDT0001_System_Time_ToDb(Protocol::System_Time system_time);
	
	void EDT0001_MOTOR_ToDb(Protocol::MOTOR motor);
	
	void EDT0001_INVERTER_ToDb(Protocol::INVERTER inverter);
	

	//SendProtoData
	//void SendBatteryTo();
	//void SendTableTo();

private:
	BYTE* _buffer;
	int32 _bufferLen;
	std::string _str;
	nlohmann::json _EdtJson;

	const int32 DEFAULT_INT = 0.0;
	const float DEFAULT_FLOAT = 0.0f;
	const string DEFAULT_STRING = "";

public:

	Protocol::Battery _battery;
	Protocol::Battery_Pack _battery_pack;
	Protocol::BAT_MODULE_0 _bat_module_0;
	Protocol::BAT_MODULE_1 _bat_module_1;
	Protocol::BAT_MODULE_2 _bat_module_2;
	Protocol::BAT_MODULE_3 _bat_module_3;
	Protocol::Environment _environment;
	Protocol::AIS _ais;
	Protocol::System_Time _system_time;
	Protocol::MOTOR _motor;
	Protocol::INVERTER _inverter;
};

//struct 정의
