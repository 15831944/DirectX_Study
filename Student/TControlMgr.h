#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include "THashTable.cpp"
#include "TStudent.h"

class TControlMgr
{
public:
	TLinkedList<TStudent> m_List;
	THashTable<TStudent>    m_Hash;
private:
	TLinkedList<TStudent>   m_InitList;
public:
	bool	InputData(int iCnt=10);
	void	ShowData();
	bool    ShowData(TStudent* pStd);
	void	Save();
	void	Load();
	void	Release();
	void	Sort(bool bUp=true);
	TStudent* Find(int iCnt);
	TNode<TStudent>* Swap(	TNode<TStudent>*a, 
							TNode<TStudent>*b); 
public:
	TControlMgr(void);
	virtual ~TControlMgr(void);
};

