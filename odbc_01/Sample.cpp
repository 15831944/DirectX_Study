/* 
	sql.h, sqlext.h 
	ȯ��, ����, ��� �ڵ� ( �Ҵ� -> ���� ) env, dbc, stmt
	SQLHENV
	------------------------------------ȯ��-----------------------------------------
	SQLRETURN rt = SQLAllocHandle((�θ�)SQL_HANDLE_ENV, (�ڽ�)SQL_NULL_HANDLE, )  :: �Ҵ�
	if(rt != SQL_SUCCESS) return
	SQLSetEnvAttr( , SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER ) :: ����
	------------------------------------����-----------------------------------------
	SQLRETURN rt = SQLAllocHandle((�θ�)SQL_HANDLE_DBC, (�ڽ�)ȯ��, )  :: �Ҵ�
	SQLDriverConnect( , NuLL, , , , , , SQL_DRIVER_NOPROMPT); :: ���Ͽ���
	_stprintf(constrin, _T("DRIVER={ Microsoft Access Driver (*.mdb)}; DBQ(���) = %s\\cigaret.mdb;"), dir);
	TCHAR dir[MAX_PATH = 260] = {0, } 
	GetCurrentDirectory(MAX_PATH, dir); 
	_countof(); �迭�� ũ�� ����
	------------------------------------���-----------------------------------------
	SQLRETURN rt = SQLAllocHandle((�θ�)SQL_HANDLE_STMT, (�ڽ�)����, )  :: �Ҵ�

	/////// ��Ƽ����Ʈ, �����ڵ� �߸�����ߵ�
	SQLLEN IName;
	SQLCHAR Name[256]
	SQLBindCol(, 1, SQL_C_CHAR, Name,  _countofName, &IName)
	SQLExecDirect(stmt, _T("select username, userpass from userlist"), SQL_NTS(���ڿ�����NULL)); :: ���
	while(TRUE)
		if(SQLfetch() == SQL_NO_DATA) break:: �ݺ����۾�


	�Ҹ� : SQLFreeHandle(SQL_HANDLE_STMT, );           ::       (�Ҹ��� ����)
	�Ҹ� : SQLFreeHandle(SQL_HANDLE_DBC, );
	�Ҹ� : SQLFreeHandle(SQL_HANDLE_ENV, );

	SQLCloseCursor(); ���������� �ʱ�ȭ

*/
// accountTime -> Date(), ��¥/�ð�
/*
	Select - From - Where �⺻����
	Select :: ��ȸ
	INSERT INTO :: �߰�
	ex) INSERT INTO userlist (username,userpass,email) VALUES('1111','2222','3333@444.com');
	UPDATE SET :: ����
	ex) update Userlist set username='%s' where username='%s', _T(1), _T(2)
	
*/

/*
	if(SQLRETURN != SQL_SUCCESS && SQL_SUCCESS_WITH_INFO)
	{
		// ����üũ�뵵
		SQLTCHAR buf[SQL_MAX_MESSAGE_LENGTH+1]
		SQLError();
		int count;
		while(rt != SQL_NO_DATA)
		{
			// �������ο���üũ�뵵
			rt = SQLGetDiagRec(SQL_HANDLE_DBC, hDbc, count++,);
		}
	}
*/
/*
	///////////////////////////////////////////////DSN/////////////////////////////////////////////////
	// ����DNS
	�������� - ODBC������ ���� ������(32��Ʈ) - ����DNS - �����丮���� - �߰� - mdb ~~
	_stprintf(strIn, _T("FileDsn=%s"),_T("~~~.dsn));

	// �ý���DNS
	_stprintf(strIn, _T("%s"),_T("~~~)); // �ý��ۿ� �����Ǿ��ִ�
	SQLConnect(hDbc, (SQLTCHAR*)strIn, SQL_NTS, ID, SQL_NTS, PW, SQLNTS);
*/

/*
	///////////////////////////////////////////SQL SERVER////////////////////////////////////////////////
	Server - �����ͺ��̽� ����� - �����ͺ��̽� ��������(�׽�ũ)
	_stprintf((TCHAR*)szConIn, _T("DRIVER={SQL Server};
								   Server=ComName.kr;
								   Address=192.168.0.23,1443;(��Ʈ��ȣ) <- ����Ʈ�� 1433
								   Network=dbmssocn;(TCP/IP�� �����Ѵٴ� ��)
								   Database=Server;(������ ����� �̸�)
								   Uid=sa;(�������̵�)
								   Pwd=kgca!@34;");(�������)
*/
/*
	1) acess - ���̷�Ʈ���� �߰�������ȸ������Ʈ .
	2) server -           å
*/