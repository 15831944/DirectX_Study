#include "JCore.h"
#include "JDxHelper.h"

using namespace DX;
class Sample : public JCore
{
public:
	JDxObject obj;
	VSCB      m_cbData;
	D3DXMATRIX					m_matWorld[4];
	D3DXMATRIX					m_matView;
	D3DXMATRIX					m_matProj;
	float						m_fAngleY;
	D3DXVECTOR3					m_vInitCameraPosition;
	D3DXVECTOR3					m_vCameraPosition;
	D3DXVECTOR3					m_vTargetPosition;
	SimpleVertex                m_VertexList[4];
public:
	bool Init()
	{
		m_VertexList[0].p = D3DXVECTOR3(-1.0f, 1.0f, 0.5f);
		m_VertexList[0].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

		m_VertexList[1].p = D3DXVECTOR3(1.0f, 1.0f, 0.5f);
		m_VertexList[1].c = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

		m_VertexList[2].p = D3DXVECTOR3(1.0f, -1.0f, 0.5f);
		m_VertexList[2].c = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

		m_VertexList[3].p = D3DXVECTOR3(-1.0f, -1.0f, 0.5f);
		m_VertexList[3].c = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

		obj.m_iVertexNum = sizeof(m_VertexList) / sizeof(m_VertexList[0]);
		obj.m_iVertexSize = sizeof(SimpleVertex);

		DWORD indices[] =
		{
			0,1,2,	0,2,3, 
		};
		obj.m_iIndexNum = sizeof(indices) / sizeof(indices[0]);
		obj.m_iIndexSize = sizeof(DWORD);

		obj.m_pVertexBuffer=CreateVertexBuffer(GetDevice(), m_VertexList, obj.m_iVertexSize, obj.m_iVertexNum);
		obj.m_pIndexBuffer=CreateIndexBuffer(GetDevice(), indices, obj.m_iIndexSize, obj.m_iIndexNum);
		obj.m_pConstantBuffer=CreateConstantBuffer(GetDevice(), &m_cbData, sizeof(VSCB), 1);
		obj.m_pVS=DX::LoadVertexShader(GetDevice(), L"Sample.hlsl", &obj.m_BlobVS);
		obj.m_pPS=DX::LoadPixelShader(GetDevice(), L"Sample.hlsl", &obj.m_BlobPS);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		int ElementCnt = sizeof(ied) / sizeof(ied[0]);
		obj.m_pIL=DX::CreateLayout(GetDevice(), ied, ElementCnt, obj.m_BlobVS);

		//===========================================================================
		//=================================Camera====================================
		//===========================================================================
		//m_vInitCameraPosition = D3DXVECTOR3(0.0f, 5.0f, -10.0f);
		//m_vCameraPosition = m_vInitCameraPosition;
		//m_vTargetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
		//// 뷰 행렬
		//D3DXMatrixLookAtLH(&m_matView, &m_vInitCameraPosition, &m_vTargetPosition, &Up);
		//D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
		//// 투영행렬
		//D3DXMatrixPerspectiveFovLH(&m_matProj,	(float)D3DX_PI * 0.25f,	g_rtClient.right / (FLOAT)g_rtClient.bottom,
		//	1.0f,100.0f);
		//D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
		return true;
	}
	bool Frame()
	{
		//D3DXMATRIX mSpin;
		//D3DXMATRIX mScale;
		//D3DXMATRIX mTranslate;

		//D3DXMatrixIdentity(&mSpin);
		//D3DXMatrixIdentity(&mScale);
		//D3DXMatrixIdentity(&mTranslate);

		//D3DXMatrixIdentity(&m_matWorld[0]);

		//D3DXMatrixTranslation(&mTranslate, 1.0f, 0.0f, 0.0f);
		//D3DXMatrixScaling(&mScale, 1.0f, 0.1f, 0.1f);

		//m_matWorld[1] = mSpin * mScale * mTranslate;

		//D3DXMatrixTranslation(&mTranslate, 0.0f, 1.0f, 0.0f);
		//D3DXMatrixScaling(&mScale, 0.1f, 1.0f, 0.1f);
		//m_matWorld[2] = mSpin * mScale * mTranslate;

		//D3DXMatrixTranslation(&mTranslate, 0.0f, 0.0f, 1.0f);
		//D3DXMatrixScaling(&mScale, 0.1f, 0.1f, 1.0f);
		//m_matWorld[3] = mSpin * mScale * mTranslate;

		//D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
		//D3DXMatrixLookAtLH(&m_matView, &m_vCameraPosition, &m_vTargetPosition, &Up);

		return true;
	}
	bool Render()
	{
		//D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld[0]);
		//GetContext()->UpdateSubresource(obj.g_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
		//obj.Render(GetContext());

		//D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld[1]);
		//GetContext()->UpdateSubresource(obj.g_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
		//obj.Render(GetContext());

		//D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld[2]);
		//GetContext()->UpdateSubresource(obj.g_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
		//obj.Render(GetContext());

		D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld[3]);
		GetContext()->UpdateSubresource(obj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
		obj.Render(GetContext());
		//obj.Render(GetContext());
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