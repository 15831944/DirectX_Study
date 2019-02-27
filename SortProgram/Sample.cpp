#include <iostream>
#include "HSort.h"
using namespace std;
enum SortSelect
{
	BUBBLE = 1,
	INSERT,
	QUICK,
	PRINT,
	EXIT = 99
};
int main()
{
	int iNumber = -1;
	int iSelect = -1;
	bool iExit = true;
	cout << "��� ������ �����͸� �����Ͻðڽ��ϱ� ? : ";
	cin >> iNumber;
	HSort* SortSelect = new HSort(iNumber);

	while (iExit)
	{
		cout << "(1) �������� (2) ����Ʈ���� (3) ������ (4) ��� (99) ���� : ";
		cin >> iSelect;
		switch(iSelect)
		{
		case BUBBLE:
		{
			SortSelect->Bubble();
		}break;

		case INSERT:
		{
			SortSelect->Insert();
		}break;

		case QUICK:
		{
			SortSelect->Quick();
		}break;
		case PRINT:
		{
			SortSelect->Print(SortSelect->GetNumber());
		}break;
		case EXIT:
		{
			iExit = false;
		}break;
		default:
		{
			cout << "���ǵ������� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���." << endl;
		}break;
		}
	}
	return 0;
}