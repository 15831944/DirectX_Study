#pragma once
#include "JStd.h"
class JSQLServer
{
public:
	SQLHENV m_hEnv;
	SQLHENV m_hDbc;
	SQLHENV m_hStmt;
public:
	bool Release();
public:
	bool Set();
	bool Add(const SQLVARCHAR* szID, const SQLVARCHAR* szPW, const SQLVARCHAR* szName);
	bool Delete(const TCHAR* DelName);
	bool Update(const TCHAR* SrcValue, const TCHAR* DescValue);
	bool Check();
public:
	JSQLServer();
	virtual ~JSQLServer();
};

