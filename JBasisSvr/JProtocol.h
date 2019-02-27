#pragma once
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

typedef struct 
{
	int iAccountID;
	char Name[20];
	char PW[20];
}ReqAccountObtain;
typedef struct 
{
	int iAccountID;
	int iAck;
}AckAccountObtain;
#pragma pack(pop)
#define LEN ph.len
#define TYPE ph.type
#define PACKET_CHAT_MSG 1000
#define PACKET_CHAT_NAME_ACK 2000
#define PACKET_CHAT_NAME_REQ 2001
#define PACKET_HEADER_SIZE 4
#define REQ_ACCOUNT_OBTAIN 9999
#define ACK_ACCOUNT_OBTAIN 9999
/* DataBase */
#define PACKET_DB_PRINT_ACK 3000
#define PACKET_DB_PRINT_REQ 3001
#define PACKET_DB_ADD_ACK 3100
#define PACKET_DB_ADD_REQ 3101
#define PACKET_DB_DEL_ACK 3200
#define PACKET_DB_DEL_REQ 3201
#define PACKET_DB_UPDATE_ACK 3300
#define PACKET_DB_UPDATE_REQ 3301
#define PACKET_DB_CHANNEL_ACK 3400
#define PACKET_DB_CHANNEL_REQ 3401