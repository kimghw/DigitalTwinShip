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
			auto query = L"DROP TABLE IF EXISTS [dbo].[ship_test_ver1];"
				L"CREATE TABLE [dbo].[ship_test_ver1] "
				L"("
				L"     [01_INV_PHASE_A_CURRENT] INT NULL,"
				L"     [02_INV_PHASE_B_CURRENT] INT NULL,"
				L"     [03_INV_PHASE_C_CURRENT] INT NULL,"
				L"     [04_INV_POST_FAULT] FLOAT NULL,"
				L"     [05_INV_RUN_FAULT] FLOAT NULL,"
				L"     [06_INV_GATE_DRIVER_BOARD_TEMP] INT NULL,"
				L"     [07_INV_MODULE_A_TEMP] INT NULL,"
				L"     [08_INV_MODULE_B_TEMP] INT NULL,"
				L"     [09_INV_MODULE_C_TEMP] INT NULL,"
				L"     [10_INV_POWER] INT NULL,"
				L"     [11_INV_OUTPUT_VOLTAGE] INT NULL,"
				L"     [12_MT_RPM] INT NULL,"
				L"     [13_MT_TORQUE] INT NULL,"
				L"     [14_MT_TEMP] INT NULL,"
				L"     [15_Wind_speed] INT NULL,"
				L"     [16_Wind_direction] INT NULL,"
				L"     [17_latitude] NVARCHAR(100) NULL,"
				L"     [18_longtitude] NVARCHAR(100) NULL,"
				L"     [19_System-time] NVARCHAR(100) NULL,"
				L");";


		
			DBConnection* dbConn = GDBConnectionPool->Pop();
			dbConn->Execute(query);
			GDBConnectionPool->Push(dbConn);
			
		}
	}

	



};

