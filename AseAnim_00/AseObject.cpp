#include "AseObject.h"
bool AseObject::Init()
{
	D3DXQUATERNION  q;
	D3DXVECTOR3     vS,vT;
	D3DXMatrixDecompose(&vS,&q,&vT, &m_matWorld);
	return true;
}
bool AseObject::Frame()
{
	m_fCurrentTick += g_fSecPerFrame * 1.0f * m_Scene.iFrameSpeed * m_Scene.iTickPerFrame;
	if (m_fCurrentTick >= m_Scene.iLastFrame* m_Scene.iTickPerFrame)
	{
		m_fCurrentTick = m_Scene.iFirstFrame * m_Scene.iTickPerFrame;
	}

	D3DXQUATERNION qR, qS;
	D3DXMatrixIdentity(&m_matCalc);
	D3DXMATRIX matAnim, matPos, matRotate, matScale;

	matRotate = m_matRotate;
	matPos = m_matTrans;
	matScale = m_matScale;

	D3DXQuaternionRotationMatrix(&qR, &matRotate);
	D3DXQuaternionRotationMatrix(&qS, &matScale);

	// fFrameTick = m_Scene.iFirstFrame * m_Scene.iTickPerFrame + CurFame;
	float fStartTick = m_Scene.iFirstFrame * m_Scene.iTickPerFrame;
	float fEndTick = 0.0f;

	TRACK* pStartTrack = NULL;
	TRACK* pEndTrack = NULL;
	if (m_pRot.size())
	{
		// pStartTrack를 찾을수 있으면
		if (FindCurrentTrack(m_pRot, m_fCurrentTick, &pStartTrack, &pEndTrack))
		{
			qR = pStartTrack->qRot;
			fStartTick = pStartTrack->iTick;
		}
		if (pEndTrack)
		{
			fEndTick = pEndTrack->iTick;
			D3DXQuaternionSlerp(&qR, &qR, &pEndTrack->qRot, (m_fCurrentTick - fStartTick) / (fEndTick - fStartTick));
		}
		D3DXMatrixRotationQuaternion(&matRotate, &qR);
	}

	pStartTrack = NULL;
	pEndTrack = NULL;

	D3DXVECTOR3 Trans(matPos._41, matPos._42, matPos._43);
	if (m_pPos.size())
	{
		// pStartTrack를 찾을수 있으면
		if (FindCurrentTrack(m_pPos, m_fCurrentTick, &pStartTrack, &pEndTrack))
		{
			Trans = pStartTrack->vPos;
			fStartTick = pStartTrack->iTick;
		}
		if (pEndTrack)
		{
			fEndTick = pEndTrack->iTick;
			D3DXVec3Lerp(&Trans, &Trans, &pEndTrack->vPos, (m_fCurrentTick - fStartTick) / (fEndTick - fStartTick));
		}

		D3DXMatrixTranslation(&matPos, Trans.x, Trans.y, Trans.z);
	}


	pStartTrack = NULL;
	pEndTrack = NULL;

	D3DXMATRIX matScaleRot, matInvScaleRot;
	D3DXVECTOR3 vScale(matScale._11, matScale._22, matScale._33);
	if (m_pScale.size())
	{
		// pStartTrack를 찾을수 있으면
		if (FindCurrentTrack(m_pScale , m_fCurrentTick, &pStartTrack, &pEndTrack))
		{
			vScale = pStartTrack->vPos;
			qS = pStartTrack->qRot;
			fStartTick = pStartTrack->iTick;
		}
		if (pEndTrack)
		{
			fEndTick = pEndTrack->iTick;
			D3DXVec3Lerp(&vScale, &vScale, &pEndTrack->vPos, (m_fCurrentTick - fStartTick) / (fEndTick - fStartTick));
			D3DXQuaternionSlerp(&qS, &qS, &pEndTrack->qRot, (m_fCurrentTick - fStartTick) / (fEndTick - fStartTick));
		}
		D3DXMATRIX matScl;
		D3DXMatrixScaling(&matScl, vScale.x, vScale.y, vScale.z);
		D3DXMatrixRotationQuaternion(&matScaleRot, &qS);
		D3DXMatrixInverse(&matInvScaleRot, NULL, &matScaleRot);
		matScale = matInvScaleRot * matScl * matScaleRot;
	}
	D3DXMatrixMultiply(&m_matCalc, &matScale, &matRotate);
	m_matCalc._41 = matPos._41;
	m_matCalc._42 = matPos._42;
	m_matCalc._43 = matPos._43;
	//m_matCalc = matRotate * matScale *matPos;
	return true;
}
bool AseObject::Render(ID3D11DeviceContext* context)
{
	//for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
	//{
	//	if (m_Mtrl[iMtrl].subMtrl.size() > 0)
	//	{
	//		for (int iSubMtrl = 0; iSubMtrl < m_Mtrl[iMtrl].subMtrl.size(); iSubMtrl++)
	//		{
	//			context->UpdateSubresource(m_SubAseObj[iSubMtrl].m_dxObj.m_pConstantBuffer, 0, NULL, &m_SubAseObj[iSubMtrl].m_cbData, 0, 0);
	//			m_SubAseObj[iSubMtrl].m_dxObj.Render(context);
	//		}
	//	}
	//	else
	//	{
	//		context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	//		m_dxObj.Render(context);
	//	}
	//}
	return true;
}
bool AseObject::Draw(ID3D11DeviceContext* context, D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	for (int iMtrl = 0; iMtrl < m_pMesh.size(); iMtrl++)
	{
		for (int iSubMtrl = 0; iSubMtrl < m_pMesh[iMtrl].m_pSubMeshList.size(); iSubMtrl++)
		{
			m_pMesh[iMtrl].m_pSubMeshList[iSubMtrl].SetMatrix(&m_matCalc, matView, matProj);
			context->UpdateSubresource(m_pMesh[iMtrl].m_pSubMeshList[iSubMtrl].m_dxObj.m_pConstantBuffer, 0, NULL, &m_pMesh[iMtrl].m_pSubMeshList[iSubMtrl].m_cbData, 0, 0);
			m_pMesh[iMtrl].m_pSubMeshList[iSubMtrl].m_dxObj.Render(context);
		}
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
bool AseObject::FindCurrentTrack(vector<TRACK*> track, float tick, TRACK** start, TRACK** end)
{
	for (int iTrack = 0; iTrack < track.size(); iTrack++)
	{
		TRACK* md = track[iTrack];
		if (md->iTick > tick)
		{
			*end = md;
			break;
		}
		*start = md;

	}
	return (*start != NULL) ? true : false;
}
bool AseObject::Interpolate(float fCurrentTick)
{
	return true;
}
bool AseObject::SetData()
{
	m_pMesh = m_Paser.GetData();
	m_Scene = m_Paser.m_Scene;
	m_pPos = m_Paser.GetPos();
	m_pRot = m_Paser.GetRot();
	m_pScale = m_Paser.GetScl();
	m_matWorld = m_Paser.matWorld;
	if (m_pMesh.size() < 0) return false;
	m_Paser.clear();

	// MATRIX
	D3DXQUATERNION rot;
	D3DXVECTOR3 trans, scl;
	D3DXMatrixDecompose(&scl, &rot, &trans, &m_matWorld);

	D3DXMatrixTranslation(&m_matTrans, trans.x, trans.y, trans.z);
	D3DXMatrixRotationQuaternion(&m_matRotate, &rot);
	D3DXMatrixScaling(&m_matScale, scl.x, scl.y, scl.z);
	return true;
}
bool AseObject::Load(ID3D11Device* device, const TCHAR* AseFileName)
{
	if (!m_Paser.LoadAseFile(AseFileName)) return false;
	if (!m_Paser.Load()) return false;
	if (!SetData()) return false;
	for (int iMesh = 0; iMesh < m_pMesh.size(); iMesh++)
	{
		for (int iSubMesh = 0; iSubMesh < m_pMesh[iMesh].m_pSubMeshList.size(); iSubMesh++)
		{
			if (!m_pMesh[iMesh].m_pSubMeshList[iSubMesh].Create(device)) return false;
		}
	}
	return true;
}
AseObject::AseObject()
{

}
AseObject::~AseObject()
{

}