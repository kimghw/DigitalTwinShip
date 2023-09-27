#include "pch.h"
#include "DBConnection.h"




bool DBConnection::Connect(SQLHENV henv, const WCHAR* connectionString)
{
	// Connection to the database with both the environment and the connection handle.
	if (::SQLAllocHandle(SQL_HANDLE_DBC, henv, &_connection) != SQL_SUCCESS)
		return false;
	
	WCHAR stringBuffer[MAX_PATH] = { 0 };
	//size_t len = ::wcslen(connectionString);

	//::wcscpy_s의 두번째 인자는 대상버퍼(원본버퍼가 아닌)의 크기를 나타냄
	::wcscpy_s(stringBuffer, MAX_PATH, connectionString);
	WCHAR resultString[MAX_PATH] = {0};
	SQLSMALLINT resultStringLen = 0;

	SQLRETURN ret = ::SQLDriverConnectW(
		_connection,
		NULL,
		reinterpret_cast<SQLWCHAR*>(stringBuffer),
		_countof(stringBuffer),
		OUT reinterpret_cast<SQLWCHAR*>(resultString),
		_countof(resultString),
		OUT & resultStringLen,
		SQL_DRIVER_NOPROMPT
	);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		std::wcout << L"Successfully connected to the database" << std::endl;
	else 
		std::wcout << L"Failed to connect the the database" << std::endl;


	// Define a statement handle of the database.
	if (::SQLAllocHandle(SQL_HANDLE_STMT, _connection, &_statement) != SQL_SUCCESS)
		return false;

	return (ret == SQL_SUCCESS || ret + SQL_SUCCESS_WITH_INFO);
	

}

void DBConnection::Clear()
{
	if (_connection != SQL_NULL_HANDLE)
	{
		::SQLFreeHandle(SQL_HANDLE_DBC, _connection);
		_connection = SQL_NULL_HANDLE;
	}
	if (_statement != SQL_NULL_HANDLE)
	{
		::SQLFreeHandle(SQL_HANDLE_DBC, _statement);
		_statement = SQL_NULL_HANDLE;
	}

}


// This function is important
bool DBConnection::Execute(const WCHAR* query)
{
	

	try
	{
		SQLRETURN ret = ::SQLExecDirectW(_statement, (SQLWCHAR*)query, SQL_NTSL);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			return true;

		HandleError(ret);
		return false;

	}
	catch (const std::exception& e)
	{
		std::wcerr << L"Exception: " << e.what() << std::endl;

	}




}

bool DBConnection::Fetch()
{ 
	SQLRETURN ret = ::SQLFetch(_statement);

	switch (ret)
	{
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:
		return true;
	case SQL_NO_DATA:
		return false;
	case SQL_ERROR:
		HandleError(ret);
		return false;

	default:
		break;
	}
}

int32 DBConnection::GetRowCount()
{
	SQLLEN count = 0;
	SQLRETURN ret = ::SQLRowCount(_statement, OUT & count);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		return static_cast<int32>(count);

	}

void DBConnection::Unbind()
{
	::SQLFreeStmt(_statement, SQL_UNBIND);
	::SQLFreeStmt(_statement, SQL_RESET_PARAMS);
	::SQLFreeStmt(_statement, SQL_CLOSE);

}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, SQLSMALLINT cType, SQLSMALLINT sqlType, SQLULEN len, SQLPOINTER ptr, SQLLEN* index)
{
	SQLRETURN ret = ::SQLBindParameter(_statement, paramIndex, SQL_PARAM_INPUT, cType, sqlType, len, 0, ptr, 0, index);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		HandleError(ret);
	}

	return true;
}
// C데이터형식 식별자 : SQL_C_TINYINT, SQL 형식 : SQL_TINYINT
bool DBConnection::BindParam(SQLUSMALLINT paramIndex, int8* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, size32(bool), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, int16* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, size32(bool), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, int32* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, size32(bool), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, int64* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, size32(bool), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, float* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, size32(bool), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, double* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, size32(bool), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, bool* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, size32(bool), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, BYTE* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, size32(bool), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, WCHAR** string, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, size32(bool), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, TIMESTAMP_STRUCT* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, size32(bool), value, index);
}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, SQLSMALLINT cType, SQLULEN len, SQLPOINTER value, SQLLEN* index)
{
	SQLRETURN ret = ::SQLBindCol(_statement, columnIndex, cType, value, len, index);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		HandleError(ret);
		return false;
	}
	return true;

}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, int8* value, SQLLEN* index)
{

}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, int16* value, SQLLEN* index)
{

}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, int32* value, SQLLEN* index)
{

}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, int64* value, SQLLEN* index)
{

}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, float* value, SQLLEN* index)
{

}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, double* value, SQLLEN* index)
{

}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, bool* value, SQLLEN* index)
{

}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, BYTE* value, SQLLEN* index)
{

}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, WCHAR** string, SQLLEN* index)
{

}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, TIMESTAMP_STRUCT* value, SQLLEN* index)
{

}

void DBConnection::HandleError(SQLRETURN ret)
{
	if (ret == SQL_SUCCESS)
		return;

	SQLSMALLINT index = 1;
	SQLWCHAR sqlState[MAX_PATH] = { 0 };
	SQLINTEGER nativeErr = 0;
	SQLWCHAR errMsg[MAX_PATH] = { 0 };
	SQLSMALLINT msgLen = 0;
	SQLRETURN errorRet = 0;

	while (true)
	{
		errorRet = ::SQLGetDiagRecW(
			SQL_HANDLE_STMT,
			_statement,
			index,
			sqlState,
			OUT & nativeErr,
			errMsg,
			_countof(errMsg),
			OUT & msgLen
		);

		if (errorRet == SQL_NO_DATA)
			break;

		if (errorRet != SQL_SUCCESS && errorRet != SQL_SUCCESS_WITH_INFO)
			break;

		wcout.imbue(locale("kor"));
		wcout << errMsg << endl;
		
	}

}
