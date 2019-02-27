#include "InsertSort.h"

InsertSort* InsertSort::m_pInstance = NULL;

InsertSort* InsertSort::GetInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new InsertSort;
	return m_pInstance;
}
void InsertSort::Sort(int iNum, HData* pData)
{
	int j;
	for (int i = 1; i < iNum; i++)
	{
		HData Temp = pData[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (pData[j].Data > Temp.Data)
			{
				pData[j + 1] = pData[j];
			}
			else
			{
				break;
			}
		}
		pData[j + 1] = Temp;
	}
}

InsertSort::InsertSort()
{
}


InsertSort::~InsertSort()
{
}
