#define _CRT_SECURE_NO_WARNINGS
#include "JCore.h"
#include "JDxHelper.h"
using namespace DX;
class Sample : public JCore
{
public:
	JDxObject obj;
	VSCB      m_cbData;
	D3D11_VIEWPORT				m_ViewPort[9];

	D3DXMATRIX					m_matWorld[9];
	D3DXMATRIX					m_matView;
	D3DXMATRIX					m_matProj;
	float						m_fAngleY;
	D3DXVECTOR3					m_vInitCameraPosition;
	D3DXVECTOR3					m_vCameraPosition;
	D3DXVECTOR3					m_vTargetPosition;
	
public:
	bool SetViewPort()
	{
		FLOAT Width = g_rtClient.right / 3;
		FLOAT Height = g_rtClient.bottom / 3;

		//=========================상단=========================//
		m_ViewPort[0].TopLeftX = 0;				m_ViewPort[0].TopLeftY = 0;
		m_ViewPort[0].Width = Width;			m_ViewPort[0].Height = Height;
		m_ViewPort[0].MinDepth = 0;				m_ViewPort[0].MaxDepth = 1;

		m_ViewPort[1].TopLeftX = Width;			m_ViewPort[1].TopLeftY = 0; 
		m_ViewPort[1].Width = Width;			m_ViewPort[1].Height = Height;
		m_ViewPort[1].MinDepth = 0;				m_ViewPort[1].MaxDepth = 1;

		m_ViewPort[2].TopLeftX = Width + Width; m_ViewPort[2].TopLeftY = 0; 
		m_ViewPort[2].Width = Width;			m_ViewPort[2].Height = Height;
		m_ViewPort[2].MinDepth = 0;				m_ViewPort[2].MaxDepth = 1;
		//=========================중간=========================//
		m_ViewPort[3].TopLeftX = 0;				m_ViewPort[3].TopLeftY = Height; 
		m_ViewPort[3].Width = Width;			m_ViewPort[3].Height = Height;
		m_ViewPort[3].MinDepth = 0;				m_ViewPort[3].MaxDepth = 1;

		m_ViewPort[4].TopLeftX = Width;			m_ViewPort[4].TopLeftY = Height; 
		m_ViewPort[4].Width = Width;			m_ViewPort[4].Height = Height;
		m_ViewPort[4].MinDepth = 0;				m_ViewPort[4].MaxDepth = 1;

		m_ViewPort[5].TopLeftX = Width + Width; m_ViewPort[5].TopLeftY = Height; 
		m_ViewPort[5].Width = Width;			m_ViewPort[5].Height = Height;
		m_ViewPort[5].MinDepth = 0;				m_ViewPort[5].MaxDepth = 1;
		//=========================하단=========================//
		m_ViewPort[6].TopLeftX = 0;				m_ViewPort[6].TopLeftY = Height + Height;
		m_ViewPort[6].Width = Width;			m_ViewPort[6].Height = Height;
		m_ViewPort[6].MinDepth = 0;				m_ViewPort[6].MaxDepth = 1;

		m_ViewPort[7].TopLeftX = Width;			m_ViewPort[7].TopLeftY = Height + Height;
		m_ViewPort[7].Width = Width;			m_ViewPort[7].Height = Height;
		m_ViewPort[7].MinDepth = 0;				m_ViewPort[7].MaxDepth = 1;

		m_ViewPort[8].TopLeftX = Width + Width; m_ViewPort[8].TopLeftY = Height + Height; 
		m_ViewPort[8].Width = Width;			m_ViewPort[8].Height = Height;
		m_ViewPort[8].MinDepth = 0;				m_ViewPort[8].MaxDepth = 1;
		return true;
	}
	bool Init()
	{
		SetViewPort();
		SimpleVertex vertices[] =
		{
			{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR4(0.4f, 1.0f, 5.0f, 1.0f) },
			{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR4(0.7f, 0.5f, 1.0f, 1.0f) },
			{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR4(0.5f, 1.0f, 0.5f, 1.0f) },
			{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f) },
			{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 1.0f, 1.0f) },
			{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR4(0.5f, 1.0f, 0.5f, 1.0f) },
			{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR4(0.5f, 1.0f, 0.5f, 1.0f) },
			{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR4(1.0f, 0.6f, 0.5f, 1.0f) },
		};
		obj.m_iVertexNum = sizeof(vertices) / sizeof(vertices[0]);
		obj.m_iVertexSize = sizeof(SimpleVertex);
		DWORD indices[] =
		{
			3,1,0,        2,1,3,        0,5,4,        1,5,0,

			3,4,7,        0,4,3,        1,6,5,        2,6,1,

			2,7,6,        3,7,2,        6,4,5,        7,4,6,
		};
		obj.m_iIndexNum = sizeof(indices) / sizeof(indices[0]);
		obj.m_iIndexSize = sizeof(DWORD);

		obj.m_pVertexBuffer=CreateVertexBuffer(GetDevice(), vertices, obj.m_iVertexSize, obj.m_iVertexNum);
		obj.m_pIndexBuffer = CreateIndexBuffer(GetDevice(), indices, obj.m_iIndexSize, obj.m_iIndexNum);
		obj.m_pConstantBuffer=CreateConstantBuffer(GetDevice(), &m_cbData, sizeof(VSCB), 1);
		obj.m_pVS=LoadVertexShader(GetDevice(), L"Sample.hlsl", &obj.m_BlobVS);
		obj.m_pPS=LoadPixelShader(GetDevice(), L"Sample.hlsl", &obj.m_BlobPS);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		int ElementCnt = sizeof(ied) / sizeof(ied[0]);
		obj.m_pIL=CreateLayout(GetDevice(), ied, ElementCnt, obj.m_BlobVS);
		//===========================================================================
		//=================================Camera====================================
		//===========================================================================
		m_vInitCameraPosition = D3DXVECTOR3(0.0f, 5.0f, -10.0f);
		m_vCameraPosition = m_vInitCameraPosition;
		m_vTargetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
		// 뷰 행렬
		D3DXMatrixLookAtLH(&m_matView, &m_vInitCameraPosition, &m_vTargetPosition, &Up);
		D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
		// 투영행렬
		// , 90도, 가로세로비율,최소~최대거리
		D3DXMatrixPerspectiveFovLH(&m_matProj, (float)D3DX_PI * 0.25f, g_rtClient.right / (FLOAT)g_rtClient.bottom, 1.0f, 100.0f);
		D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
		return true;
	}
	bool Frame()
	{
		float fTime = I_Timer.m_fGameTimer * 10.0f;
	
		D3DXMatrixTranslation(&m_matWorld[0], cosf(fTime), 0.0f, 0.0f);
		D3DXMatrixTranslation(&m_matWorld[1], 0.0f, cosf(fTime), 0.0f);
		D3DXMatrixTranslation(&m_matWorld[2], 0.0f, 0.0f, cosf(fTime));

		D3DXMatrixScaling(&m_matWorld[3], cosf(fTime), 1.0f, 1.0f);
		D3DXMatrixScaling(&m_matWorld[4], 1.0f, cosf(fTime), 1.0f);
		D3DXMatrixScaling(&m_matWorld[5], 1.0f, 1.0f, cosf(fTime));

		D3DXMatrixRotationX(&m_matWorld[6], fTime);
		D3DXMatrixRotationY(&m_matWorld[7], fTime);
		D3DXMatrixRotationZ(&m_matWorld[8], fTime);
		return true;
	}
	bool Render()
	{
		for (int iView = 0; iView < 9; iView++)
		{
			float fX = m_ViewPort[iView].TopLeftX;
			float fY = m_ViewPort[iView].TopLeftY;
			T_STR iVp = L"Vp : ";
			TCHAR iValue[12];
			iVp += _itow(iView, iValue, 10);
			
			I_Write.Draw(iVp.c_str(), 20, {fX,fY,800,800});
			m_pd3dContext->RSSetViewports(1, &m_ViewPort[iView]);
			D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld[iView]);
			// 상수버퍼 -> Dynamic이 아닐때
			GetContext()->UpdateSubresource(obj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
			obj.Render(GetContext(), sizeof(SimpleVertex), 36);
		}
		return true;
	}
	bool Release()
	{
		return true;
	}
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow)
{
	Sample core;
	if (core.SetWindow(hInstance, 800, 600, L"DirectX Sample Box3D"))
	{
		core.Run();
		return 0;
	}
	return 1;
}