#include <stdio.h>
#define MAX_ARRAY 3
class Stack
{
public:
	int iIndex = 0;
	int iData[MAX_ARRAY];
public:
	bool Push(int data)
	{
		if (iIndex > MAX_ARRAY) return false;
		iData[iIndex] = data;
		printf("%d¹ø Data : %d\n", iIndex, iData[iIndex]);
		iIndex++;
		return true;
	}
	bool Pop()
	{
		if (iIndex < 0) return false;
		iIndex--;
		iData[iIndex] = -1;
		printf("%d¹ø Data : %d\n", iIndex, iData[iIndex]);

		return true;
	}
	void Print()
	{
		for (int i = 0; i <= iIndex; i++)
		{
			printf("%d¹ø Data : %d\n", i, iData[i]);
		}
	}
public:
	Stack()
	{
		iIndex = 0;
	}
};
int main()
{
	Stack stack;
	stack.Push(10);
	stack.Push(20);
	stack.Push(30);

	stack.Pop();
	printf("================================\n");
	stack.Print();

}