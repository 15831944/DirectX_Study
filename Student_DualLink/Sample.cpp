#include "JStudent.h"

int main()
{
	JStudent Stu;
	int Choice;

	while (1)
	{
		printf("(0)신규 (1)제거 (2)출력 (3)번호검색 (4)이름검색 (5)저장 (6)읽기 (7)생성 (99)종료 : ");
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