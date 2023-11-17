#pragma once
#include "DBBind.h"
#include "pch.h"
#include "DBConnectionPool.h"
#include "Protocol.pb.h"


class {{Ship_num}}_PacketHandler
{
public:
	{{Ship_num}}_PacketHandler(BYTE* buffer, int32 len); // 생성자
	~{{Ship_num}}_PacketHandler(); // 소멸자

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
	{% for table in tables-%}
	void Assign_JsonToPb_{{table['table_name']}}(Protocol::{{table['table_name']}}& {{table['table_name']|lower}});
	{% endfor%}

public:
	//Get the value
	{% for table in tables -%}
	Protocol::{{table['table_name']}} get_{{table['table_name']}}();
	{% endfor -%}

public:
	//Send to Database
	void Insert_AllPbToDb();
	{% for table in tables-%}
	void Insert_{{table['table_name']}}_ToDb(Protocol::{{table['table_name']}} {{table['table_name']|lower}});
	{% endfor%}



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
{% for table in tables%}
	Protocol::{{table['table_name']}} _{{table['table_name']|lower}};
{%- endfor%}
};

//struct 정의

