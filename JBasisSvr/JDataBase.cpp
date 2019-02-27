#include "JDataBase.h"

bool JDataBase::Init()
{
	SQLRETURN		Ret;
	TCHAR			dir[MAX_PATH] = { 0, };
	TCHAR			szConIn[255] = { 0, };
	TCHAR			szConOut[255] = { 0, };
	SQLSMALLINT		pcchConnStrOut = 0;

	/* 환경핸들 */
	Ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv);
	if (Ret != SQL_SUCCESS) return FALSE;
	Ret = SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	if (Ret != SQL_SUCCESS) return FALSE;

	/* 연결핸들 */
	Ret = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc);
	if (Ret != SQL_SUCCESS) return FALSE;
	GetCurrentDirectory(MAX_PATH, dir);
	_stprintf((TCHAR*)szConIn, _T("DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s\\Sample.mdb;"), dir);
	Ret = SQLDriverConnect(m_hDbc, NULL, (SQLTCHAR*)szConIn, sizeof(szConIn),
		szConOut, sizeof(szConOut),
		&pcchConnStrOut, SQL_DRIVER_NOPROMPT);

	/* 명령핸들 */
	Ret = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt);
	return true;
}
bool JDataBase::Release()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
	return true;
}
bool JDataBase::Add(const TCHAR* szID, const TCHAR* szPW, const TCHAR* szName)
{
	wstring Server = GetChannel();
	SQLRETURN Ret;
	SQLTCHAR SQL[255] = { 0, };
	_stprintf(SQL, _T("Insert into %s(UserID, UserPW, NickName) VALUES('%s', '%s', '%s')"), Server.c_str(), szID, szPW, szName);
	Ret = SQLExecDirect(m_hStmt, SQL, SQL_NTS);
	if (Ret != SQL_SUCCESS)
	{
		std::cout << "ID or Name Overlap..." << std::endl;
		_getch();
		system("cls");
	}
	SQLCloseCursor(m_hStmt);
	return true;
}
bool JDataBase::Del(const TCHAR* DelName)
{
	wstring Server = GetChannel();
	SQLRETURN Ret;
	SQLTCHAR SQL[255] = { 0, };
	_stprintf(SQL, _T("delete from %s where NickName='%s'"), Server.c_str(), DelName);
	Ret = SQLExecDirect(m_hStmt, SQL, SQL_NTS);
	if (Ret != SQL_SUCCESS && Ret != 100)
	{
		std::cout << "NickName Not Find..." << std::endl;
		_getch();
		system("cls");
	}
	SQLCloseCursor(m_hStmt);
	return true;
}
bool JDataBase::Check()
{
	SQLRETURN Ret;
	SQLLEN iUserID = 1;
	SQLTCHAR UserID[255] = { 0, };
	SQLTCHAR UserPW[255] = { 0, };
	SQLTCHAR NickName[255] = { 0, };
	SQLTCHAR Physical[255] = { 0, };
	SQLTCHAR Magical[255] = { 0, };
	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, UserID, _countof(UserID), &iUserID);
	SQLBindCol(m_hStmt, 2, SQL_C_CHAR, UserPW, _countof(UserPW), &iUserID);
	SQLBindCol(m_hStmt, 3, SQL_C_CHAR, NickName, _countof(NickName), &iUserID);
	SQLBindCol(m_hStmt, 4, SQL_C_CHAR, Physical, _countof(Physical), &iUserID);
	SQLBindCol(m_hStmt, 5, SQL_C_CHAR, Magical, _countof(Magical), &iUserID);

	wstring ExecDirect = L"select UserID, UserPW, NickName, PhysicalDamage, MagicalDamage from ";

	ExecDirect += GetChannel();
	Ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)ExecDirect.c_str(), SQL_NTS);
	if (Ret != SQL_SUCCESS) return FALSE;
	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		printf("ID : %s  PW : %s NickName : %s PhysicalDmg : %s MagicalDmg : %s\n", UserID, UserPW, NickName, Physical, Magical);
	}
	SQLCloseCursor(m_hStmt);
	return true;
}
bool JDataBase::Update(const TCHAR* SrcValue, const TCHAR* DescValue)
{
	wstring Server = GetChannel();
	SQLRETURN Ret;
	SQLTCHAR SQL[255] = { 0, };
	_stprintf(SQL, _T("Update %s set NickName='%s' where NickName='%s'"), Server.c_str(), DescValue, SrcValue);
	Ret = SQLExecDirect(m_hStmt, SQL, SQL_NTS);
	if (Ret != SQL_SUCCESS)
	{
		std::cout << "NickName Not Find or Overlap..." << std::endl;
		_getch();
		system("cls");
	}
	SQLCloseCursor(m_hStmt);
	return true;
}

JDataBase::JDataBase()
{
}


JDataBase::~JDataBase()
{
}
