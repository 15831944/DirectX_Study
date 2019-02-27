#pragma once
#include "ExpObject.h"
class ExpWrite : public JSingleton<ExpWrite>, public ExpObject
{
public:
	FILE*	m_pStream;	// ��� ���� ������
	TSTR	m_strFileName;	// ��� �� ���ϸ�
public:
	bool 	Init(TSTR strFileName, Interface* pMax); // �ʱ�ȭ
	bool	RunExport(const TCHAR* FileName);		// ���� ���
	bool	Release();		// �޸� �Ҹ� �� ����	
	//��� ���� ���� ��ȭ����
	//TCHAR*	SaveFileDlg(TCHAR* szExt, TCHAR* szTitle = _T("Exporter"));
	void	ExpScene();
	void	ExpMaterial();
	void	ExpObject();
	//int		ExpMesh(FILE* fp, JMesh* pMesh, int iMtrl = -1, int iAddCount = 0);
	void	ExpAnimation(JMesh* pMesh);
	void	ExpTexture(vector<JTexMap>& TexMap);
	//int		IsEqulVertexList(vector<PNCT_VERTEX>&  VertexArray, PNCT_VERTEX& Vertex);
	//int		SetUniqueBuffer(JMesh* pMesh, int iMtrl, int iStartTri, vector <PNCT_VERTEX>& VertexArray, vector<int>& IndexArray);
	//void	matExport();
public:
	ExpWrite();
	virtual ~ExpWrite();
};
#define I_Writer ExpWrite::GetInstance()
