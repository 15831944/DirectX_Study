#include "BubbleSort.h"
BubbleSort* BubbleSort::m_pInstance = NULL;

BubbleSort* BubbleSort::GetInstance()
{
	if (m_pInstance == NULL) 
		m_pInstance = new BubbleSort;
	return m_pInstance;
}
void BubbleSort::Sort(int iNum, HData* pData)
{
	for (int i = 0; i < iNum - 1; i++)
	{
		for (int j = 0; j < iNum - 1 - i; j++)
		{
			if (pData[j + 1].Data < pData[j].Data)
			{
				HData Temp = pData[j + 1];
				pData[j + 1] = pData[j];
				pData[j] = Temp;
			}
		}
	}
}

BubbleSort::BubbleSort()
{
}


BubbleSort::~BubbleSort()
{
}
