#pragma once
#include "DBConnection.h"

template<int32 C>
struct FullBits { enum {value = (1 << (C-1)) | FullBits<C-1>::value }; };

template<>
struct FullBits<1> { enum {value = 1}; };

template<>
struct FullBits<0> { enum {value = 0}; };

template<int32 ParamCount, int32 ColumnCount>
class DBBind
{
public:
	DBBind(DBConnection& dbConnection, const WCHAR* query)
		: _dbConnection(dbConnection), _query(query)
	{
		memset(_paramIndex, 0, sizeof(_paramIndex));
		memset(_columnIndex, 0, sizeof(_columnIndex));
		_paramFlag = 0;
		_columnFlag = 0;
		dbConnection.Unbind();
	}
	 
	bool Validate() 
	{
		return _paramFlag == FullBits<ParamCount>::value && _columnFlag == FullBits<ColumnCount>::value;
	}

	bool Execute() 
	{
		//ASSERT_CRASH(Validate());
		return _dbConnection.Execute(_query	);

	}

	bool Fetch() 
	{
		return _dbConnection.Fetch();
	}

public:

	//정수, 실수
	template<typename T>
	void BindParam(int32 idx, T& value)
	{
		_dbConnection.BindParam(idx+1, &value, &_paramIndex[idx]);
		_paramFlag |= (1LL << idx);
	}


	//문자열
	void BindParam(int32 idx, WCHAR* value)
	{
		_dbConnection.BindParam(idx + 1, value, &_paramIndex[idx]);
		_paramFlag |= (1LL << idx);
	}

	//배열
	template<typename T, int32 N>
	void BindParam(int32 idx, T(&value)[N])
	{
		_dbConnection.BindParam(idx+1,  size32(T) * N, (BYTE*)value, &_paramIndex[idx]);
		_paramFlag |= (1LL << idx);
	}

	// 데이터 여러개
	template<typename T>
	void BindParam(int32 idx, T* value, int32 N)
	{
		_dbConnection.BindParam(idx + 1,  size32(T) * N, (BYTE*)value, &_paramIndex[idx]);
		_paramFlag |= (1LL << idx);
	}

	// BindCol
	template<typename T>
	void BindCol(int32 idx, OUT T& value)
	{
		_dbConnection.BindCol(idx + 1, OUT &value, &_columnIndex[idx]);
		_columnFlag |= (1LL << idx);
	}

	// BYTE 배열
	template<typename T, int32 N>
	void BindCol(int32 idx, OUT T(&value)[N])
	{
		// BindCol 배열의 숫자를 입력으로 받음
		_dbConnection.BindCol(idx +1, value, size32(T) * N,   &_columnIndex[idx]);
		_columnFlag |= (1LL << idx);
	}

	// WCHAR 배열
	// 컴파일 타임에 배열의 크기를 정함
	template<int32 N>
	void BindCol(int32 idx, OUT WCHAR(&value)[N])
	{
		_dbConnection.BindCol(idx + 1, value, size32(WCHAR)*(N-1), &_columnIndex[idx]);
		_columnFlag |= (1LL << idx);
	}

	// WCHAR 문자열
	// 런타임에 배열의 크기를 저장
	void BindCol(int32 idx, WCHAR* value, int32 len)
	{
		_dbConnection.BindCol(idx + 1, value, size32(WCHAR)*(len - 1), &_columnIndex[idx]);
		_columnFlag |= (1LL << idx);
	}

	// 데이터 여러개


protected:
	DBConnection&	_dbConnection;
	const WCHAR*	_query;
	SQLLEN			_paramIndex[ParamCount > 0 ? ParamCount : 1 ];
	SQLLEN			_columnIndex[ColumnCount > 0 ? ColumnCount : 1];
	uint64			_paramFlag;
	uint64			_columnFlag;
	
};


