#include "QuickSort.h"

QuickSort* QuickSort::m_pInstance = NULL;

QuickSort* QuickSort::GetInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new QuickSort;
	return m_pInstance;
}
void QuickSort::Sort(int iNum, HData* pData)
{
	CalcQuick(pData, 0, iNum - 1);
}
void  QuickSort::Swap(HData* pSrcData, HData* DeskpData)
{
	HData Temp = *pSrcData;
	*pSrcData = *DeskpData;
	*DeskpData = Temp;
}
void  QuickSort::CalcQuick(HData* pData, int iLow, int iHigh)
{
	int iPivot = pData[iLow].Data;
	int iStart = iLow;
	int iEnd = iHigh;
	while (iLow < iHigh)
	{
		while (iPivot <= pData[iHigh].Data && iLow < iHigh)
		{
			iHigh--;
		}
		if (iLow > iHigh) break;
		while (iPivot >= pData[iLow].Data && iLow < iHigh)
		{
			iLow++;
		}
		if (iLow > iHigh) break;
		Swap(&pData[iLow], &pData[iHigh]);
	}
	Swap(&pData[iStart], &pData[iLow]);

	if (iStart < iLow)
		CalcQuick(pData, iStart, iLow - 1);
	if (iEnd > iHigh)
		CalcQuick(pData, iLow + 1, iEnd);
}
QuickSort::QuickSort()
{
}


QuickSort::~QuickSort()
{
}
