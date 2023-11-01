#pragma once
#include<sql.h>
#include<sqlext.h>

#define SQLBUFFLENZERO 0
#define SQLDECIZERO  0
#define SQLCOLUSIZEZERO 0

enum
{
	WVARCHAR_MAX = 4000,
	BINARY_MAX = 8000
};

class DBConnection
{


public:
	bool Connect (SQLHENV henv, const WCHAR* connectionString);
	void Clear();

	bool Execute(const WCHAR* query);
	bool Fetch();
	int32 GetRowCount();
	void Unbind();

	SQLLEN SQLINPUTZERO = 0;

	// I would like to creat functions to wrap the SQLBindParameter and SQLBindCol functions by each data types
	// as below.
	bool BindParam(SQLUSMALLINT paramIndex, float* value, SQLLEN* index);	 // float
	bool BindParam(SQLUSMALLINT paramIndex, double* value, SQLLEN* index);	 // double
	bool BindParam(SQLUSMALLINT paramIndex, bool* value, SQLLEN* index);		 // bool
	bool BindParam(SQLUSMALLINT paramIndex, int8* value, SQLLEN* index);		 // int8
	bool BindParam(SQLUSMALLINT paramIndex, int16* value, SQLLEN* index);	 // int16
	bool BindParam(SQLUSMALLINT paramIndex, int32* value, SQLLEN* index);	 // int32
	bool BindParam(SQLUSMALLINT paramIndex, int64* value, SQLLEN* index);	 // int64
	bool BindParam(SQLUSMALLINT paramIndex, int32 size, BYTE* bin,  SQLLEN* index);		 // BYTE
	bool BindParam(SQLUSMALLINT paramIndex, WCHAR* string, SQLLEN* index);	 // WCHAR
	bool BindParam(SQLUSMALLINT paramIndex, TIMESTAMP_STRUCT* value, SQLLEN* index);	 // TIMESTAMP

	
	bool BindCol(SQLUSMALLINT columnIndex, float* value, SQLLEN* index);	 // float
	bool BindCol(SQLUSMALLINT columnIndex, double* value, SQLLEN* index);	 // double
	bool BindCol(SQLUSMALLINT columnIndex, bool* value, SQLLEN* index);		 // bool
	bool BindCol(SQLUSMALLINT columnIndex, int8* value, SQLLEN* index);		 // int8
	bool BindCol(SQLUSMALLINT columnIndex, int16* value, SQLLEN* index);	 // int16
	bool BindCol(SQLUSMALLINT columnIndex, int32* value, SQLLEN* index);	 // int32
	bool BindCol(SQLUSMALLINT columnIndex, int64* value, SQLLEN* index);	 // int64
	bool BindCol(SQLUSMALLINT columnIndex,  BYTE* value, int32 size, SQLLEN* index);		 // BYTE
	bool BindCol(SQLUSMALLINT columnIndex, WCHAR* string, int32 size, SQLLEN* index);	 // WCHAR
	bool BindCol(SQLUSMALLINT columnIndex, TIMESTAMP_STRUCT* value, SQLLEN* index);	 // TIMESTAMP


private:
	bool BindParam(SQLUSMALLINT paramIndex, SQLSMALLINT cType, SQLSMALLINT sqlType, SQLULEN len, SQLPOINTER ptr, SQLLEN* index);
	bool BindCol(SQLUSMALLINT columnIndex, SQLSMALLINT cType, SQLULEN len, SQLPOINTER value, SQLLEN* index);
	void HandleError(SQLRETURN ret);


private:
	SQLHDBC _connection = SQL_NULL_HANDLE; 
	SQLHSTMT _statement = SQL_NULL_HANDLE;
};

