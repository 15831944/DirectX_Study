#include "HSort.h"
int HSort::GetNumber()
{
	return m_iNumber;
}
bool HSort::InitData()
{
	for (int iNum = 0; iNum < m_iNumber; iNum++)
	{
		int Rnd = rand() % 42641;
		m_pData[iNum].Data = Rnd;
		m_pData[iNum].iIndex = iNum;
	}
	return true;
}
bool HSort::Print(int iNum)
{
	int Num = iNum;
	if (Num > m_iNumber) Num = m_iNumber;
	std::cout << Num <<"개가 출력됩니다." << std::endl;
	for (int i = 0; i < Num; i++)
	{
		std::cout << m_pData[i].iIndex<< " : "<<   m_pData[i].Data   << std::endl;
	}
	return true;
}
bool HSort::Bubble()
{
	m_pSort = BubbleSort::GetInstance();
	m_pSort->Sort(m_iNumber, m_pData);
	Print(50);
	return true;
}
bool HSort::Insert()
{
	m_pSort = InsertSort::GetInstance();
	m_pSort->Sort(m_iNumber, m_pData);
	Print(50);
	return true;
}
bool HSort::Quick()
{
	m_pSort = QuickSort::GetInstance();
	m_pSort->Sort(m_iNumber, m_pData);
	Print(50);
	return true;
}
HSort::HSort(int iNumber)
{
	m_iNumber = iNumber;
	m_pData = new HData[iNumber];
	InitData();
}
HSort::~HSort()
{
}
