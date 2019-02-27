#include "JCore.h"
#include "MaxObject.h"
class Sample : public JCore
{
public:
	MaxObject obj;
	JCamera cam;
public:
	bool Init()
	{
		D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 50.0f, -150.0f);
		D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		cam.SetViewMatrix(vPos, vTarget, vUp); 
		cam.SetProjMatrix(GetContext(), D3DX_PI* 0.25f,
				(float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 10000.0f);

		obj.Load(GetDevice(), L"../../Data/TURRET_DEPLOY.ASH");
		return true;
	}
	bool Frame()
	{
		GetContext()->RSSetState(JState::g_pRSNoneCullSolid);
		obj.Frame();
		return cam.Frame();
	}
	bool Render()
	{
		obj.Draw(GetContext(), NULL, &cam.m_matView, &cam.m_matProj);
		TCHAR buf[256] = { 0, };
		_stprintf_s(buf, L"Tick : %.1f", obj.m_fCurrentTick);
		I_Write.BlueDraw(buf, 20, { 0,0,800,600 });
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;