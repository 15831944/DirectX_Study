#pragma once
#include <iostream>
struct HData
{
	int iIndex;
	int Data;
};
class SortAlgorithm
{
public:
	static SortAlgorithm* GetInstance();
	virtual void Sort(int iNum, HData* pData);
protected:
	SortAlgorithm();
public:
	virtual ~SortAlgorithm();
};