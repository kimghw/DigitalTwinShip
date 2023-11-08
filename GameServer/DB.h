#include "pch.h"
#include "DBConnectionPool.h"


class DB
{
public:

	static void Init()
	{
		std::vector<std::wstring> createTableQueries;

		std::string schemaFileName = "DBschema.json";

		ASSERT_CRASH(GDBConnectionPool->Connect(1, L"Driver={ODBC Driver 18 for SQL Server};Server=tcp:krdigitaltwindbserver.database.windows.net,1433;Database=digitaltwindb;Uid=digitaltwin;Pwd=ship0909$;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;"));
		MakeTableQueriesFromJson(OUT createTableQueries, schemaFileName);
		//CheckTable();
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
		if (!inputfile.is_open())
			throw std::runtime_error("Failed to open the Json file");

		try
		{
			inputfile >> jconfig;
		}
		catch (const std::exception& e)
		{
			std::cerr << "runtime error : " << e.what() << std::endl;
		}

		MakeTableQueryFromJson(jconfig);
	}

	static void MakeTableQueryFromJson(nlohmann::json jconfig)
	{
		for (const auto& table : jconfig["tables"])
		{
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
				{
					createQuery += col["nullable"].get<bool>() ? " NULL," : " NOT NULL,";
				}

			}
			createQuery.pop_back();
			createQuery += ");";
			std::wstring wcreateQuery = JsonToConf::stringToWString(createQuery);
			std::cout << createQuery << endl;
			CheckAndMakeTable(wcreateQuery.c_str());
			//createTableQueries.push_back(wcreateQuer);
		}
	}

	static void CheckAndMakeTable(const wchar_t* wcreateQuery)
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();
		dbConn->Execute(wcreateQuery);
		GDBConnectionPool->Push(dbConn);
		cout << "success for Execute" << endl;
	}

	//static void CheckTable()
	//{
	//	{
	//		auto query = L"DROP TABLE IF EXISTS [dbo].[ship_test_ver1];"
	//			L"CREATE TABLE [dbo].[ship_test_ver1] "
	//			L"("
	//			L"     [SHIP_NUMBER] INT NOT NULL PRIMARY KEY IDENTITY(1,1),"
	//			L"     [INV_PHASE_A_CURRENT] INT NULL,"
	//			L"     [INV_PHASE_B_CURRENT] INT NULL ,"
	//			L"     [INV_PHASE_C_CURRENT] INT NULL,"
	//			L"     [INV_POST_FAULT] float NULL,"
	//			L"     [INV_RUN_FAULT] float NULL,"
	//			L"     [INV_GATE_DRIVER_BOARD_TEMP] INT NULL,"
	//			L"     [INV_MODULE_A_TEMP] INT NULL,"
	//			L"     [INV_MODULE_B_TEMP] INT NULL,"
	//			L"     [INV_MODULE_C_TEMP] INT NULL,"
	//			L"     [INV_POWER] INT NULL,"
	//			L"     [INV_OUTPUT_VOLTAGE] INT NULL,"
	//			L"     [MT_RPM] INT NULL,"
	//			L"     [MT_TORQUE] INT NULL,"
	//			L"     [MT_TEMP] INT NULL,"
	//			L"     [Wind_speed] INT NULL,"
	//			L"     [Wind_direction] INT NULL,"
	//			L"     [latitude] NVARCHAR(100) NULL,"
	//			L"     [longitude] NVARCHAR(100) NULL,"
	//			L"     [System_time] NVARCHAR(100) NULL,"
	//			L");";

	//	
	//		DBConnection* dbConn = GDBConnectionPool->Pop();
	//		dbConn->Execute(query);
	//		GDBConnectionPool->Push(dbConn);
	//		
	//	}
	//}

	



};



