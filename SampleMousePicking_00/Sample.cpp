#define _CRT_SECURE_NO_WARNINGS
#include "JCore.h"
#include "JLineShape.h"
#include "JPlaneShape.h"
#include "MousePicking.h"
class Sample : public JCore
{
public:
	MousePicking MP;
	JPlaneShape m_Plane;
	D3DXMATRIX m_PlaneWorld;
	TCHAR Buf[256];
	JLineShape m_Line;
public:
	bool Init()
	{
		MP.Init();
		m_Plane.Init();
		m_Line.Init();
		return true;
	}
	bool Frame()
	{
		GetContext()->OMSetBlendState(JState::g_pNoAlphaBlend, 0, 1);
		/* 그냥 플랜 돌리기 */
		D3DXMATRIX mScale, mSpin, mTranslate, mzSpin;
		D3DXMatrixIdentity(&m_PlaneWorld);
		float t = I_Timer.m_fGameTimer * D3DX_PI;
		D3DXMatrixScaling(&m_PlaneWorld, 10.0f, 10.0f, 10.0f);
		D3DXMatrixRotationX(&mSpin, D3DX_PI*t*0.1f);
		//D3DXMatrixRotationZ(&mzSpin, D3DX_PI*t*0.1f);
		//D3DXMatrixTranslation(&mTranslate, cos(t) * 10, -1.0f, 0.0f);
		//D3DXMatrixMultiply(&m_PlaneWorld, &mScale, &mzSpin);
		//D3DXMatrixMultiply(&m_PlaneWorld, &m_PlaneWorld, &mSpin);
		//D3DXMatrixMultiply(&m_PlaneWorld, &m_PlaneWorld, &mTranslate);

		MP.SetMatrix(&m_PlaneWorld, &m_Camera[0].m_matView, &m_Camera[0].m_matProj);
		//_stprintf_s(Buf, L"%f %f %f", vM.x, vM.y, vM.z);

		D3DXVECTOR3 v0, v1, v2;
		for (int iFace = 0; iFace < 2; iFace++)
		{
			if (iFace == 0)
			{
				v0 = m_Plane.m_pVertices[0].p;
				v1 = m_Plane.m_pVertices[1].p;
				v2 = m_Plane.m_pVertices[2].p;
			}
			if (iFace == 1)
			{
				v0 = m_Plane.m_pVertices[0].p;
				v1 = m_Plane.m_pVertices[2].p;
				v2 = m_Plane.m_pVertices[3].p;
			}
			// 방법 -2-
			//D3DXVec3TransformCoord(&v0, &v0, &m_PlaneWorld);
			//D3DXVec3TransformCoord(&v1, &v1, &m_PlaneWorld);
			//D3DXVec3TransformCoord(&v2, &v2, &m_PlaneWorld);
		//	D3DXVECTOR3 vStart = MP.m_rRay.vOrigin;
		//	D3DXVECTOR3 vEnd = MP.m_rRay.vOrigin + MP.m_rRay.vDirection * 10000.0f;

		//	D3DXVECTOR3 vNormal, vCross;
		//	D3DXVECTOR3 edge0 = v1 - v0;
		//	D3DXVECTOR3 edge1 = v2 - v0;
		//	D3DXVec3Cross(&vCross, &edge0, &edge1);
		//	D3DXVec3Normalize(&vNormal, &vCross);

		//	if (I_Input.m_dwMouseState[0] == KEY_PUSH &&
		//		MP.GetIntersection(vStart, vEnd, vNormal, v0, v1, v2))
		//	{
		//		if (MP.PointInPolygon(MP.m_vIntersection, vNormal, v0,v1,v2))//MP.PointInPolygon(MP.m_vIntersection, m_Plane.m_pVertices[0].n, v0, v1, v2))
		//		{
		//			return true;
		//		}
		//	}
		//}
			if (I_Input.m_dwMouseState[0] == KEY_PUSH &&
				MP.ChkPick(v0, v1, v2))
			{
				return true;
			}
		}

		return true;
	}
	bool Render()
	{
		m_Plane.SetMatrix(&m_PlaneWorld, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_Plane.Render(GetContext());

		float t = I_Timer.m_fGameTimer * D3DX_PI;
		m_Line.SetMatrix(&MP.m_matWorldPick, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_Line.Draw(GetContext(), MP.m_vSrcVex[0], MP.m_vSrcVex[1], D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
		m_Line.Draw(GetContext(), MP.m_vSrcVex[1], MP.m_vSrcVex[2], D3DXVECTOR4(0, 0.0f, 0, 1.0f));
		m_Line.Draw(GetContext(), MP.m_vSrcVex[2], MP.m_vSrcVex[0], D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));

		m_Line.Draw(GetContext(), MP.m_vSrcVex[0], MP.m_vSrcVex[0] + MP.qvec*1.0f, D3DXVECTOR4(1.0f, 1.0f, 0, 1.0f));
		m_Line.Draw(GetContext(), MP.m_vSrcVex[0], MP.m_vSrcVex[0] + MP.tvec*1.0f, D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f));
		m_Line.Draw(GetContext(), MP.m_vSrcVex[0], MP.m_vSrcVex[0] + MP.pvec*1.0f, D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f));
		m_Line.Draw(GetContext(), MP.m_rRay.vOrigin, MP.m_rRay.vDirection*100.0f, D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;