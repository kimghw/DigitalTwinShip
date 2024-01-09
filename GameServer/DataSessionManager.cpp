#include "pch.h"
#include "DataSessionManager.h"
#include "DataSession.h"



DataSessionManager GSessionManager;

void DataSessionManager::Add(DataSessionRef session)
{
	WRITE_LOCK;
	_sessions.insert(session);
}

void DataSessionManager::Remove(DataSessionRef session)
{
	WRITE_LOCK;
	_sessions.erase(session);
}

void DataSessionManager::Broadcast(SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	for (DataSessionRef session : _sessions)
	{
		session->Send(sendBuffer);
	}
}

set<DataSessionRef> DataSessionManager::GetAllSession()
{
	return _sessions;
}
