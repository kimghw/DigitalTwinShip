#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "BufferWriter.h"
#include "ClientPacketHandler.h"
#include <tchar.h>
#include "DBConnectionPool.h"


int main()
{
	serverConf conf; JsonToConf::Init("serverconfig.json", conf);

	//TODO : DBConnectionPool 초기화
	ASSERT_CRASH(GDBConnectionPool->Connect(1, L"Driver={ODBC Driver 18 for SQL Server};Server=tcp:krdigitaltwindbserver.database.windows.net,1433;Database=digitaltwindb;Uid=digitaltwin;Pwd=ship0909$;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;"));

	// Create Table

	{
		auto query = L"DROP TABLE IF EXISTS [dbo].[Gold];"
			L"CREATE TABLE [dbo].[Gold] ("
			L"    [id] INT NOT NULL PRIMARY KEY IDENTITY,"
			L"    [gold] INT NULL"
			L");";

		DBConnection* dbConn = GDBConnectionPool->Pop();
		ASSERT_CRASH(dbConn->Execute(query));
		GDBConnectionPool->Push(dbConn);
	}

	// Add Data
	for (size_t i = 0; i < 3; i++)
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();

		// 기존 바인딩된 정보 날리기
		dbConn->Unbind(); 

		// 바인딩할 파라미터
		int32 gold = 1000;
		SQLLEN len = 0;

		// 바인딩
		ASSERT_CRASH(dbConn->BindParam(1, SQL_C_LONG, SQL_INTEGER, sizeof(gold), &gold, &len));

		// 쿼리 실행
		ASSERT_CRASH(dbConn->Execute(L"INSERT INTO [dbo].[Gold] ([gold]) VALUES (?)"));
		GDBConnectionPool->Push(dbConn);
	}

	// Read
	{
		DBConnection* dbConn = GDBConnectionPool->Pop();
		dbConn->Unbind();

		// Read 할 떄도 바인딩할 수 있음(실행문의 플레이스 홀더)
		int32 gold = 1000;
		SQLLEN len = 0;
		// 바인딩
		ASSERT_CRASH(dbConn->BindParam(1, SQL_C_LONG, SQL_INTEGER, sizeof(gold), &gold, &len));


		int32 outId = 0;
		SQLLEN outIdLen = 0;
		ASSERT_CRASH(dbConn->BindCol(1, SQL_C_LONG, sizeof(outId), &outId, &outIdLen));


		int32 outGold = 0;
		SQLLEN outGoldLen = 0;
		ASSERT_CRASH(dbConn->BindCol(2, SQL_C_LONG, sizeof(outGold), &outGold, &outGoldLen));

		// 쿼리 실행
		// 데이터를 여러개 반환할 수도 있음
		ASSERT_CRASH(dbConn->Execute(L"SELECT id, gold FROM [dbo].[Gold] WHERE gold = (?)"));


		while (dbConn->Fetch())
		{
			cout << "id : " << outId << " gold : " << outGold << endl;
		}
		GDBConnectionPool->Push(dbConn);
	}

 	ClientPacketHandler::Init();

	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(conf.ip, conf.port),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>, // TODO : SessionManager 등
		conf.maxSessionCount);
	

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}				
			});
	}	


	while (true)
	{
		cout << "Server is running..." << endl;
		this_thread::sleep_for(25ms);
	}

	GThreadManager->Join();
}