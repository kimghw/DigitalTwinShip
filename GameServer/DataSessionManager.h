#pragma once

class DataSession;

using DataSessionRef = shared_ptr<DataSession>;

class DataSessionManager
{
public:
	void Add(DataSessionRef session);
	void Remove(DataSessionRef session);
	void Broadcast(SendBufferRef sendBuffer);

	set<DataSessionRef> GetAllSession();
private:
	USE_LOCK;
	set<DataSessionRef> _sessions;

};

extern DataSessionManager GSessionManager;

