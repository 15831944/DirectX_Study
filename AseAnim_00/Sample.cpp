#include "JCore.h"
#include "AseObject.h"
/*
	convert = render가능한 구조로 바꿈
	asemesh -> convert = mesh
*/
class Sample : public JCore
{
	AseObject box;
	D3DXMATRIX matWorld;
	D3DXMATRIX matPos;
	D3DXMATRIX matRot;
public:
	bool Init()
	{
		box.Load(GetDevice(), L"../../data/scaleanimationmodel.ase");
		box.Init();
		m_Camera[0].SetViewMatrix(D3DXVECTOR3(0.0f, 5.0f, -10.0f), D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f,1.0f,0.0f)); // QuarterView
		m_Camera[0].SetProjMatrix(D3DX_PI* 0.25f,
			(float)g_rtClient.right / (float)g_rtClient.bottom,
			1.0f, 10000.0f);
		D3DXMatrixIdentity(&matPos);
		return true;
	}
	bool Frame()
	{
		//float fTime = I_Timer.m_fGameTimer;
		//D3DXMatrixTranslation(&matWorld, fTime, 0, 0);
		box.Frame();
		//D3DXMATRIX matpos, matrotx, matroty, matrotz;
		//for (int iTrack = 0; iTrack < box.m_pPos.size(); iTrack++)
		//{
		//	TRACK_POS pos = box.m_pPos[iTrack];
		//	if (pos.iTick < box.m_fCurrentTick)
		//	{
		//		D3DXMatrixTranslation(&matpos, box.m_pPos[iTrack].vPos.x, box.m_pPos[iTrack].vPos.y, box.m_pPos[iTrack].vPos.z);
		//	}
		//}
		//for (int iTrack = 0; iTrack < box.m_pRot.size(); iTrack++)
		//{
		//	TRACK rot = box.m_pRot[iTrack];
		//	if (rot.iTick < box.m_fCurrentTick)
		//	{
		//		D3DXMatrixRotationX(&matrotx, box.m_pRot[iTrack].vRot.x);
		//		D3DXMatrixRotationY(&matroty, box.m_pRot[iTrack].vRot.y);
		//		D3DXMatrixRotationZ(&matrotz, box.m_pRot[iTrack].vRot.z);
		//	}
		//}
		//matWorld = matpos*matrotx * matroty * matrotz;
		return true;
	}
	bool Render()
	{
		box.Draw(GetContext(), &matWorld, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		TCHAR buf[256] = { 0, };
		_stprintf_s(buf, L"%f", box.m_fCurrentTick);
		I_Write.Draw(buf, 15, { 0,150,800,600 });
		return true;
	}
	bool Release()
	{
		box.Release();
		return true;
	}
};
RUN;