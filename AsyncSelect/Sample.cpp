/*
	:::::::::::::::::::::::::::::::::::::AsyncSelect
	-> Server
	// wparam -> ���� ��.. lparam -> �ΰ����� .. 
	1: ������ ����
	2: WSAAsyncSelect����
	3: winproc -> ����üũ : WSA GET SELECT ERROR :: lparam
				  else     : WSA GET SELECT EVENT -> FD_ACCEPT, CLOSE READ WRITE ...  lparam

	// �ͺ��ŷ�϶� recv -> != WSAWORULDBLOCK PostMessage(, WM_SOCKET, wParam, FD_READ); 
							:: �ι��ٽ� recv�� �ȵ��ü��ֱ⶧���� ���۾����� �ٽ�ȣ������ش�. + CLOSE��
*/
/*
	-> Client
	WM_SOCKET, FD_CONNET, FD_READ, FD_WRITE, FD_CLOSE

	�Լ�(MSG msg) -> �޾Ƽ� �޼��� ó�� :: if ����üũ else �̺�Ʈó��
*/
/*
	:::::::::::::::::::::::::::::::::::EventSelect
	-> Svr
	CLIENT SOCKET �ϳ��� EVENT �ϳ�
	HANDLE aaa = WSACreateEvent(); -> �̺�Ʈ ����
	WSAEventSelect();
	WaitForMultipleObjects() :: False ������ �ϳ��� �ñ׳λ��µǵ� ��������
							 :: Ÿ�Ӿƿ� üũ WAIT_TIMEOUT
							 :: index = ret - WAIT_OBJECT_0 << �⺻������ 0 ������ ������(�ٲ��������)
	index���� �ٽ� ������  ��������� �������ִ�.
	WSANETWORKEVENTS nwe;
	if(nwe. INetworkEvents & FD_ACCEPT) accept �۾�.
	����üũ if (nwe.iErrorCode[FD_READ,WRITE,CLOSE..._BIT] == 0) �����ڵ尡 �ϳ���������ȵȴ�. ==0 �̸� ����
	WSAEnumNetworkEvents() ; 

*/