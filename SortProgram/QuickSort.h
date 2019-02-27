#pragma once
#include "SortAlgorithm.h"

class QuickSort : public SortAlgorithm
{
public:
	static QuickSort* GetInstance();
	void Sort(int iNum, HData* pData);
	void CalcQuick(HData* pData, int iLow, int iHigh);
	void Swap(HData* pSrcData, HData* pDeskData);
protected:
	QuickSort();
public:	
	virtual ~QuickSort();
private:
	static QuickSort* m_pInstance;
};