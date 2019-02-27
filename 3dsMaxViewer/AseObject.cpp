#include "AseObject.h"
bool AseObject::Init()
{
	return true;
}
bool AseObject::Frame()
{
	/* Tick 누적 */
	m_fCurrentTick += g_fSecPerFrame * m_Scene.iFrameSpeed * m_Scene.iTickPerFrame;
	if (m_fCurrentTick >= m_Scene.iLastFrame* m_Scene.iTickPerFrame)
	{
		m_fCurrentTick = m_Scene.iFirstFrame * m_Scene.iTickPerFrame;
	}
	//m_fCurrentTick = 0.0f;
	//for (int iMesh = 0; iMesh < m_pMesh.size(); iMesh++)
	//{
	//	JMesh* pMesh = m_pMesh[iMesh];
	//	D3DXMATRIX matParent;
	//	D3DXMatrixIdentity(&matParent);
	//	if (pMesh->m_pParent)
	//	{
	//		matParent = pMesh->m_pParent->m_matCalc;
	//		Interpolate(pMesh, m_fCurrentTick, matParent);
	//		continue;
	//	}
	//	Interpolate(pMesh, m_fCurrentTick, matParent);
	//}
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	for (DWORD dwObject = 0; dwObject < m_pMesh.size(); dwObject++)
	{
		JMesh* pMesh = m_pMesh[dwObject];
		if (pMesh->m_pParent)
			Interpolate(pMesh, &pMesh->m_pParent->m_matCalc, m_fCurrentTick);
		else
			Interpolate(pMesh, &mat, m_fCurrentTick);
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
		m_pMesh[iMesh]->Draw(context, matWorld, matView, matProj);
	}
	return true;
}
bool AseObject::Release()
{
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
bool AseObject::Interpolate(JMesh* pMesh, D3DXMATRIX* matParents, float fCurrentTick)
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
	pMesh->m_matCalc = matScale * matRotate * matPos * (*matParents);
	//D3DXMatrixMultiply(&pMesh->m_matCalc, &matAnim, &matParentCalc);



	//D3DXQUATERNION qR, qS;
	//D3DXMatrixIdentity(&pMesh->m_matCalc);
	//D3DXMATRIX matAnim, matPos, matRotate, matScale;

	//matRotate = pMesh->m_matLocalRotate;
	//matPos = pMesh->m_matLocalTrans;
	//matScale = pMesh->m_matLocalScale;

	//D3DXQuaternionRotationMatrix(&qR, &matRotate);
	//D3DXQuaternionRotationMatrix(&qS, &matScale);

	//float fStartTick = m_Scene.iFirstFrame * m_Scene.iTickPerFrame;
	//float fEndTick = 0.0f;

	//AnimTrack* pStartTrack = NULL;
	//AnimTrack* pEndTrack = NULL;
	//if (pMesh->m_pRotateTrack.size())
	//{
	//	if (GetAnimationTrack(fCurrentTick, pMesh->m_pRotateTrack, &pStartTrack, &pEndTrack))
	//	{
	//		qR = pStartTrack->qRot;
	//		fStartTick = pStartTrack->iTick;
	//	}
	//	if (pEndTrack)
	//	{
	//		fEndTick = pEndTrack->iTick;
	//		D3DXQuaternionSlerp(&qR, &qR, &pEndTrack->qRot, (fCurrentTick - fStartTick) / (fEndTick - fStartTick));
	//	}
	//	D3DXMatrixRotationQuaternion(&matRotate, &qR);
	//}

	//pStartTrack = NULL;
	//pEndTrack = NULL;

	//D3DXVECTOR3 Trans(matPos._41, matPos._42, matPos._43);
	//if (pMesh->m_pTransTrack.size())
	//{
	//	if (GetAnimationTrack(fCurrentTick, pMesh->m_pTransTrack, &pStartTrack, &pEndTrack))
	//	{
	//		Trans = pStartTrack->vPos;
	//		fStartTick = pStartTrack->iTick;
	//	}
	//	if (pEndTrack)
	//	{
	//		fEndTick = pEndTrack->iTick;
	//		D3DXVec3Lerp(&Trans, &Trans, &pEndTrack->vPos, (fCurrentTick - fStartTick) / (fEndTick - fStartTick));
	//	}

	//	D3DXMatrixTranslation(&matPos, Trans.x, Trans.y, Trans.z);
	//}


	//pStartTrack = NULL;
	//pEndTrack = NULL;

	//D3DXMATRIX matScaleRot, matInvScaleRot;
	//D3DXVECTOR3 vScale(matScale._11, matScale._22, matScale._33);
	//if (pMesh->m_pScaleTrack.size())
	//{
	//	if (GetAnimationTrack(fCurrentTick, pMesh->m_pScaleTrack, &pStartTrack, &pEndTrack))
	//	{
	//		vScale = pStartTrack->vPos;
	//		qS = pStartTrack->qRot;
	//		fStartTick = pStartTrack->iTick;
	//	}
	//	if (pEndTrack)
	//	{
	//		fEndTick = pEndTrack->iTick;
	//		D3DXVec3Lerp(&vScale, &vScale, &pEndTrack->vPos, (fCurrentTick - fStartTick) / (fEndTick - fStartTick));
	//		D3DXQuaternionSlerp(&qS, &qS, &pEndTrack->qRot, (fCurrentTick - fStartTick) / (fEndTick - fStartTick));
	//	}
	//	D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
	//	D3DXMatrixRotationQuaternion(&matScaleRot, &qS);
	//	D3DXMatrixInverse(&matInvScaleRot, NULL, &matScaleRot);
	//	matScale = matInvScaleRot * matScale * matScaleRot;
	//}

	//pStartTrack = NULL;
	//pEndTrack = NULL;

	//D3DXMatrixMultiply(&matAnim, &matScale, &matRotate);
	//matAnim._41 = matPos._41;
	//matAnim._42 = matPos._42;
	//matAnim._43 = matPos._43;
	//D3DXMatrixMultiply(&pMesh->m_matCalc, &matAnim, matParents);

	return true;
}
bool AseObject::GetAnimationTrack(float fFrame, vector<AnimTrack*> pTrackList, AnimTrack** pStartTrack, AnimTrack** pEndTrack)
{
	for (DWORD dwTrack = 0; dwTrack < pTrackList.size(); dwTrack++)
	{
		AnimTrack *pTrack = pTrackList[dwTrack];
		_ASSERT(pTrack);
		// fFrame 보다 큰 Tick 트랙이 있다면 이전 트랙을 넘겨 주어야 하기 때문에 break한다.
		if (pTrack->iTick > fFrame)
		{
			*pEndTrack = pTrack;
			break;
		}
		// 현프레임보다 큰값이 없다면. 가장 시간경과가 오래된 것을 사용한다.
		*pStartTrack = pTrack;
	}
	return (*pStartTrack != NULL) ? true : false;
}
AseObject::AseObject()
{

}
AseObject::~AseObject()
{

}