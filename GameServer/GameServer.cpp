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
		this_thread::sleep_for(10s);
	}

	GThreadManager->Join();
}