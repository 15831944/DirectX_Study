/* 
	sql.h, sqlext.h 
	환경, 연결, 명령 핸들 ( 할당 -> 생성 ) env, dbc, stmt
	SQLHENV
	------------------------------------환경-----------------------------------------
	SQLRETURN rt = SQLAllocHandle((부모)SQL_HANDLE_ENV, (자식)SQL_NULL_HANDLE, )  :: 할당
	if(rt != SQL_SUCCESS) return
	SQLSetEnvAttr( , SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER ) :: 생성
	------------------------------------연결-----------------------------------------
	SQLRETURN rt = SQLAllocHandle((부모)SQL_HANDLE_DBC, (자식)환경, )  :: 할당
	SQLDriverConnect( , NuLL, , , , , , SQL_DRIVER_NOPROMPT); :: 파일오픈
	_stprintf(constrin, _T("DRIVER={ Microsoft Access Driver (*.mdb)}; DBQ(경로) = %s\\cigaret.mdb;"), dir);
	TCHAR dir[MAX_PATH = 260] = {0, } 
	GetCurrentDirectory(MAX_PATH, dir); 
	_countof(); 배열의 크기 리턴
	------------------------------------명령-----------------------------------------
	SQLRETURN rt = SQLAllocHandle((부모)SQL_HANDLE_STMT, (자식)연결, )  :: 할당

	/////// 멀티바이트, 유니코드 잘맞춰줘야됨
	SQLLEN IName;
	SQLCHAR Name[256]
	SQLBindCol(, 1, SQL_C_CHAR, Name,  _countofName, &IName)
	SQLExecDirect(stmt, _T("select username, userpass from userlist"), SQL_NTS(문자열끝에NULL)); :: 명령
	while(TRUE)
		if(SQLfetch() == SQL_NO_DATA) break:: 반복적작업


	소멸 : SQLFreeHandle(SQL_HANDLE_STMT, );           ::       (소멸은 역순)
	소멸 : SQLFreeHandle(SQL_HANDLE_DBC, );
	소멸 : SQLFreeHandle(SQL_HANDLE_ENV, );

	SQLCloseCursor(); 파일포인터 초기화

*/
// accountTime -> Date(), 날짜/시간
/*
	Select - From - Where 기본구조
	Select :: 조회
	INSERT INTO :: 추가
	ex) INSERT INTO userlist (username,userpass,email) VALUES('1111','2222','3333@444.com');
	UPDATE SET :: 수정
	ex) update Userlist set username='%s' where username='%s', _T(1), _T(2)
	
*/

/*
	if(SQLRETURN != SQL_SUCCESS && SQL_SUCCESS_WITH_INFO)
	{
		// 에러체크용도
		SQLTCHAR buf[SQL_MAX_MESSAGE_LENGTH+1]
		SQLError();
		int count;
		while(rt != SQL_NO_DATA)
		{
			// 세부적인에러체크용도
			rt = SQLGetDiagRec(SQL_HANDLE_DBC, hDbc, count++,);
		}
	}
*/
/*
	///////////////////////////////////////////////DSN/////////////////////////////////////////////////
	// 파일DNS
	관리도구 - ODBC데이터 원본 관리자(32비트) - 파일DNS - 디텍토리설정 - 추가 - mdb ~~
	_stprintf(strIn, _T("FileDsn=%s"),_T("~~~.dsn));

	// 시스템DNS
	_stprintf(strIn, _T("%s"),_T("~~~)); // 시스템에 장착되어있다
	SQLConnect(hDbc, (SQLTCHAR*)strIn, SQL_NTS, ID, SQL_NTS, PW, SQLNTS);
*/

/*
	///////////////////////////////////////////SQL SERVER////////////////////////////////////////////////
	Server - 데이터베이스 만들기 - 데이터베이스 가져오기(테스크)
	_stprintf((TCHAR*)szConIn, _T("DRIVER={SQL Server};
								   Server=ComName.kr;
								   Address=192.168.0.23,1443;(포트번호) <- 디폴트가 1433
								   Network=dbmssocn;(TCP/IP로 접근한다는 뜻)
								   Database=Server;(서버에 등록한 이름)
								   Uid=sa;(서버아이디)
								   Pwd=kgca!@34;");(서버비번)
*/
/*
	1) acess - 다이렉트쿼리 추가삭제조회업데이트 .
	2) server -           책
*/