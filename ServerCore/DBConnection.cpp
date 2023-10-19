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
	SQLRETURN ret = ::SQLBindParameter(_statement, paramIndex, SQL_PARAM_INPUT, cType, sqlType, len, SQLDECIZERO, ptr, SQLBUFFLENZERO, index);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		HandleError(ret);
		return false;
	}
	else
		return true;
}

// C데이터형식 식별자 : SQL_C_TINYINT, SQL 형식 : SQL_TINYINT
bool DBConnection::BindParam(SQLUSMALLINT paramIndex, int8* value, SQLLEN* index)
{
	
	return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, static_cast<int32>(3), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, int16* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_SHORT, SQL_SMALLINT, static_cast<int32>(5), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, int32* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_LONG, SQL_INTEGER, static_cast<int32>(10), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, int64* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_SBIGINT, SQL_BIGINT, static_cast<int32>(19), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, float* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_FLOAT, SQL_REAL, static_cast<int32>(15), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, double* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_DOUBLE, SQL_DOUBLE, static_cast<int32>(15), value, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, bool* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_TINYINT, SQL_TINYINT, static_cast<int32>(3), value, index);
}

// image, etc.,
bool DBConnection::BindParam(SQLUSMALLINT paramIndex, int32 size, BYTE* bin,  SQLLEN* index)
{
	// 빈 배열의 경우
	// 1. SQLLEN indptr = SQL_NULL_DATA; 로 설정
	// 2. 매개변수 값에 대한 포인터를 nullptr로 설정
	// 3. 매개변수의 최대 바이트 크기를 0으로 설정
	 
	// 바이트의 경우 index에 바이너리 값을 넣어주네요. 
	if (bin == nullptr)
	{
		*index = SQL_NULL_DATA;
		return BindParam(paramIndex, SQL_C_BINARY, SQL_BINARY, size, nullptr, index);
	}

	SQLSMALLINT sqlType = (size> BINARY_MAX) ? SQL_LONGVARBINARY : SQL_BINARY;
	return BindParam(paramIndex, SQL_C_BINARY, sqlType, size, (SQLPOINTER)bin, index);

	//if (size > BINARY_MAX)
	//	return BindParam(paramIndex, SQL_C_BINARY, SQL_LONGVARBINARY, size, (SQLPOINTER)bin, index);
	//else
	//	return BindParam(paramIndex, SQL_C_BINARY, SQL_BINARY, size, (SQLPOINTER)bin, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, WCHAR* string, SQLLEN* index)
{
	// Calculate the size of the string
	SQLULEN size = 0;
	*index = SQL_NTSL;

	if (string == nullptr)
		size = 0;
	else
		size = static_cast<SQLULEN>((::wcslen(string) + 1) * sizeof(WCHAR));
	
	if (size > WVARCHAR_MAX)
		return BindParam(paramIndex, SQL_C_WCHAR, SQL_WLONGVARCHAR, size, (SQLPOINTER)string, index);
	else
		return BindParam(paramIndex, SQL_C_WCHAR, SQL_WVARCHAR, size, (SQLPOINTER)string, index);
}

bool DBConnection::BindParam(SQLUSMALLINT paramIndex, TIMESTAMP_STRUCT* value, SQLLEN* index)
{
	return BindParam(paramIndex, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, size32(TIMESTAMP_STRUCT), value, index);
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

// In case of variable length, Buffer length should be set in the API 
bool DBConnection::BindCol(SQLUSMALLINT columnIndex, float* value, SQLLEN* index)
{
	return DBConnection::BindCol( columnIndex, SQL_C_FLOAT, size32(float), value, index);
}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, double* value, SQLLEN* index)
{
	return DBConnection::BindCol(columnIndex, SQL_C_DOUBLE, size32(double), value, index);
}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, bool* value, SQLLEN* index)
{
	return DBConnection::BindCol(columnIndex, SQL_C_TINYINT, size32(bool), value, index);
}
bool DBConnection::BindCol(SQLUSMALLINT columnIndex, int8* value, SQLLEN* index)
{
	return DBConnection::BindCol(columnIndex, SQL_C_TINYINT, size32(int8), value, index);
}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, int16* value, SQLLEN* index)
{
	return DBConnection::BindCol(columnIndex, SQL_C_SHORT, size32(int16), value, index);
}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, int32* value, SQLLEN* index)
{
	return DBConnection::BindCol(columnIndex, SQL_C_LONG, size32(int32), value, index);
}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, int64* value, SQLLEN* index)
{
	return DBConnection::BindCol(columnIndex, SQL_C_SBIGINT, size32(int64), value, index);
}

//  BYTE
bool DBConnection::BindCol(SQLUSMALLINT columnIndex,  BYTE* bin, int32 size, SQLLEN* index)
{
	if (bin == nullptr)
		return BindCol(columnIndex, SQL_C_BINARY, SQLBUFFLENZERO, nullptr, index);
	else
		return BindCol(columnIndex, SQL_C_BINARY, size, (SQLPOINTER)bin, index);
}   

// WCHAR 
bool DBConnection::BindCol(SQLUSMALLINT columnIndex, WCHAR* string, int32 size, SQLLEN* index)
{

	return BindCol(columnIndex, SQL_C_WCHAR, size, (SQLPOINTER)string, index);
}

bool DBConnection::BindCol(SQLUSMALLINT columnIndex, TIMESTAMP_STRUCT* value, SQLLEN* index)
{
	return DBConnection::BindCol(columnIndex, SQL_C_TYPE_TIMESTAMP, size32(TIMESTAMP_STRUCT), value, index);
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
