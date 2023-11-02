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
#include "DBBind.h"
#include "DB.h"


int main()
{
	serverConf conf; JsonToConf::Init("serverconfig.json", conf);
	DB::Init();


	//	//// 바인딩할 파라미터
	//	//int32 gold = 1000;
	//	//SQLLEN len = 0;

	//	//WCHAR name[100] = L"Geohwa";
	//	//SQLLEN nameLen = 0;

	//	//TIMESTAMP_STRUCT ts = { };
	//	//ts.year = 2023;
	//	//ts.month = 10;
	//	//ts.day = 12;
	//	//SQLLEN tsLen = 0;	

	//	//// 바인딩
	//	//ASSERT_CRASH(dbConn->BindParam(1, &gold, &len));
	//	//ASSERT_CRASH(dbConn->BindParam(2, name, &nameLen));
	//	//ASSERT_CRASH(dbConn->BindParam(3, &ts, &tsLen));

	//	//// 쿼리 실행
	//	//auto query = L"INSERT INTO [dbo].[Gold] ([gold], [name], [createDate]) VALUES (?,?,?)";
	//	//ASSERT_CRASH(dbConn->Execute(query));
	//	GDBConnectionPool->Push(dbConn);
	//}

	//// Read
	//{
	//	DBConnection* dbConn = GDBConnectionPool->Pop();
	//	auto query = L"SELECT id, gold, name, createDate FROM [dbo].[test] WHERE gold = (?)";
	//	DBBind<1, 4> dbBind(*dbConn, query);

	//	int32 gold = 100;
	//	dbBind.BindParam(0, gold);

	//	//struct test {
	//	//	int32 outId = 0;
	//	//	int32 outGold = 0;
	//	//	WCHAR outName[100] = { };
	//	//	TIMESTAMP_STRUCT outDate = { };
	//	//} test1;

	//	int32 outId = 0;
	//	int32 outGold = 0;
	//	WCHAR outName[100] = { };
	//	TIMESTAMP_STRUCT outDate = { };

	//	dbBind.BindCol(0, OUT outId);
	//	dbBind.BindCol(1, OUT outGold);
	//	dbBind.BindCol(2, OUT outName);
	//	dbBind.BindCol(3, OUT outDate);

	//	ASSERT_CRASH(dbBind.Execute());


	//	
	//	//dbConn->Unbind();



	//	//// Read 할 떄도 바인딩할 수 있음(실행문의 플레이스 홀더)
	//	//int32 gold = 1000;
	//	//SQLLEN len = 0;
	//	//// 바인딩
	//	//ASSERT_CRASH(dbConn->BindParam(1, &gold, &len));


	//	//int32 outId = 0;
	//	//SQLLEN outIdLen = 0; 
	//	//ASSERT_CRASH(dbConn->BindCol(1, &outId, &outIdLen));


	//	//int32 outGold = 0;
	//	//SQLLEN outGoldLen = 0;
	//	//ASSERT_CRASH(dbConn->BindCol(2, &outGold, &outGoldLen));    

	//	//WCHAR outName[100];
	//	//SQLLEN outNameLen = 0;
	//	//ASSERT_CRASH(dbConn->BindCol(3, outName, 100*sizeof(WCHAR), &outNameLen));

	//	//wcout<< 100 * sizeof(WCHAR) << endl;
	//	//
	//	//TIMESTAMP_STRUCT   outDate = { };
	//	//SQLLEN outDateLen = 0;
	//	//ASSERT_CRASH(dbConn->BindCol(4, &outDate, &outDateLen));

	//	//// 쿼리 실행
	//	//// 데이터를 여러개 반환할 수도 있음
	//	//ASSERT_CRASH(dbConn->Execute(L"SELECT id, gold, name, createDate FROM [dbo].[Gold] WHERE gold = (?)"));


	//	while (dbConn->Fetch())
	//	{
	//		wcout << "id : " << outId << " gold : " << outGold << "Name:" << outName << endl;
	//		wcout << "Date : " << outDate.year << "-" << outDate.month << "-" << outDate.day << endl;
	//	}
	//	GDBConnectionPool->Push(dbConn);
	//}



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
		wcout << "Server is running..." << endl;
		this_thread::sleep_for(1s);
	}

	GThreadManager->Join();
}