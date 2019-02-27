#pragma once
#include "HObject.h"
class HWrite : public HObject, public JSingleton<HWrite>
{
public:
	FILE* m_pFile;
	TSTR  m_strFileName;
public:
	void PreProcess(INode* pNode);
	bool Init(TSTR strFileName, Interface* pMax);
	bool Release();
public:
	void ExpScene();
	void ExpMaterial();
	void ExpObject();
	void ExpAnimation();
	bool Export();
	//int ExpMesh(FILE* pFile, HMesh* pMesh, int iMtrl = -1, int iAddCount = 0);
	void ExpTexture(vector<HTexMap>& TexMap);
	int IsEqulVertexList(vector<PNCT_VERTEX>& vertices, PNCT_VERTEX& vertex);
private:
	friend class JSingleton<HWrite>;
public:
	HWrite();
	virtual ~HWrite();
};
#define I_HWrite HWrite::GetInstance()