#pragma once
#include "DBBind.h"
#include "pch.h"
#include "DBConnectionPool.h"

void replaceDegrees(std::string& coord);
void addBackslashBeforeQuotes(OUT std::string& input);
void MakeJsonString(std::string& str);
bool StringToJson(std::string& str, OUT nlohmann::json& jsonInput);
bool SendJsonToDb(nlohmann::json& jsonInput);
std::wstring stringToWString(const std::string& str);

class JsonPacketHandler
{
};

