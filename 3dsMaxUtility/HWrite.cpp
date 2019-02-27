#include "HWrite.h"

void HWrite::PreProcess(INode* pNode)
{

}
bool HWrite::Init(TSTR strFileName, Interface* pMax)
{
	m_strFileName = strFileName;
	return Initialize(pMax);
}
bool HWrite::Release()
{
	return true;
}
void HWrite::ExpScene()
{
	_ftprintf_s(m_pFile, L"FirstFrame, LastFrame, FrameSpeed, TickPerFrame\n");
	_ftprintf_s(m_pFile, L"*Scene %d %d %d %d\n", 
		&m_Scene.iFirstFrame,
		&m_Scene.iLastFrame,
		&m_Scene.iFrameSpeed,
		&m_Scene.iTickPerFrame);
}
void HWrite::ExpMaterial()
{
	_ftprintf_s(m_pFile, L"*Material " );
	for (int iRootMtrl = 0; iRootMtrl < m_pMtrlList.size(); iRootMtrl++)
	{
		_ftprintf_s(m_pFile, L"%s %d", L"#MATERIAL", m_ExpMtrlList[iRootMtrl].iIndex);
	}
}
void HWrite::ExpObject()
{

}
void HWrite::ExpAnimation()
{

}
bool HWrite::Export()
{
	_tfopen_s(&m_pFile, L"?", L"wt");
	ExpScene();
	ExpMaterial();
	ExpObject();
	fclose(m_pFile);
	return true;
}
//int HWrite::ExpMesh(FILE* pFile, HMesh* pMesh, int iMtrl = -1, int iAddCount = 0)
//{
//
//}
void HWrite::ExpTexture(vector<HTexMap>& TexMap)
{

}
int HWrite::IsEqulVertexList(vector<PNCT_VERTEX>& vertices, PNCT_VERTEX& vertex)
{
	return -1;
}

HWrite::HWrite()
{
}


HWrite::~HWrite()
{
}
