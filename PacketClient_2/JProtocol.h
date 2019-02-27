#pragma once
#include "windows.h"
#define MAX_MSG_COUNTER 2048
// 1����Ʈ�� ��ŷ
#pragma pack(push, 1)
typedef struct
{
	WORD len;  // ��Ŷ ����
	WORD type; // ��Ŷ ����
}PACKET_HEADER;
typedef struct
{
	PACKET_HEADER ph;
	char msg[MAX_MSG_COUNTER];
}UPACKET;
#pragma pack(pop)
#define LEN ph.len
#define TYPE ph.type
#define PACKET_CHAT_MSG 1000
#define PACKET_CHAT_NAME_ACK 2000
#define PACKET_CHAT_NAME_REQ 2001
#define PACKET_HEADER_SIZE 4
//REQ <-> ACK
//UPACKET ����
// client -> �����¸޼���  memcpy
//UPACKET packet;
//ZeroMemory(&packet, UPACKET);
//iRecvByte = 0;
//while (iRecvByte < packet.ph.len)
//{
//	iRecvByte += recv(sock, &packet.msg[iRecvByte], packet.ph.len - PACKET_HEADER_SIZE);
//}#pragma once
