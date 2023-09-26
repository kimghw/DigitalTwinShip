#pragma once
#include "DBConnection.h"



class DBConnectionPool
{
public:
	DBConnectionPool();
	~DBConnectionPool();

public:
	bool Connect(int32 connectionCount, const WCHAR* connectionSTring);
	void Clear();

	DBConnection* Pop();
	void Push(DBConnection* connection);

private:
	USE_LOCK;
	SQLHENV _environment = SQL_NULL_HANDLE;
	Vector<DBConnection*> _connections;

};