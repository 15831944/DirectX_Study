#include "AseObject.h"
bool AseObject::Init()
{
	return true;
}
bool AseObject::Frame()
{
	/* Tick ´©Àû */
	m_fCurrentTick += g_fSecPerFrame * 0.5f * m_Scene.iFrameSpeed * m_Scene.iTickPerFrame *2.0f;
	if (m_fCurrentTick >= m_Scene.iLastFrame* m_Scene.iTickPerFrame)
	{
		m_fCurrentTick = m_Scene.iFirstFrame * m_Scene.iTickPerFrame;
	}
	//m_fCurrentTick = 0.0f;
	for (int iMesh = 0; iMesh < m_pMesh.size(); iMesh++)
	{
		JMesh* pMesh = m_pMesh[iMesh];
		D3DXMATRIX matParent;
		D3DXMatrixIdentity(&matParent);
		if (pMesh->m_pParent)
		{
			matParent = pMesh->m_pParent->m_matCalc;
			Interpolate(pMesh, m_fCurrentTick, matParent);
			continue;
		}
		Interpolate(pMesh, m_fCurrentTick, matParent);
	}
	return true;
}
bool AseObject::Render(ID3D11DeviceContext* context)
{
	return true;
}
bool AseObject::Draw(ID3D11DeviceContext* context, D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	for (int iMesh = 0; iMesh < m_pMesh.size(); iMesh++)
	{
		//if (m_pMesh[iMesh]->m_pParent == NULL) continue;
		m_pMesh[iMesh]->Draw(context, matWorld, matView, matProj);
	}
	return true;
}
bool AseObject::Release()
{
	//for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
	//{
	//	for (int iSubMtrl = 0; iSubMtrl < m_Mtrl[iMtrl].subMtrl.size(); iSubMtrl++)
	//	{
	//		m_SubAseObj[iSubMtrl].m_dxObj.Release();
	//	}
	//}
	//m_dxObj.Release();
	return true;
}
bool AseObject::SetData()
{
	m_pMesh = m_Paser.GetData();
	m_Scene = m_Paser.m_Scene;
	return true;
}
bool AseObject::Load(ID3D11Device* device, const TCHAR* AseFileName)
{
	if (!m_Paser.LoadAseFile(AseFileName)) return false;
	if (!m_Paser.Load()) return false;
	if (!SetData()) return false;
	for (int iMesh = 0; iMesh < m_pMesh.size(); iMesh++)
	{
		for (int iSubMesh = 0; iSubMesh < m_pMesh[iMesh]->m_pSubMeshList.size(); iSubMesh++)
		{
			if(m_pMesh[iMesh]->m_pSubMeshList[iSubMesh].m_pVertexList.size() > 0)
				m_pMesh[iMesh]->m_pSubMeshList[iSubMesh].Create(device);
		}
	}
	return true;
}
bool AseObject::Interpolate(JMesh* pMesh, float fCurrentTick, D3DXMATRIX matParentCalc)
{
	D3DXQUATERNION qR, qS;
	D3DXMatrixIdentity(&pMesh->m_matCalc);
	D3DXMATRIX matPos, matRotate, matScale;

	matRotate = pMesh->m_matLocalRotate;
	matPos =	pMesh->m_matLocalTrans;
	matScale =  pMesh->m_matLocalScale;

	D3DXQuaternionRotationMatrix(&qR, &matRotate);
	D3DXQuaternionRotationMatrix(&qS, &matScale);

	float fStartTick = m_Scene.iFirstFrame * m_Scene.iTickPerFrame;
	float fEndTick = 0.0f;

	AnimTrack* pStartTrack = NULL;
	AnimTrack* pEndTrack = NULL;
	if (pMesh->m_pRotateTrack.size())
	{
		for (int iTrack = 0; iTrack < pMesh->m_pRotateTrack.size(); iTrack++)
		{
			AnimTrack* md = pMesh->m_pRotateTrack[iTrack];
			if (md->iTick > fCurrentTick)
			{
				pEndTrack = md;
				break;
			}
			pStartTrack = md;
		}
		if (pStartTrack)
		{
			qR = pStartTrack->qRot;
			fStartTick = pStartTrack->iTick;
		}
		if (pEndTrack)
		{
			fEndTick = pEndTrack->iTick;
			D3DXQuaternionSlerp(&qR, &qR, &pEndTrack->qRot, (fCurrentTick - fStartTick) / (fEndTick - fStartTick));
		}
		D3DXMatrixRotationQuaternion(&matRotate, &qR);
	}

	pStartTrack = NULL;
	pEndTrack = NULL;

	D3DXVECTOR3 Trans(matPos._41, matPos._42, matPos._43);
	if (pMesh->m_pTransTrack.size())
	{
		for (int iTrack = 0; iTrack < pMesh->m_pTransTrack.size(); iTrack++)
		{
			AnimTrack* md = pMesh->m_pTransTrack[iTrack];
			if (md->iTick > fCurrentTick)
			{
				pEndTrack = md;
				break;
			}
			pStartTrack = md;
		}
		if (pStartTrack)
		{
			Trans = pStartTrack->vPos;
			fStartTick = pStartTrack->iTick;
		}
		if (pEndTrack)
		{
			fEndTick = pEndTrack->iTick;
			D3DXVec3Lerp(&Trans, &Trans, &pEndTrack->vPos, (fCurrentTick - fStartTick) / (fEndTick - fStartTick));
		}

		D3DXMatrixTranslation(&matPos, Trans.x, Trans.y, Trans.z);
	}


	pStartTrack = NULL;
	pEndTrack = NULL;

	D3DXMATRIX matScaleRot, matInvScaleRot;
	D3DXVECTOR3 vScale(matScale._11, matScale._22, matScale._33);
	if (pMesh->m_pScaleTrack.size())
	{
		for (int iTrack = 0; iTrack < pMesh->m_pScaleTrack.size(); iTrack++)
		{
			AnimTrack* md = pMesh->m_pScaleTrack[iTrack];
			if (md->iTick > fCurrentTick)
			{
				pEndTrack = md;
				break;
			}
			pStartTrack = md;
		}
		if (pStartTrack)
		{
			vScale = pStartTrack->vPos;
			qS = pStartTrack->qRot;
			fStartTick = pStartTrack->iTick;
		}
		if (pEndTrack)
		{
			fEndTick = pEndTrack->iTick;
			D3DXVec3Lerp(&vScale, &vScale, &pEndTrack->vPos, (fCurrentTick - fStartTick) / (fEndTick - fStartTick));
			D3DXQuaternionSlerp(&qS, &qS, &pEndTrack->qRot, (fCurrentTick - fStartTick) / (fEndTick - fStartTick));
		}
		D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
		D3DXMatrixRotationQuaternion(&matScaleRot, &qS);
		D3DXMatrixInverse(&matInvScaleRot, NULL, &matScaleRot);
		matScale = matInvScaleRot * matScale * matScaleRot;
	}
	//pMesh->m_matCalc = pMesh->m_matLocalScale * pMesh->m_matLocalRotate * pMesh->m_matLocalTrans * pMesh->m_pParent->m_matCalc;
	pMesh->m_matCalc = matScale * matRotate * matPos * matParentCalc;
	//D3DXMatrixMultiply(&pMesh->m_matCalc, &matAnim, &matParentCalc);
	return true;
}
AseObject::AseObject()
{

}
AseObject::~AseObject()
{

}