#include "TSubject.h"
void	TSubject::Set( int iKor, int iEng, int iMat )
{
	m_iKor = iKor;
	m_iEng = iEng;
	m_iMat = iMat;
};
int		TSubject::GetKor()
{
	return m_iKor;
};
int		TSubject::GetEng(){
	return m_iEng;
};
int		TSubject::GetMat(){
	return m_iMat;
};

TSubject::TSubject(void)
{
	m_iKor = 0;
	m_iEng = 0;
	m_iMat = 0;
}


TSubject::~TSubject(void)
{
}
