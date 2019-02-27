#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"
#include <WS2tcpip.h>
#include <windows.h>
#include "stdio.h"
#include "conio.h"
#include "vector"
#include "list"
#include "string"
#include <process.h>
#include "JProtocol.h"
#include <iostream>
#include <tchar.h>
#include <sql.h>
#include <sqlext.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
typedef basic_string<TCHAR> T_STR;
typedef basic_string<WCHAR> W_STR;
typedef basic_string<CHAR> C_STR;
typedef vector<T_STR> T_STR_VECTOR;

typedef struct {
	UPACKET		packet;
	SOCKET		sock;
}PACKET;

template<class T>
class JSingleton
{
public:
	static T& GetInstance()
	{
		static T Instance;
		return Instance;
	}
};

static std::wstring mtow(std::string str)
{
	// 멀티바이트 -> 유니코드
	std::wstring ret = std::wstring(str.begin(), str.end());
	return ret;
}
static std::string wtom(std::wstring str)
{
	//  유니코드 -> 멀티바이트
	std::string ret = std::string(str.begin(), str.end());
	return ret;
}
static char* wtom(WCHAR* pData)
{
	char RetData[4096] = { 0, };
	// 변환길이
	int iLength = WideCharToMultiByte(CP_ACP, 0, pData, -1, 0, 0, NULL, NULL);
	// 변환
	WideCharToMultiByte(CP_ACP, 0, pData, -1, RetData, iLength, NULL, NULL);
	return RetData;
}
static bool wtom(WCHAR* pData, char* pDest)
{
	// 변환길이
	int iLength = WideCharToMultiByte(CP_ACP, 0, pData, -1, 0, 0, NULL, NULL);
	// 변환
	int iRet = WideCharToMultiByte(CP_ACP, 0, pData, -1, pDest, iLength, NULL, NULL);
	if (iRet == 0) return false;
	return true;
}
static WCHAR* mtow(char* pData)
{
	WCHAR RetData[4096] = { 0, };
	// 변환길이
	int iLength = MultiByteToWideChar(CP_ACP, 0, pData, -1, NULL, NULL);
	// 변환
	MultiByteToWideChar(CP_ACP, 0, pData, -1, RetData, iLength);
	return RetData;
}