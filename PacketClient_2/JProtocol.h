#pragma once
#include "windows.h"
#define MAX_MSG_COUNTER 2048
// 1바이트씩 패킹
#pragma pack(push, 1)
typedef struct
{
	WORD len;  // 패킷 길이
	WORD type; // 패킷 종류
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
//UPACKET 생성
// client -> 보내는메세지  memcpy
//UPACKET packet;
//ZeroMemory(&packet, UPACKET);
//iRecvByte = 0;
//while (iRecvByte < packet.ph.len)
//{
//	iRecvByte += recv(sock, &packet.msg[iRecvByte], packet.ph.len - PACKET_HEADER_SIZE);
//}#pragma once
