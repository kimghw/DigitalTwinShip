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
	serverConf conf; 
	JsonToConf::Init("serverconfig.json", conf);

	//TODO : DBConnectionPool 초기화
	ASSERT_CRASH(GDBConnectionPool->Connect(1, L"Driver={ODBC Driver 18 for SQL Server};Server=tcp:krdigitaltwindbserver.database.windows.net,1433;Database=digitaltwindb;Uid=digitaltwin;Pwd=ship0909$;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;"));

	// Create Table

	{
		auto query = L"DROP TABLE IF EXISTS [dbo].[Gold];"
			L"CREATE TABLE [dbo].[Gold]"
			L"("
			L"[id] INT NOT NULL PRIMARY KEY IDENTITY,"
			L"[gold] INT NULL"
			L");";
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