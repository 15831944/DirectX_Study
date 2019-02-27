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
	cout << "몇개의 랜덤한 데이터를 생성하시겠습니까 ? : ";
	cin >> iNumber;
	HSort* SortSelect = new HSort(iNumber);

	while (iExit)
	{
		cout << "(1) 버블정렬 (2) 셀렉트정렬 (3) 퀵정렬 (4) 출력 (99) 종료 : ";
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
			cout << "정의되지않은 번호를 입력하셨습니다. 다시 입력해주세요." << endl;
		}break;
		}
	}
	return 0;
}