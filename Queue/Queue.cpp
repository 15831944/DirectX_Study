#define MAX_ARRAY 10
#include "stdio.h"
#include <windows.h>
int iFront = 0;
int iRear = 0;
int iData[MAX_ARRAY] = { 0, };
void Print()
{
	system("cls");
	for (int i = 0; i < MAX_ARRAY; i++)
	{
		printf("iData[%d] = %d \n", i, iData[i]);
	}
}
bool EnQueue(int data)
{
	if((iRear + 1) % MAX_ARRAY == iFront % MAX_ARRAY)
	{
		printf("OverFlow \n");
		return false;
	}
	iData[iRear] = data;
	printf("iData[%d] = %d \n",iRear, iData[iRear]);
	iRear++;
	Print();
	return true;
}
bool DeQueue()
{
	if ((iRear + 1) % MAX_ARRAY == iFront % MAX_ARRAY)
	{
		printf("UnderFlow \n");
		return false;
	}
	iData[iFront] = -1;
	iFront++;
	Print();
	return true;
}

int main()
{
	EnQueue(100);
	EnQueue(200);
	EnQueue(300);

	DeQueue();
	DeQueue();
}