#pragma once
#include "SortAlgorithm.h"
class InsertSort : public SortAlgorithm
{
public:
	static InsertSort* GetInstance();
	void Sort(int iNum, HData* pData);
protected:
	InsertSort();
public:
	virtual ~InsertSort();
private:
	static InsertSort * m_pInstance;
};

