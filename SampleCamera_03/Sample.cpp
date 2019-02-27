#include "JCore.h"

class TopView : public JCamera
{
};
class QuarterView : public JCamera
{
public:
};
class SideView : public JCamera
{
};

class Sample : public JCore
{
public:
	TopView TopCam;
	JShape* m_box;
public:
	bool Init()
	{
		D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 100.0f, -1.0f);
		D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		TopCam.SetViewMatrix(vPos, vTarget, vUp);
		TopCam.SetProjMatrix(D3DX_PI* 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom, 1.0f, 1000.0f);
		SwapCamera(&TopCam);

		m_box = new JBoxShape(CENTER);
		m_box->Init();
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		m_box->SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_box->Render(GetContext());
		return true;
	}
	bool Release()
	{
		m_box->Release();
		return true;
	}
};
RUN;