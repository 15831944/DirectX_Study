#include "JStudent.h"

int main()
{
	JStudent Stu;
	int Choice;

	while (1)
	{
		printf("(0)�ű� (1)���� (2)��� (3)��ȣ�˻� (4)�̸��˻� (5)���� (6)�б� (7)���� (99)���� : ");
		scanf("%d", &Choice);
		if (Choice == Exit)
		{
			break;
		}
		switch (Choice)
		{
		case NewData: {
			Stu.New_Data();
		}break;
		case DelData: {
			Stu.Del_Data(Stu.Find_Name());
		}break;
		case DataPrint: {
			Stu.Data_Print();
		}break;
		case FindNum: {
			Stu.Find_Num();
		}break;
		case FindName: {
			Stu.Find_Name();
		}break;
		case DataSave: {
			Stu.Data_Save();
		}break;
		case DataLoad: {
			Stu.Data_Load();
		}break;
		case DataCreat: {
			Stu.Data_Creat();
		}break;
		}
	}
}