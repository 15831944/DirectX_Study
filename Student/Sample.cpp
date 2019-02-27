#include "TControlMgr.h"
#include <new>
enum Choice_Num { NewData = 0, DataPrint, FindNum, DataSave, DataLoad, DataSort, Exit = 99 };
void main()
{
	TControlMgr g_CtlMgr;

	int Choice;

	while (1)
	{
		printf("(0)�ű� (1)��� (2)��ȣ�˻� (3)���� (4)�б� (5)���� (99)���� : ");
		scanf("%d", &Choice);
		if (Choice == Exit)
		{
			break;
		}
		switch (Choice)
		{
		case NewData: 
		{
			g_CtlMgr.InputData(); // 10 �� ����
		}break;
		case DataPrint: {
			g_CtlMgr.ShowData();
		}break;
		case FindNum: {
			int i = -1;
			printf("\n ���� �˻� :  ");
			scanf("%d", &i);
			g_CtlMgr.ShowData(g_CtlMgr.Find(i));
		}break;
		case DataSave: {
			g_CtlMgr.Save();
		}break;
		case DataLoad: {
			g_CtlMgr.Load();
		}break;
		case DataSort: {
			g_CtlMgr.Sort();
		}break;
		}
	}
	g_CtlMgr.Release();
	cout << "����";
}