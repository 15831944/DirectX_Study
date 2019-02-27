#pragma once
#include "JServerStd.h"
class JDataBase : public JSingleton<JDataBase>
{
private:
	friend class JSingleton<JDataBase>;
public:
	SQLHENV m_hEnv;
	SQLHENV m_hDbc;
	SQLHENV m_hStmt;
public:
	bool Init();
	bool Release();
public:
	bool Add(const TCHAR* szID, const TCHAR* szPW, const TCHAR* szName);
	bool Del(const TCHAR* DelName);
	bool Check();
	bool Update(const TCHAR* SrcValue, const TCHAR* DescValue);
public:
	JDataBase();
	virtual ~JDataBase();
};
#define I_DB JDataBase::GetInstance()