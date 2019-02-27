#pragma once
#define MAX_DATA_NUMBER 1000
#include "SortAlgorithm.h"
#include "BubbleSort.h"
#include "InsertSort.h"
#include "QuickSort.h"

class HSort
{
public:
	bool InitData();
	bool Print(int iNum);
	bool Bubble();
	bool Insert();
	bool Quick();
	int GetNumber();
public:
	HSort(int iNumber);
	virtual ~HSort();
private:
	HData* m_pData;
	int  m_iNumber;
	SortAlgorithm* m_pSort;
};