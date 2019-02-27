#include "JODBC.h"
wstring JODBC::GetServer()
{
	while (TRUE)
	{
		int iServer = -1;
		system("cls");
		cout << "서버를 고르시오." << endl;
		cout << "1. Korea" << endl;
		cout << "2. Asia" << endl;
		cout << "서버 : ";
		cin >> iServer;
		switch (iServer)
		{
		case 1:
		{
			wstring Korea = L"Korea";
			return Korea;
		}break;
		case 2:
		{
			wstring Asia = L"Asia";
			return Asia;
		}break;
		default:
		{
			cout << "잘못 입력하셨습니다. 다시 골라주세요." << endl;
		}break;
		}
	}
	return NULL;
}
bool JODBC::Set()
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
	//_stprintf((TCHAR*)szConIn, _T("DRIVER = { Microsoft Access Driver (*.mdb) };DBQ = %s\\Sample.mdb;"), dir);
	//_stprintf((TCHAR*)szConIn, _T("DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s\\Sample.mdb;"), dir);
	_stprintf((TCHAR*)szConIn, _T("%s"), _T("Driver={SQL Server};Server=ASH.kr;Address=222.112.63.66,1433;Network=dbmssocn;Database=master;Uid=sa;Pwd=tkfkd2!#;"));
	Ret = SQLDriverConnect(m_hDbc, NULL, (SQLTCHAR*)szConIn, sizeof(szConIn),
		szConOut, sizeof(szConOut),
		&pcchConnStrOut, SQL_DRIVER_NOPROMPT);

	/* 명령핸들 */
	Ret = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt);

	return TRUE;
}
bool JODBC::Add(const TCHAR* szID, const TCHAR* szPW, const TCHAR* szName)
{
	SQLRETURN Ret;
	//SQLTCHAR SQL[255] = { 0, };
	//_stprintf(SQL, _T("Insert into %s(UserID, UserPW, NickName) VALUES('%s', '%s', '%s')"),Server.c_str(), szID, szPW, szName);
	//Ret = SQLExecDirect(m_hStmt, SQL, SQL_NTS);
	//if (Ret != SQL_SUCCESS)
	//{
	//	std::cout << "ID or Name Overlap..." << std::endl;
	//	_getch();
	//	system("cls");
	//}
	//SQLCloseCursor(m_hStmt);

	TCHAR sql[] = _T("{ ? = CALL sam(?)}");
	Ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)sql, SQL_NTS);

	SWORD sReturn;
	SQLLEN cbRetParam;
	SQLBindParameter(m_hStmt, 1,  // 반환값 저장
		SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0,
		&sReturn, 0, &cbRetParam);

	SQLINTEGER ID = 4; // 파라미터 전달 : 4번 인덱스 조회
	SQLBindParameter(m_hStmt, 2,
		SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &ID, 0, NULL);


	return TRUE;
}
bool JODBC::Delete(const TCHAR* DelName)
{
	wstring Server = GetServer();
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
	return TRUE;
}
bool JODBC::Update(const TCHAR* SrcValue, const TCHAR* DescValue)
{
	wstring Server = GetServer();
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
	return TRUE;
}
bool JODBC::Check()
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

	ExecDirect += GetServer();
	Ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)ExecDirect.c_str(), SQL_NTS);
	if (Ret != SQL_SUCCESS) return FALSE;
	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		printf("ID : %s  PW : %s NickName : %s PhysicalDmg : %s MagicalDmg : %s\n", UserID, UserPW, NickName, Physical, Magical);
	}
	SQLCloseCursor(m_hStmt);
	return true;
}
bool JODBC::Init()
{
	Set();
	return true;
}
bool JODBC::Frame()
{
	return true;
}
bool JODBC::Render()
{
	return true;
}
bool JODBC::Release()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
	return true;
}
JODBC::JODBC()
{
	Set();
}


JODBC::~JODBC()
{
	Release();
}
