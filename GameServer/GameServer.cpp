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
#include "MakeTableQuery.h"
#include "MRSchema.pb.h"
#include "EDT0001.pb.h"
#include "enum.pb.h"

int main()
{
	//Initial value is internal loop back ip
	ServerIpInfo conf = { L"127.0.0.1", 6340, 10 };

	ServerConf::Init("ServerConfig.json", conf);
	MakeTableQuery::Init();

 	ClientPacketHandler::Init();

	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(conf.ip, conf.port),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>, // TODO : SessionManager 등
		conf.maxSessionCount);
	
	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 10; i++)
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

//string strLat = _EdtJson.at("latitude");
//float value_latitude = dmsStrToDd(strLat);
////ValidateJson<float>("latitude", DEFAULT_FLOAT);
////float value_latitude = _EdtJson.at("latitude");
//ais.set_latitude(value_latitude);
//
//string strLon = _EdtJson.at("longitude");
//float value_longitude = dmsStrToDd(strLon);
////ValidateJson<float>("longitude", DEFAULT_FLOAT);
////float value_longitude = _EdtJson.at("longitude");
//ais.set_longitude(value_longitude);