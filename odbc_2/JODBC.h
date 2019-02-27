#pragma once

class JODBC
{
public:
	SQLHENV m_hEnv;
	SQLHENV m_hDbc;
	SQLHENV m_hStmt;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	wstring GetServer();
	bool Set();
	bool Add(const TCHAR* szID, const TCHAR* szPW, const TCHAR* szName);
	bool Delete(const TCHAR* DelName);
	bool Update(const TCHAR* SrcValue, const TCHAR* DescValue);
	bool Check();
public:
	JODBC();
	virtual ~JODBC();
};

