/*
	:::::::::::::::::::::::::::::::::::::AsyncSelect
	-> Server
	// wparam -> 소켓 등.. lparam -> 부가정보 .. 
	1: 원도우 생성
	2: WSAAsyncSelect생성
	3: winproc -> 오류체크 : WSA GET SELECT ERROR :: lparam
				  else     : WSA GET SELECT EVENT -> FD_ACCEPT, CLOSE READ WRITE ...  lparam

	// 넌블록킹일때 recv -> != WSAWORULDBLOCK PostMessage(, WM_SOCKET, wParam, FD_READ); 
							:: 두번다시 recv에 안들어올수있기때문에 수작업으로 다시호출시켜준다. + CLOSE도
*/
/*
	-> Client
	WM_SOCKET, FD_CONNET, FD_READ, FD_WRITE, FD_CLOSE

	함수(MSG msg) -> 받아서 메세지 처리 :: if 에러체크 else 이벤트처리
*/
/*
	:::::::::::::::::::::::::::::::::::EventSelect
	-> Svr
	CLIENT SOCKET 하나당 EVENT 하나
	HANDLE aaa = WSACreateEvent(); -> 이벤트 생성
	WSAEventSelect();
	WaitForMultipleObjects() :: False 놓으면 하나만 시그널상태되도 리턴해줌
							 :: 타임아웃 체크 WAIT_TIMEOUT
							 :: index = ret - WAIT_OBJECT_0 << 기본적으로 0 이지만 걍쓰셈(바뀔수도있음)
	index부터 다시 돌려야  모든유저를 받을수있다.
	WSANETWORKEVENTS nwe;
	if(nwe. INetworkEvents & FD_ACCEPT) accept 작업.
	에러체크 if (nwe.iErrorCode[FD_READ,WRITE,CLOSE..._BIT] == 0) 에러코드가 하나라도있으면안된다. ==0 이면 정상
	WSAEnumNetworkEvents() ; 

*/