#pragma once
#include "dllStd.h"
class HObject
{
public:
	Interface* m_pMax;
	INode* m_pRootNode;
	Interval m_Interval;
	HScene m_Scene;
	vector<Mtl*> m_pMtrlList;
	vector<HMtrl> m_ExpMtrlList;
public:
	bool Initialize(Interface* pMax);
	void PreProcess(INode* pNode);
	void AddObject(INode* pNode);
	void AddMtrl(INode* pNode);
	HMtrl* GetMaterial();
	void GetTexture(HMtrl* AddMtrl, Mtl* pMtl);
public:
	HObject();
	virtual ~HObject();
};

