#pragma once
#include "SortAlgorithm.h"
class BubbleSort : public SortAlgorithm
{
public:
	static BubbleSort* GetInstance();
	void Sort(int iNum, HData* pData);
protected:
	BubbleSort();
public:
	virtual ~BubbleSort();
private:
	static BubbleSort* m_pInstance;
};