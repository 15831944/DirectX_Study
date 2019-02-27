/*
State, Camera 오브젝트마다 상태를 다르게할수있다
	직교투영 :: 이펙트, UI
	Proj == OrthoLH(2w,2h(박스다참),0.1f, 100.0f ) << w,h 뷰 좌표
	OrthoOffCenterLH() // 원하는 부분을 잘라서 보여줄수있다 (인자값4개)
	//======= CameraPos값도 고려
*/
/*
//////=====T*R == 궤도회전
	Stencil
	INCR : 참조값만큼 증가 1+
	KEEP : 그대로
	배경값다르게해서적용해보기.

*/
#define _CRT_SECURE_NO_WARNINGS
#include "JCore.h"
#include "JShape.h"
class Sample : public JCore
{
public:
	JShape* m_pBox;
	D3D11_VIEWPORT				m_ViewPort[4];
	D3DXMATRIX m_matOrthoProj;
	D3DXMATRIX m_matCenterProj[4];
	D3DXMATRIX m_matWorld;
public:
	bool SetViewPort()
	{
		FLOAT Width = g_rtClient.right / 2;
		FLOAT Height = g_rtClient.bottom / 2;

		//=========================상단=========================//
		m_ViewPort[0].TopLeftX = 0;				m_ViewPort[0].TopLeftY = 0;
		m_ViewPort[0].Width = Width;			m_ViewPort[0].Height = Height;
		m_ViewPort[0].MinDepth = 0;				m_ViewPort[0].MaxDepth = 1;

		m_ViewPort[1].TopLeftX = Width;			m_ViewPort[1].TopLeftY = 0;
		m_ViewPort[1].Width = Width;			m_ViewPort[1].Height = Height;
		m_ViewPort[1].MinDepth = 0;				m_ViewPort[1].MaxDepth = 1;
		//=========================하단=========================//
		m_ViewPort[2].TopLeftX = 0;				m_ViewPort[2].TopLeftY = Height;
		m_ViewPort[2].Width = Width;			m_ViewPort[2].Height = Height;
		m_ViewPort[2].MinDepth = 0;				m_ViewPort[2].MaxDepth = 1;

		m_ViewPort[3].TopLeftX = Width;			m_ViewPort[3].TopLeftY = Height;
		m_ViewPort[3].Width = Width;			m_ViewPort[3].Height = Height;
		m_ViewPort[3].MinDepth = 0;				m_ViewPort[3].MaxDepth = 1;
		return true;
	}
	bool Init()
	{
		m_pBox = new JBoxShape(CENTER);
		m_pBox->Init();

		D3DXMatrixOrthoLH(&m_matOrthoProj, 2, 2, 0.1f, 100.0f);
		//=====LT
		D3DXMatrixOrthoOffCenterLH(&m_matCenterProj[0], -1.0f, 3.0f, -3.0f, 1.0f, 0.1f, 50.0f);
		//=====RT
		D3DXMatrixOrthoOffCenterLH(&m_matCenterProj[1], -3.0f, 1.0f, -3.0f, 1.0f, 0.1f, 50.0f);
		//=====LB
		D3DXMatrixOrthoOffCenterLH(&m_matCenterProj[2], -1.0f, 3.0f, -1.0f, 3.0f, 0.1f, 50.0f);
		//=====RB
		D3DXMatrixOrthoOffCenterLH(&m_matCenterProj[3], -3.0f, 1.0f, -1.0f, 3.0f, 0.1f, 50.0f);

		SetViewPort();
		D3DXMatrixScaling(&m_matWorld, 1, 1, 1);
		return true;
	}
	bool Frame()
	{

		return true;
	}
	bool Render()
	{
		for (int iView = 0; iView < 4; iView++)
		{
			float fX = m_ViewPort[iView].TopLeftX;
			float fY = m_ViewPort[iView].TopLeftY;
			T_STR iVp = L"Vp : ";
			TCHAR iValue[12];
			iVp += _itow(iView, iValue, 10);

			I_Write.Draw(iVp.c_str(), 20, { fX,fY,800,800 });
			m_pd3dContext->RSSetViewports(1, &m_ViewPort[iView]);
			m_pBox->SetMatrix(&m_matWorld, &m_Camera.m_matView, &m_matCenterProj[iView]);
			m_pBox->Render(GetContext());
		}
		return true;
	}
	bool Release()
	{
		m_pBox->Release();
		return true;
	}
};
RUN;