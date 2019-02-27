#include "TControlMgr.h"

void	TControlMgr::Save()
{
	FILE *File = fopen("Student_Data.txt", "w+");

	for (TNode<TStudent>* Temp = m_List.GetHead();
		Temp != NULL;
		Temp = Temp->m_pNext)
	{
		TStudent* Data		= Temp->m_pData;
		TSubject Subject = Data->GetSubject();
		fprintf(File, "%d\t %ws\t %d\t %d\t %d\t %d\t %f\t \n",
			Data->GetIndex(),
			Data->GetName().c_str(),
			Subject.GetKor(),
			Subject.GetMat(),
			Subject.GetEng(),
			Data->GetTotal(),
			Data->GetAverage());
	}

	fclose(File);
}
void	TControlMgr::Load()
{
	FILE *File = fopen("Student_Data.txt", "r+");
	while (!feof(File))
	{
		TStudent* pStudent = new TStudent();
		TCHAR name[256] = {0,};
		int iIndex, Kor, Mat, Eng, Sum;
		float Aver;
		fscanf(File, "%d%ws%d%d%d%d%f\n", 
			&iIndex, name, &Kor, &Mat, &Eng, &Sum, &Aver);
		wstring Name = name;
		pStudent->SetIndex(iIndex);
		pStudent->SetName(Name);
		pStudent->SetSubject(Kor, Eng, Mat);

		m_Hash.Insert(pStudent);
		m_List.AddLink(pStudent);
	}
	fclose(File);
}
template <typename T> void SwapPoint(T* a, T* b)
{
	a->m_pNext = b;
	b->m_pPrev = a;
}
TNode<TStudent>* TControlMgr::Swap(TNode<TStudent>* a, TNode<TStudent>* b) // 1, 2
{
	// NULL
	TNode<TStudent>* aprev = a->m_pPrev; 
	TNode<TStudent>* anext = a->m_pNext; 
	TNode<TStudent>* bprev = b->m_pPrev; 
	TNode<TStudent>* bnext = b->m_pNext; 

	//Head <-> b 
	if( aprev != NULL ) 
	{
		SwapPoint<TNode<TStudent>>(aprev, b);
#pragma region KGCA
		//aprev->m_pNext = b;
		//b->m_pPrev = aprev;
#pragma endregion
	}
	else
	{
		m_List.m_pHead = b;
		b->m_pPrev = NULL;
	}
	// b <-> c    anext(c)
	if( anext != b )	
	{
		SwapPoint<TNode<TStudent>>(b, anext);
#pragma region KGCA
		//b->m_pNext = anext; //  b -> c
		//anext->m_pPrev = b; //  b <- c
#pragma endregion
		// 초기 a -> c -> b 경우
		if( anext->m_pNext == b )
		{
			SwapPoint<TNode<TStudent>>(anext, a);
#pragma region 
			//anext->m_pNext = a; // c -> a		
			//a->m_pPrev = anext; // c <- a
#pragma endregion
		}
		else
		{
			SwapPoint<TNode<TStudent>>(bprev, a);
#pragma region 
			//bprev->m_pNext = a;
			//a->m_pPrev = bprev;
#pragma endregion
		}
	}
	else  // b <-> a
	{
		b->m_pNext = a;      // b -> a
		a->m_pPrev = b;      // b <- a
		a->m_pNext = bnext;  // a -> d
		if( bnext != NULL )	bnext->m_pPrev = a;  // a <- d		
	}
	// a <-> d  anext(d)  // 초기 a -> c -> b -> d 경우
	if( bnext != NULL )	
	{
		SwapPoint<TNode<TStudent>>(a, bnext);
#pragma region 
		//a->m_pNext = bnext;  // a -> d
		//bnext->m_pPrev = a;  // a <- d
#pragma endregion
	}
	else
	{
		a->m_pNext = NULL;  // a -> d
	}

	if( anext == b )	return a;
	return anext;
}

void TControlMgr::Sort(bool bUp)
{
	TNode<TStudent>* pNodeSrc  = m_List.GetHead();
	while(pNodeSrc && pNodeSrc->m_pNext )
	{
		TNode<TStudent>* pNodeSwap = pNodeSrc; 
		TStudent*  pStd = pNodeSwap->m_pData;  

		for(TNode<TStudent>*  pNodeDesk = pNodeSrc->m_pNext;	
			pNodeDesk != NULL;	pNodeDesk = pNodeDesk->m_pNext )
		{
			TStudent*  pDesk= pNodeDesk->m_pData;
			if( pNodeSwap->m_pData->GetTotal() > pDesk->GetTotal() )
			{
				pNodeSwap = pNodeDesk;			
			}
		}
		if(pNodeSrc != pNodeSwap )
		{
			pNodeSrc = Swap( pNodeSrc, pNodeSwap);			
		}
		else		
		{
			pNodeSrc = pNodeSrc->m_pNext;
		}
	}
	m_List.m_pTail = pNodeSrc;
}
TStudent* TControlMgr::Find(int iCnt)
{	
	TStudent* pData = m_List.GetData(iCnt);
	return pData;	
}
void TControlMgr::ShowData()
{	
	for(TNode<TStudent>*  pNode=m_List.GetHead();
					pNode != NULL;
					pNode = pNode->m_pNext )
	{
		TStudent*  pData= pNode->m_pData;
		if( pData )
		{
			wcout << pData->GetIndex() 
				<< L"   " 
				<< pData->GetName() 
				<< L"   " 
				<< pData->GetTotal() << endl;
		}
	}
}
bool    TControlMgr::ShowData(TStudent* pStd)
{
	if (pStd == NULL) return false;
	wcout << " ========= " << pStd->GetIndex() << " "
		<< pStd->GetName().c_str() << " "
		<< pStd->GetSubject().GetKor() << " "
		<< pStd->GetSubject().GetEng() << " "
		<< pStd->GetSubject().GetMat() << " "
		<< pStd->GetTotal() << " "
		<< endl;
	return true;
}
bool TControlMgr::InputData(int iCnt)
{
	for( int iSt=0; iSt < iCnt; iSt++)
	{		
		TStudent* pStudent = new TStudent;
		wstring name;
		for( int iname =0; iname < 3; iname++ )
		{
			char iName = 65+rand()%26;
			name += iName;
		}
		pStudent->SetIndex(iSt);
		pStudent->SetName(name);
		pStudent->SetSubject( rand() %100,rand() %100,rand() %100 );
				
		m_Hash.Insert(pStudent);
		m_List.AddLink( pStudent );
	}
	return true;
}
void TControlMgr::Release()
{
	m_List.Delete();
}
TControlMgr::TControlMgr(void)
{
}


TControlMgr::~TControlMgr(void)
{
}
