#include "JSQLServer.h"

enum ODBCCHOICE
{
	CHECK = 0,
	ADD,
	DEL,
	UPDATE,
	EXIT = 99
};
WCHAR* mtow(char* pData)
{
	WCHAR RetData[4096] = { 0, };
	// ��ȯ����
	int iLength = MultiByteToWideChar(CP_ACP, 0, pData, -1, NULL, NULL);
	// ��ȯ
	MultiByteToWideChar(CP_ACP, 0, pData, -1, RetData, 4096);
	return RetData;
}
void main()
{
	JSQLServer sqlserver;
	int Choice;
	while (1)
	{
		printf("(0)CHECK (1)ADD (2)DEL (3)UPDATE (99)EXIT : ");
		scanf("%d", &Choice);
		if (Choice == EXIT)
		{
			break;
		}
		switch (Choice)
		{
		case CHECK:
		{
			system("cls");
			sqlserver.Check();
		}break;
		case ADD:
		{
			system("cls");
			SQLVARCHAR szID[20] = { 0, };
			SQLVARCHAR szPW[20] = { 0, };
			SQLVARCHAR szName[20] = { 0, };
			string tID;
			string tPW;
			string tName;
			cout << "ȸ������ ID : ";
			cin >> szID;
			cout << "ȸ������ PW : ";
			cin >> szPW;
			cout << "ȸ������ Name : ";
			cin >> szName;

			//tID = mtow(szID);
			//tPW = mtow(szPW);
			//tName = mtow(szName);
			sqlserver.Add(szID, szPW, szName);
		}break;
		case DEL:
		{
			system("cls");
			wstring szName;
			char name[256] = { 0, };
			cout << "Delete Name : ";
			cin >> name;
			szName = mtow(name);
			sqlserver.Delete(szName.c_str());
		}break;
		case UPDATE:
		{
			system("cls");
			char szFrontName[256] = { 0, };
			char szChangeName[256] = { 0, };

			wstring tFrontName;
			wstring tChangeName;
			cout << "���� �� Name : ";
			cin >> szFrontName;
			cout << "���� �� Name : ";
			cin >> szChangeName;
			tFrontName = mtow(szFrontName);
			tChangeName = mtow(szChangeName);

			sqlserver.Update(tFrontName.c_str(), tChangeName.c_str());
		}break;
		}
	}
}