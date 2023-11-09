#pragma once
#include "pch.h"
#include "DBConnectionPool.h"
#include "nlohmann/json.hpp"

class MakeTableQuery
{
public:

	static void Init()
	{
		std::vector<std::wstring> createTableQueries;
		std::string schemaFileName = "DbSchema.json";

		ASSERT_CRASH(GDBConnectionPool->Connect(1, L"Driver={ODBC Driver 18 for SQL Server};Server=tcp:krdigitaltwindbserver.database.windows.net,1433;Database=digitaltwindb;Uid=digitaltwin;Pwd=ship0909$;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;"));
		MakeTableQueriesFromJson(OUT createTableQueries, schemaFileName);

	}

	static void MakeTableQueriesFromJson(std::vector<std::wstring>& createTableQueries, std::string& fileName)
	{
		//validate filename
		MakeJsonstrfromfile(fileName);
	}

	static void MakeJsonstrfromfile(std::string& schemaFileName)
	{
		nlohmann::json jconfig;

		// json 파일 읽기
		std::ifstream inputfile(schemaFileName);
		cout << "S1" << endl;
		if (!inputfile.is_open())
			throw std::runtime_error("Failed to open the Json file");

		cout << "S2" << endl;
		try{ inputfile >> jconfig;}
		catch (const std::exception& e){std::cerr << "runtime error : " << e.what() << std::endl;}
		cout << "S3" << endl;
		MakeTableQueryFromJson(jconfig);
		cout << "S4" << endl;
	}

	static void MakeTableQueryFromJson(nlohmann::json jconfig)
	{
		for (const auto& table : jconfig["tables"])
		{
			cout << "S5" << endl;
			std::string createQuery = "DROP TABLE IF EXISTS " + table["table_name"].get<std::string>() + " ;";
			createQuery += "CREATE TABLE " + table["table_name"].get<std::string>() + " (";
			for (const auto& col : table["columns"])
			{
				createQuery += col["name"].get<std::string>() + " "
					+ col["type"].get<std::string>();
				if (col["type"] == "NVARCHAR")
					createQuery += "(" + std::to_string(col["size"].get<int>()) + ")";

				if (col.contains("primarykey") && !col["primarykey"].is_null())
				{
					createQuery += " NOT NULL ";
					createQuery += col["primarykey"].get<std::string>();
				}
				else
					createQuery += col["nullable"].get<bool>() ? " NULL," : " NOT NULL,";
			}
			createQuery.pop_back();
			createQuery += ");";
			std::wstring wcreateQuery = JsonToConf::stringToWString(createQuery);
			//std::cout << createQuery << endl;
			CheckAndMakeTable(wcreateQuery.c_str());
			//createTableQueries.push_back(wcreateQuer);
			cout << "success for checking the tables" << endl;
		}
	}

	static void CheckAndMakeTable(const wchar_t* wcreateQuery)
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();
		dbConn->Execute(wcreateQuery);
		GDBConnectionPool->Push(dbConn);
	}
};



