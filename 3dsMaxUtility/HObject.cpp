#include "HObject.h"

bool HObject::Initialize(Interface* pMax)
{
	if (pMax == NULL && m_pMax == NULL) return false;
	m_pMax = pMax;
	m_pRootNode = pMax->GetRootNode();

	/* Scene */
	m_Interval = m_pMax->GetAnimRange();
	m_Scene.iFirstFrame = m_Interval.Start() / GetTicksPerFrame();
	m_Scene.iLastFrame = m_Interval.End() / GetTicksPerFrame();
	m_Scene.iFrameSpeed = GetFrameRate();
	m_Scene.iTickPerFrame = GetTicksPerFrame();

	PreProcess(pMax->GetRootNode());


	return true;
}
void HObject::PreProcess(INode* pNode)
{
	if (pNode == NULL) return;

	AddMtrl(pNode);
	AddObject(pNode);

	/* pNode의 Child 개수 */
	int iChildLen = pNode->NumberOfChildren();
	for (int iCnt = 0; iCnt < iChildLen; iCnt++)
	{
		INode* pChild = pNode->GetChildNode(iCnt);
		PreProcess(pChild);
	}
}
void HObject::AddObject(INode* pNode)
{
	ObjectState os = pNode->EvalWorldState(m_Interval.Start());
	if (os.obj)
	{
		if (os.obj->ClassID() == Class_ID(TARGET_CLASS_ID, 0)) return;

		/* Geom */
		if (os.obj->SuperClassID() == GEOMOBJECT_CLASS_ID)
		{

		}
		/* HelperObject */
		if (os.obj->SuperClassID() == HELPER_CLASS_ID)
		{
			
		}
	}
}
void HObject::AddMtrl(INode* pNode)
{
	if (pNode->GetMtl() == NULL) return;

	Mtl* pMtrl = pNode->GetMtl();
	bool bAdd = true;
	for (int iCnt = 0; iCnt < m_pMtrlList.size(); iCnt++)
	{
		/* Mtrl 중복제거 */
		if (m_pMtrlList[iCnt] == pMtrl)
		{
			bAdd = false;
			break;
		}
	}
	if (bAdd)
	{
		m_pMtrlList.push_back(pMtrl);
	}
}
HMtrl* HObject::GetMaterial()
{
	for (int iMtrl = 0; iMtrl < m_pMtrlList.size(); iMtrl++)
	{
		Mtl* pMtrl = m_pMtrlList[iMtrl];
		HMtrl Add;
		TSTR className;
		pMtrl->GetClassName(className);

		Add.iIndex = iMtrl;
		Add.strClassName = className;
		Add.strName = pMtrl->GetName();
		Add.iNumSubMtrl = pMtrl->NumSubMtls();
		if (pMtrl->NumSubMtls() > 0)
		{
			for (int iSubMtrl = 0; iSubMtrl < pMtrl->NumSubMtls(); iSubMtrl++)
			{
				TSTR subClassName;
				Mtl* pSubMtrl = pMtrl->GetSubMtl(iSubMtrl);
				pSubMtrl->GetClassName(subClassName);
				HMtrl AddSub;
				AddSub.iIndex = iSubMtrl;
				AddSub.strName = pSubMtrl->GetName();
				AddSub.iNumSubMtrl = pSubMtrl->NumSubMtls();
				AddSub.strClassName = className;
				if (pSubMtrl->NumSubMtls() > 0)
				{
					
				}
				if (pSubMtrl)
				{
					GetTexture(&AddSub, pSubMtrl);
				}
			}
		}
		else
		{
			m_ExpMtrlList.push_back(Add);
		}
	}
	HMtrl* mtrl = new HMtrl();
	return mtrl;
}
void HObject::GetTexture(HMtrl* AddMtrl, Mtl* pMtl)
{
	for (int iSubMap = 0; iSubMap < pMtl->NumSubTexmaps(); iSubMap++)
	{
		Texmap* pTex = pMtl->GetSubTexmap(iSubMap);
		if (pTex)
		{
			/* 3dsMax에서 이 텍스쳐를 적용 중인지 판단 */
			if (pMtl->ClassID() == Class_ID(DMTL_CLASS_ID, 0))
			{
				StdMat* std = (StdMat*)pMtl;
				if (!std->MapEnabled(iSubMap)) continue;
			}
		}

		HTexMap TexMap;
		TexMap.iType = iSubMap;
		if (pTex->ClassID() == Class_ID(BMTEX_CLASS_ID, 0x00))
		{
			TSTR mapName = ((BitmapTex*)pTex)->GetMapName();
			TSTR strFullName;
			SplitPathFile(mapName, &strFullName, &mapName);
			TexMap.szTexName = mapName;
		}
		AddMtrl->TexMapList.push_back(TexMap);
		AddMtrl->iNumMap = AddMtrl->TexMapList.size();
	}
}
HObject::HObject()
{
}


HObject::~HObject()
{
}
