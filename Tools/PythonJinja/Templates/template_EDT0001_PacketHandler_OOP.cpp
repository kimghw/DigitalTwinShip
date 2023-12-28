#pragma once
#include "pch.h"
#include "JsonPacketHandler.h"
#include "{{package}}.pb.h"
#include "EDT0001_PacketHandler.h"

const int {{package}}_PacketHandler::DEFAULT_INT = 0;
const float {{package}}_PacketHandler::DEFAULT_FLOAT = 0.0f;
const double {{package}}_PacketHandler::DEFAULT_DOUBLE = 0.0;
const std::string {{package}}_PacketHandler::DEFAULT_STRING = "0";

{{package}}_PacketHandler::{{package}}_PacketHandler(BYTE* buffer, int32 len) : _str(buffer, buffer + len)
{
    SanitizeAndFormatAsJSON(_str);
}

{{package}}_PacketHandler::~{{package}}_PacketHandler()
{
}

void {{package}}_PacketHandler::SanitizeAndFormatAsJSON(std::string& str)
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

void {{package}}_PacketHandler::replaceDegrees(std::string& str)
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

void {{package}}_PacketHandler::AssignBackslashBeforeQuotes(OUT std::string& str)
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

std::wstring {{package}}_PacketHandler::stringToWString(const std::string& str)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    if (len == 0) return L"";  // º¯È¯ ½ÇÆÐ

    std::wstring wstring(len - 1, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstring[0], len);
    return wstring;
}

bool {{package}}_PacketHandler::ParseJsonFromStr()
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
void {{package}}_PacketHandler::ValidateJson(const std::string& key, const T& defaultValue)
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

void {{package}}_PacketHandler::Assign_JsonToPbALL()
{ 
  {% for table in tables-%}
    Assign_JsonToPb_{{table['table_name']}}(_{{table['table_name']|lower}});
  {% endfor-%}
}

//AssignJsonToPb//
{%- for table in tables%}
void {{package}}_PacketHandler::Assign_JsonToPb_{{table['table_name']}}({{package}}::{{table['table_name']}}& {{table['table_name'] | lower}})
{ 
        {%- for column in table['columns'] %}
        {%- if not loop.first%}
            {%- if column.type == 'INT'%}
    ValidateJson<int32>("{{column.name}}", DEFAULT_INT);
    int32 value_{{column.name}} = _EdtJson.at("{{column.name}}");
            {%- elif column.type == 'FLOAT' %}
    ValidateJson<float>("{{column.name}}", DEFAULT_FLOAT);
    float value_{{column.name}} = _EdtJson.at("{{column.name}}");
            {%- elif column.type == 'DOUBLE' %}
    ValidateJson<double>("{{column.name}}", DEFAULT_FLOAT);
    double value_{{column.name}} = _EdtJson.at("{{column.name}}");
            {%- elif column.type == 'NVARCHAR' %}
    ValidateJson<string>("{{column.name}}", DEFAULT_STRING);
    string value_{{column.name}} = _EdtJson.at("{{column.name}}");
            {%- endif%}
    {{table['table_name']|lower}}.set_{{column.name|lower}}(value_{{column.name}});
        {%- endif%}
        {% endfor%}
}
{% endfor%}

{% for table in tables -%}
{{package}}::{{table['table_name']}} {{package}}_PacketHandler::get_{{table['table_name']}}() {return _{{table['table_name']|lower}};}
{% endfor %}


//SendAllToDb//
void {{package}}_PacketHandler::Insert_AllPbToDb()
{
    {%- for table in tables%}
    Insert_{{table['table_name']}}_ToDb(_{{table['table_name'] | lower}});
    {%- endfor%}
}

{% for table in tables%}
void {{package}}_PacketHandler::Insert_{{table['table_name']}}_ToDb({{package}}::{{table['table_name']}} {{table['table_name']|lower}})
{
    auto query = L"INSERT INTO [dbo].[{{table['table_name']}}]"
        L"("
    {%- for column in table['columns'] %}
    {%- if not column.primarykey%}
        L"[{{column.name}}]{{"," if not loop.last else ""}}"
    {%- endif %}
    {%- endfor %}
        L")"
        L"VALUES(
    {%- for column in table['columns'] %}
    {%- if not loop.last -%}
    {{ "?," if loop.revindex > 2 else "" }}
    {%- else -%}
    {{ "?" if loop.revindex > 1 else "?"}}
    {%- endif -%}
    {%- endfor -%}
    );";

    DBConnection* dbConn = GDBConnectionPool->Pop();
    DBBind <{{table['columns']|length - 1}},0> dbBind(*dbConn, query);
    int32 count = 0;

    {%- for column in table['columns'] -%}
    {%- if not column.primarykey %}
    {% if column.type == 'INT' %}
    int32 {{column.name}} = static_cast<int32>({{table['table_name']|lower}}.{{column.name|lower}}());
    dbBind.BindParam(count++, {{column.name}});
    {%- elif column.type == 'FLOAT' %}
    float {{column.name}} = static_cast<float>({{table['table_name']|lower}}.{{column.name | lower}}());
    dbBind.BindParam(count++, {{column.name}});
    {%- elif column.type == 'DOUBLE' %}
    double {{column.name}} = static_cast<double>({{table['table_name']|lower}}.{{column.name|lower}}());
    dbBind.BindParam(count++, {{column.name}});
    {%- elif column.type == 'NVARCHAR' %}
    std::string {{column.name}} = {{table['table_name']|lower}}.{{column.name|lower}}();
    std::wstring w{{column.name}} = stringToWString({{column.name}});
    WCHAR* pw{{column.name}} = const_cast<WCHAR*>(w{{column.name}}.c_str());
    dbBind.BindParam(count++, pw{{column.name}});
    {%- endif %}
    {%- endif %}
    {%- endfor %}
    ASSERT_CRASH(dbBind.Execute());
    GDBConnectionPool->Push(dbConn);
}
{%- endfor %}