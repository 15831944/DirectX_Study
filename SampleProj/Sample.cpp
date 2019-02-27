/*
State, Camera ������Ʈ���� ���¸� �ٸ����Ҽ��ִ�
	�������� :: ����Ʈ, UI
	Proj == OrthoLH(2w,2h(�ڽ�����),0.1f, 100.0f ) << w,h �� ��ǥ
	OrthoOffCenterLH() // ���ϴ� �κ��� �߶� �����ټ��ִ� (���ڰ�4��)
	//======= CameraPos���� ���
*/
/*
//////=====T*R == �˵�ȸ��
	Stencil
	INCR : ��������ŭ ���� 1+
	KEEP : �״��
	��氪�ٸ����ؼ������غ���.

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

		//=========================���=========================//
		m_ViewPort[0].TopLeftX = 0;				m_ViewPort[0].TopLeftY = 0;
		m_ViewPort[0].Width = Width;			m_ViewPort[0].Height = Height;
		m_ViewPort[0].MinDepth = 0;				m_ViewPort[0].MaxDepth = 1;

		m_ViewPort[1].TopLeftX = Width;			m_ViewPort[1].TopLeftY = 0;
		m_ViewPort[1].Width = Width;			m_ViewPort[1].Height = Height;
		m_ViewPort[1].MinDepth = 0;				m_ViewPort[1].MaxDepth = 1;
		//=========================�ϴ�=========================//
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