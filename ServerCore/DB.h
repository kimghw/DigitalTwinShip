#include "pch.h"
#include "DBConnectionPool.h"


class DB
{
public:
	static void Init()
	{
		ASSERT_CRASH(GDBConnectionPool->Connect(1, L"Driver={ODBC Driver 18 for SQL Server};Server=tcp:krdigitaltwindbserver.database.windows.net,1433;Database=digitaltwindb;Uid=digitaltwin;Pwd=ship0909$;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;"));
	
		CheckTable();
	}
	static void CheckTable()
	{
		{
			auto query = L"DROP TABLE IF EXISTS [dbo].[ship_test];"
				L"CREATE TABLE [dbo].[ship_test] "
				L"("
				L"     [SHIP_NUMBER] INT NOT NULL PRIMARY KEY IDENTITY(1,1),"
				L"     [Inverter_output_frequency] FLOAT NULL,"
				L"     [Motor] FLOAT NULL,"
				L"     [Motor_torque] FLOAT NULL,"
				L"     [Motor_temp] FLOAT NULL,"
				L"     [System_time] NVARCHAR(50) NULL"
				L");";


		
			DBConnection* dbConn = GDBConnectionPool->Pop();
			dbConn->Execute(query);
			GDBConnectionPool->Push(dbConn);
			
		}
	}

	



};

