#include "JSQLServer.h"
bool JSQLServer::Set()
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
	_stprintf((TCHAR*)szConIn, _T("%s"), _T("Driver={SQL Server};Server=ASH.kr;Address=192.168.0.122,1433;Network=dbmssocn;Database=master;Uid=sa;Pwd=kgca!@34;"));
	Ret = SQLDriverConnect(m_hDbc, NULL, (SQLTCHAR*)szConIn, sizeof(szConIn), szConOut, sizeof(szConOut), &pcchConnStrOut, SQL_DRIVER_NOPROMPT);

	/* 명령핸들 */
	Ret = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt);

	return TRUE;
}
bool JSQLServer::Add(const SQLVARCHAR* szID, const SQLVARCHAR* szPW, const SQLVARCHAR* szName)
{
	SQLRETURN Ret;
	SQLLEN cbID = SQL_NTS;
	SQLINTEGER ID = rand();
	Ret = SQLBindParameter(m_hStmt, 1,
		SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &ID, 0, &cbID);

	SQLVARCHAR UserID[20] = "AsiaUser@pp.net";
	Ret = SQLBindParameter(m_hStmt, 2, 
		SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, (SQLVARCHAR*)szID, _countof(UserID), &cbID);

	SQLVARCHAR UserPW[20] = "123456sdd";
	Ret = SQLBindParameter(m_hStmt, 3,
		SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, (SQLVARCHAR*)szPW, _countof(UserPW), &cbID);

	SQLVARCHAR NickName[20] = "54545sdf";
	Ret = SQLBindParameter(m_hStmt, 4,
		SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, (SQLVARCHAR*)szName, _countof(NickName), &cbID);

	SQLINTEGER PDmg = 1;
	Ret = SQLBindParameter(m_hStmt, 5,
		SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &PDmg, 0, &cbID);

	SQLINTEGER MDmg = 1;
	Ret = SQLBindParameter(m_hStmt, 6,
		SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &MDmg, 0, &cbID);

	SQLINTEGER money = 1000;
	Ret = SQLBindParameter(m_hStmt, 7,
		SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &money, 0, &cbID);

	//insert into Asia(ID, UserID, UserPW, NickName, PhysicalDamage, MagicalDamage, Money)
	LPCTSTR sqls = _T("{CALL AddUser (?,?,?,?,?,?,?)}");
	Ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)sqls, SQL_NTS);
	SQLCloseCursor(m_hStmt);
	return TRUE;
}
bool JSQLServer::Delete(const TCHAR* DelName)
{
	SQLRETURN Ret;
	SQLTCHAR SQL[255] = { 0, };
	_stprintf(SQL, _T("delete from Asia where NickName='%s'"), DelName);
	Ret = SQLExecDirect(m_hStmt, SQL, SQL_NTS);
	if (Ret != SQL_SUCCESS && Ret != 100)
	{
		std::cout << "NickName Not Find..." << std::endl;
		_getch();
		system("cls");
	}
	SQLCloseCursor(m_hStmt);
	return TRUE;
}
bool JSQLServer::Update(const TCHAR* SrcValue, const TCHAR* DescValue)
{
	SQLRETURN Ret;
	SQLTCHAR SQL[255] = { 0, };
	_stprintf(SQL, _T("Update Asia set NickName='%s' where NickName='%s'"), DescValue, SrcValue);
	Ret = SQLExecDirect(m_hStmt, SQL, SQL_NTS);
	if (Ret != SQL_SUCCESS)
	{
		std::cout << "NickName Not Find or Overlap..." << std::endl;
		_getch();
		system("cls");
	}
	SQLCloseCursor(m_hStmt);
	return TRUE;
}
bool JSQLServer::Check()
{
	SQLRETURN Ret;
	SQLWCHAR sql[] = L"{ ? = CALL SearchUser()}";
	Ret = SQLExecDirect(m_hStmt, sql, SQL_NTS);

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

	wstring ExecDirect = L"select UserID, UserPW, NickName, PhysicalDamage, MagicalDamage from Asia";

	Ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)ExecDirect.c_str(), SQL_NTS);
	if (Ret != SQL_SUCCESS) return FALSE;
	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		printf("ID : %s  PW : %s NickName : %s PhysicalDmg : %s MagicalDmg : %s\n", UserID, UserPW, NickName, Physical, Magical);
	}
	SQLCloseCursor(m_hStmt);
	return true;
}
bool JSQLServer::Release()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
	return true;
}
JSQLServer::JSQLServer()
{
	Set();
}


JSQLServer::~JSQLServer()
{
	Release();
}
