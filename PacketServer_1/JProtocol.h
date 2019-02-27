#pragma once
#include "windows.h"
#include "string"
using namespace std;
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
	char name[MAX_MSG_COUNTER];
}UPACKET;
typedef struct
{
	char  m_szName[5];
	int   m_iDamage;
	float m_fSpeed;
}PLAYER_DATA;
#pragma pack(pop)
#define LEN ph.len
#define TYPE ph.type
#define PACKET_CHAT_MSG 1000
#define PACKET_CHAT_NAME_ACK 2000
#define PACKET_CHAT_NAME_REQ 2001
#define PACKET_HEADER_SIZE 4
