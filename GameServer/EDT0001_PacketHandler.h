#pragma once
#include "DBBind.h"
#include "pch.h"
#include "DBConnectionPool.h"
#include "EDT0001.pb.h"



class EDT0001_PacketHandler
{
public:
	EDT0001_PacketHandler(BYTE* buffer, int32 len); // 생성자
	~EDT0001_PacketHandler(); // 소멸자

private:
	void SanitizeAndFormatAsJSON(std::string& str);
	void replaceDegrees(std::string& str);
	void AssignBackslashBeforeQuotes(std::string& str);
	bool ParseJsonFromStr();
	std::wstring stringToWString(const std::string& str);

	//Validate the incomming data
	template<typename T>
	void ValidateJson(const std::string& key, const T& defaultValue);

public:
	//StoreTheJsoninProtobuf
	void Assign_JsonToPbALL();
	void Assign_JsonToPb_Battery(Protocol::Battery& battery);
	void Assign_JsonToPb_Battery_Pack(Protocol::Battery_Pack& battery_pack);
	void Assign_JsonToPb_BAT_MODULE_0(Protocol::BAT_MODULE_0& bat_module_0);
	void Assign_JsonToPb_BAT_MODULE_1(Protocol::BAT_MODULE_1& bat_module_1);
	void Assign_JsonToPb_BAT_MODULE_2(Protocol::BAT_MODULE_2& bat_module_2);
	void Assign_JsonToPb_BAT_MODULE_3(Protocol::BAT_MODULE_3& bat_module_3);
	void Assign_JsonToPb_Environment(Protocol::Environment& environment);
	void Assign_JsonToPb_AIS(Protocol::AIS& ais);
	void Assign_JsonToPb_System_Time(Protocol::System_Time& system_time);
	void Assign_JsonToPb_MOTOR(Protocol::MOTOR& motor);
	void Assign_JsonToPb_INVERTER(Protocol::INVERTER& inverter);
	

public:
	//Get the value
	Protocol::Battery get_Battery();
	Protocol::Battery_Pack get_Battery_Pack();
	Protocol::BAT_MODULE_0 get_BAT_MODULE_0();
	Protocol::BAT_MODULE_1 get_BAT_MODULE_1();
	Protocol::BAT_MODULE_2 get_BAT_MODULE_2();
	Protocol::BAT_MODULE_3 get_BAT_MODULE_3();
	Protocol::Environment get_Environment();
	Protocol::AIS get_AIS();
	Protocol::System_Time get_System_Time();
	Protocol::MOTOR get_MOTOR();
	Protocol::INVERTER get_INVERTER();
	public:
	//Send to Database
	void Insert_AllPbToDb();
	void Insert_Battery_ToDb(Protocol::Battery battery);
	void Insert_Battery_Pack_ToDb(Protocol::Battery_Pack battery_pack);
	void Insert_BAT_MODULE_0_ToDb(Protocol::BAT_MODULE_0 bat_module_0);
	void Insert_BAT_MODULE_1_ToDb(Protocol::BAT_MODULE_1 bat_module_1);
	void Insert_BAT_MODULE_2_ToDb(Protocol::BAT_MODULE_2 bat_module_2);
	void Insert_BAT_MODULE_3_ToDb(Protocol::BAT_MODULE_3 bat_module_3);
	void Insert_Environment_ToDb(Protocol::Environment environment);
	void Insert_AIS_ToDb(Protocol::AIS ais);
	void Insert_System_Time_ToDb(Protocol::System_Time system_time);
	void Insert_MOTOR_ToDb(Protocol::MOTOR motor);
	void Insert_INVERTER_ToDb(Protocol::INVERTER inverter);

	void Insert_Insert_ALLPbToDbAsArray();
	



private:
	BYTE* _buffer;
	int32 _bufferLen;
	std::string _str;
	nlohmann::json _EdtJson;

	static const int32 DEFAULT_INT;
	static const float DEFAULT_FLOAT;
	static const double DEFAULT_DOUBLE;
	static const string DEFAULT_STRING;

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
