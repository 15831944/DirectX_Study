#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
void main()
{
	SQLRETURN sqlrt;

	/* 환경핸들 */
	SQLHENV hEnv;
	sqlrt = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	if (sqlrt != SQL_SUCCESS) return;
	sqlrt = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	if (sqlrt != SQL_SUCCESS) return;

	/* 연결핸들 */
	SQLHENV hDbc;
	sqlrt = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
	if (sqlrt != SQL_SUCCESS) return;

	TCHAR dir[MAX_PATH] = { 0, };
	TCHAR		 szConIn[255] = { 0, };
	TCHAR		 szConOut[255] = { 0, };
	SQLSMALLINT		 pcchConnStrOut = 0;
	GetCurrentDirectory(MAX_PATH, dir);
	///////////////////////////////////////////////////default////////////////////////////////////////////////////
	//_stprintf((TCHAR*)szConIn, _T("DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s\\Sample.mdb;"), dir);
	//sqlrt = SQLDriverConnect(hDbc, NULL, (SQLTCHAR*)szConIn, sizeof(szConIn),
	//	szConOut, sizeof(szConOut),
	//	&pcchConnStrOut, SQL_DRIVER_NOPROMPT);
	///////////////////////////////////////////////////Server//////////////////////////////////////////////////////
	sqlrt = _stprintf((TCHAR*)szConIn, _T("DRIVER={SQL Server};Server=KGCA075;Address=192.168.0.28,1443;Network=dbmssocn;Database=SampleData;Uid=sa;Pwd=kgca!@34;"));
	sqlrt = SQLDriverConnect(hDbc, NULL, (SQLTCHAR*)szConIn, sizeof(szConIn), szConOut, sizeof(szConOut), &pcchConnStrOut, SQL_DRIVER_NOPROMPT);
	/* 명령핸들 */
	SQLHENV hStmt;
	sqlrt = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

	/////////////////////////////////////////////조회//////////////////////////////////////////////////////////////
	SQLLEN iUserID = 1;
	SQLTCHAR UserID[255] = { 0, };
	SQLTCHAR UserPW[255] = { 0, };
	SQLTCHAR NickName[255] = { 0, };
	SQLTCHAR Physical[255] = { 0, };
	SQLTCHAR Magical[255] = { 0, };
	SQLBindCol(hStmt, 1, SQL_C_CHAR, UserID, _countof(UserID), &iUserID);
	SQLBindCol(hStmt, 2, SQL_C_CHAR, UserPW, _countof(UserPW), &iUserID);
	SQLBindCol(hStmt, 3, SQL_C_CHAR, NickName, _countof(NickName), &iUserID);
	SQLBindCol(hStmt, 4, SQL_C_CHAR, Physical, _countof(Physical), &iUserID);
	SQLBindCol(hStmt, 5, SQL_C_CHAR, Magical, _countof(Magical), &iUserID);
	sqlrt = SQLExecDirect(hStmt, (SQLTCHAR*)_T("select UserID, UserPW, NickName, PhysicalDamage, MagicalDamage from UserInfo"), SQL_NTS);
	if (sqlrt != SQL_SUCCESS) return;
	while (SQLFetch(hStmt) != SQL_NO_DATA)
	{
		printf("ID : %s  PW : %s NickName : %s PhysicalDmg : %s MagicalDmg : %s\n", UserID, UserPW, NickName, Physical, Magical);
	}
	/////////////////////////////////////////////UPDATE//////////////////////////////////////////////////////////////
	//SQLCloseCursor(hStmt);
	//sqlrt = SQLExecDirect(hStmt, (SQLTCHAR*)_T("Update UserInfo set UserID = 'asdf' where UserID = 'qwer'"), SQL_NTS);
	/////////////////////////////////////////////ADD//////////////////////////////////////////////////////////////
	SQLCloseCursor(hStmt);
	sqlrt = SQLExecDirect(hStmt, (SQLTCHAR*)_T("Insert into UserInfo (UserID, UserPW, NickName) VALUES ('qwert@naver.com','qwerty123@','KGCA대리기사')"), SQL_NTS);
	if (sqlrt != SQL_SUCCESS) return;

	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}