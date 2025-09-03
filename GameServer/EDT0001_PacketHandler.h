#pragma once
#include "DBBind.h"
#include "pch.h"
#include "DBConnectionPool.h"
#include "Protocol.pb.h"
#include "enum.pb.h"


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
	void Assign_JsonToPb_Battery(EDT0001::Battery& battery);
	void Assign_JsonToPb_Battery_Pack(EDT0001::Battery_Pack& battery_pack);
	void Assign_JsonToPb_BAT_MODULE_0(EDT0001::BAT_MODULE_0& bat_module_0);
	void Assign_JsonToPb_BAT_MODULE_1(EDT0001::BAT_MODULE_1& bat_module_1);
	void Assign_JsonToPb_BAT_MODULE_2(EDT0001::BAT_MODULE_2& bat_module_2);
	void Assign_JsonToPb_BAT_MODULE_3(EDT0001::BAT_MODULE_3& bat_module_3);
	void Assign_JsonToPb_Environment(EDT0001::Environment& environment);
	void Assign_JsonToPb_AIS(EDT0001::AIS& ais);
	void Assign_JsonToPb_System_Time(EDT0001::System_Time& system_time);
	void Assign_JsonToPb_MOTOR(EDT0001::MOTOR& motor);
	void Assign_JsonToPb_INVERTER(EDT0001::INVERTER& inverter);
	void Assign_JsonToPb_Network(EDT0001::Network& network);
	void Assign_JsonToPb_SaveAsBytes(EDT0001::SaveAsBytes& saveasbytes);
	

public:
	//Get the value
	EDT0001::Battery get_Battery();
	EDT0001::Battery_Pack get_Battery_Pack();
	EDT0001::BAT_MODULE_0 get_BAT_MODULE_0();
	EDT0001::BAT_MODULE_1 get_BAT_MODULE_1();
	EDT0001::BAT_MODULE_2 get_BAT_MODULE_2();
	EDT0001::BAT_MODULE_3 get_BAT_MODULE_3();
	EDT0001::Environment get_Environment();
	EDT0001::AIS get_AIS();
	EDT0001::System_Time get_System_Time();
	EDT0001::MOTOR get_MOTOR();
	EDT0001::INVERTER get_INVERTER();
	EDT0001::Network get_Network();
	EDT0001::SaveAsBytes get_SaveAsBytes();
	public:
	//Send to Database
	void Insert_AllPbToDb();
	void Insert_Battery_ToDb(EDT0001::Battery battery);
	void Insert_Battery_Pack_ToDb(EDT0001::Battery_Pack battery_pack);
	void Insert_BAT_MODULE_0_ToDb(EDT0001::BAT_MODULE_0 bat_module_0);
	void Insert_BAT_MODULE_1_ToDb(EDT0001::BAT_MODULE_1 bat_module_1);
	void Insert_BAT_MODULE_2_ToDb(EDT0001::BAT_MODULE_2 bat_module_2);
	void Insert_BAT_MODULE_3_ToDb(EDT0001::BAT_MODULE_3 bat_module_3);
	void Insert_Environment_ToDb(EDT0001::Environment environment);
	void Insert_AIS_ToDb(EDT0001::AIS ais);
	void Insert_System_Time_ToDb(EDT0001::System_Time system_time);
	void Insert_MOTOR_ToDb(EDT0001::MOTOR motor);
	void Insert_INVERTER_ToDb(EDT0001::INVERTER inverter);
	void Insert_Network_ToDb(EDT0001::Network network);
	void Insert_SaveAsBytes_ToDb(EDT0001::SaveAsBytes saveasbytes);
	



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

	EDT0001::Battery _battery;
	EDT0001::Battery_Pack _battery_pack;
	EDT0001::BAT_MODULE_0 _bat_module_0;
	EDT0001::BAT_MODULE_1 _bat_module_1;
	EDT0001::BAT_MODULE_2 _bat_module_2;
	EDT0001::BAT_MODULE_3 _bat_module_3;
	EDT0001::Environment _environment;
	EDT0001::AIS _ais;
	EDT0001::System_Time _system_time;
	EDT0001::MOTOR _motor;
	EDT0001::INVERTER _inverter;
	EDT0001::Network _network;
	EDT0001::SaveAsBytes _saveasbytes;
};

//struct 정의
