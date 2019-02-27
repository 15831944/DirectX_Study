#include "JProtocol.h"
CRITICAL_SECTION g_Crit;
bool bPlay = false;
wstring g_strChannel;
wstring SetChannel()
{
	while (TRUE)
	{
		int iServer = -1;
		system("cls");
		cout << "채널을 고르시오." << endl;
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
unsigned  int _stdcall KeyInputProcex(LPVOID arg)
{
	printf("\n[보낼메세지] : ");
	SOCKET sock = (SOCKET)arg;
	while (TRUE)
	{
		if (!bPlay)  continue;
		char buffer[256] = { 0, };
		UPACKET packet;
		ZeroMemory(&packet, sizeof(UPACKET));
		fgets(buffer, 256, stdin);
		if (buffer[0] == '\n')
		{
			continue;
		}
		int iBufSize = strlen(buffer);
		int iSendByte = 0;
		memcpy(&packet.msg, buffer, iBufSize);
		packet.LEN = strlen(packet.msg) + PACKET_HEADER_SIZE;
		packet.TYPE = PACKET_CHAT_MSG;
		iSendByte += send(sock, (char*)&packet, packet.LEN, 0);
		while (iSendByte < packet.LEN)
		{
			iSendByte += send(sock, (char*)&packet, packet.LEN, 0);
		}
		if (iSendByte == SOCKET_ERROR || iSendByte == 0)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf("=================서버종료=================");
				break;
			}
		}
	}
	closesocket(sock);
	return 0;
}
unsigned int _stdcall RecvProcex(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	while (TRUE)
	{
		if (!bPlay)  continue;
		char buffer[256] = { 0, };
		int iRecvByte = 0;
		int iStartByte = 0;
		int iLen = 0;
		iLen = recv(sock, &buffer[iStartByte], PACKET_HEADER_SIZE - iRecvByte, 0);
		iRecvByte += iLen;
		if (iRecvByte == PACKET_HEADER_SIZE)
		{
			UPACKET* pPacket = (UPACKET*)buffer;
			while (iRecvByte < pPacket->LEN)
			{
				iLen = recv(sock, &buffer[iRecvByte], pPacket->LEN - iRecvByte, 0);
				iRecvByte += iLen;
				if (iLen == 0 || iLen == SOCKET_ERROR)
				{
					break;
				}
			}
			if (iRecvByte == pPacket->LEN)
			{
				UPACKET RecvPacket;
				memset(&RecvPacket, 0, sizeof(RecvPacket));
				memcpy(&RecvPacket, pPacket, pPacket->LEN);
				switch (pPacket->TYPE)
				{
				case PACKET_CHAT_MSG:
				{
					printf("\n[받은메세지] : %s", pPacket->msg);
					printf("\n[보낼메세지] : ");
				}break;

				case PACKET_CHAT_NAME_ACK:
				{
					UPACKET packet;
					//printf("\n%s", pPacket->msg);
					char NameBuf[] = "이준환 ";
					packet.ph.len = strlen(NameBuf) + PACKET_HEADER_SIZE;
					packet.ph.type = PACKET_CHAT_NAME_REQ;
					memcpy(packet.msg, NameBuf, packet.ph.len);
					int iSendSize = send(sock, (char*)&packet, packet.ph.len, 0);
					printf("\n[보낼메세지] : ");
				}break;
				}
				iStartByte = 0;
				iRecvByte = 0;
			}
		}
		else
		{
			iStartByte += iRecvByte;
		}
	}
	closesocket(sock);
	return 0;
}
void main()
{
	int ip = -1;
	std::cout << "ip  : 192.168.0.";
	std::cin >> ip;
	string strIP = "192.168.0.";
	strIP += to_string(ip);
	g_strChannel = SetChannel();

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET ListenSock;
	ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.S_un.S_addr = inet_addr(strIP.c_str());
	sa.sin_port = htons(10000);
	int iRet = connect(ListenSock, (sockaddr*)&sa, sizeof(sa));
	




	bPlay = true;
	InitializeCriticalSection(&g_Crit);
	unsigned int iThreadID;
	unsigned long RecvInput = _beginthreadex(NULL, 0, RecvProcex, (LPVOID)ListenSock, 0, &iThreadID);
	unsigned long KeyInput = _beginthreadex(NULL, 0, KeyInputProcex, (LPVOID)ListenSock, 0, &iThreadID);

	//대기함수
	WaitForSingleObject((HANDLE)RecvInput, INFINITE);
	WaitForSingleObject((HANDLE)KeyInput, INFINITE);
	DeleteCriticalSection(&g_Crit);

	CloseHandle((HANDLE)KeyInput);
	CloseHandle((HANDLE)RecvInput);
	closesocket(ListenSock);
	WSACleanup();
}