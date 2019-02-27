#include "JCore.h"
#include "JDxHelper.h"
#include "JShape.h"
using namespace DX;
//struct PC_VERTEX
//{
//	D3DXVECTOR3 p;
//	D3DXVECTOR4 c;
//};
//struct PNCT_VERTEX
//{
//	D3DXVECTOR3 p;
//	D3DXVECTOR3 n;
//	D3DXVECTOR4 c;
//	D3DXVECTOR2 t;
//};
////struct VSCB
////{
////	D3DXMATRIX matWorld;
////	D3DXMATRIX matView;
////	D3DXMATRIX matProj;
////};
//
//class JShape
//{
//public:
//	JDxObject	m_dxObj;
//	VSCB		m_cbData;
//	D3DXMATRIX	m_matWorld;
//	D3DXMATRIX	m_matView;
//	D3DXMATRIX	m_matProj;
//	int			m_iPrimitiveType;
//public:
//	virtual bool Init() { return true; }
//	virtual bool Frame() { return true; }
//	virtual bool Render(ID3D11DeviceContext* context) { return true; }
//	virtual bool Release() { return true; }
//	virtual void SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
//	{
//		if(matWorld != NULL) 
//			m_matWorld = *matWorld; 
//		if(matView != NULL) 
//			m_matView = *matView; 
//		if(matProj != NULL) 
//			m_matProj = *matProj;
//		D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
//		D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
//		D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
//	}
//	virtual void Draw(ID3D11DeviceContext* context, D3DXVECTOR3 vPos, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor) {}
//};
//class JBoxShape : public JShape
//{
//public:
//	bool Init()
//	{
//		PNCT_VERTEX vertices[] =
//		{
//			/* Front */
//			{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f)},
//			{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
//			{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
//			{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
//			/* Back */
//			{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
//			{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
//			{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
//			{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
//			/* Right */
//			{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
//			{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
//			{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
//			{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
//			/* Left */
//			{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
//			{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
//			{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
//			{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
//			/* Top */
//			{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
//			{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
//			{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
//			{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
//			/* Bottom */
//			{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
//			{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
//			{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
//			{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
//		};
//
//		m_dxObj.m_iVertexNum = sizeof(vertices) / sizeof(vertices[0]);
//		m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);
//
//		DWORD indices[] =
//		{
//		0,1,2,		0,2,3,
//		4,5,6,		4,6,7,
//		8,9,10,		8,10,11,
//		12,13,14,	12,14,15,
//		16,17,18,	16,18,19,
//		20,21,22,	20,22,23,
//		};
//		m_dxObj.m_iIndexNum = sizeof(indices) / sizeof(indices[0]);
//		m_dxObj.m_iIndexSize = sizeof(DWORD);
//
//		m_dxObj.g_pVertexBuffer.Attach(DX::CreateVertexBuffer(g_pd3dDevice, vertices, m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum));
//		m_dxObj.g_pIndexBuffer.Attach(CreateIndexBuffer(g_pd3dDevice, indices, m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum));
//		m_dxObj.g_pConstantBuffer.Attach(CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1));
//		m_dxObj.g_pVS.Attach(DX::LoadVertexShader(g_pd3dDevice, L"../../data/shader/shape.vsh", m_dxObj.g_BlobVS.GetAddressOf()));
//		m_dxObj.g_pPS.Attach(DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", m_dxObj.g_BlobPS.GetAddressOf()));
//
//		D3D11_INPUT_ELEMENT_DESC ied[] =
//		{
//			{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		};
//		int ElementCnt = sizeof(ied) / sizeof(ied[0]);
//		m_dxObj.g_pIL.Attach(DX::CreateLayout(g_pd3dDevice, ied, ElementCnt, m_dxObj.g_BlobVS.Get()));
//		D3DXMatrixIdentity(&m_matWorld);
//		return true;
//	}
//	bool Frame() { return true; }
//	bool Render(ID3D11DeviceContext* context)
//	{
//		context->UpdateSubresource(m_dxObj.g_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
//		m_dxObj.Render(context);
//		return true;
//	}
//	bool Release()
//	{
//		return true;
//	}
//};
//class JLineShape : public JShape
//{
//public:
//	bool Init() 
//	{
//		PC_VERTEX vertices[] =
//		{
//			{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) },
//			{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) },
//		};
//
//		m_dxObj.m_iVertexNum = sizeof(vertices) / sizeof(vertices[0]);
//		m_dxObj.m_iVertexSize = sizeof(PC_VERTEX);
//
//		DWORD indices[] =
//		{
//			0,1,
//		};
//		m_dxObj.m_iIndexNum = sizeof(indices) / sizeof(indices[0]);
//		m_dxObj.m_iIndexSize = sizeof(DWORD);
//
//		m_dxObj.g_pVertexBuffer.Attach(DX::CreateVertexBuffer(g_pd3dDevice, vertices, m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum));
//		m_dxObj.g_pIndexBuffer.Attach(CreateIndexBuffer(g_pd3dDevice, indices, m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum));
//		m_dxObj.g_pConstantBuffer.Attach(CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1));
//		m_dxObj.g_pVS.Attach(DX::LoadVertexShader(g_pd3dDevice, L"../../data/shader/shape.vsh", m_dxObj.g_BlobVS.GetAddressOf(),"VSLine"));
//		m_dxObj.g_pPS.Attach(DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", m_dxObj.g_BlobPS.GetAddressOf(), "PSLine"));
//
//		D3D11_INPUT_ELEMENT_DESC ied[] =
//		{
//			{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		};
//		int ElementCnt = sizeof(ied) / sizeof(ied[0]);
//		m_dxObj.g_pIL.Attach(DX::CreateLayout(g_pd3dDevice, ied, ElementCnt, m_dxObj.g_BlobVS.Get()));
//		D3DXMatrixIdentity(&m_matWorld);
//		return true;
//	}
//	bool Frame() { return true;}
//	bool Render(ID3D11DeviceContext* context) 
//	{ 
//		context->UpdateSubresource(
//			m_dxObj.g_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
//		context->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)m_iPrimitiveType);
//		m_dxObj.Render(context);
//		return true; 
//	}
//	bool Release() { return true; }
//	void Draw(ID3D11DeviceContext* context, D3DXVECTOR3 vPos, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor) 
//	{
//		PC_VERTEX vertex[2];
//		vertex[0].p = vPos;
//		vertex[1].p = vEnd;
//		vertex[0].c = vColor;
//		vertex[1].c = vColor;
//		context->UpdateSubresource(m_dxObj.g_pVertexBuffer.Get(), 0, NULL, &vertex, 0, 0);
//		Render(context);
//	}
//	JLineShape() 
//	{
//		m_iPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
//	}
//};
//class JPlaneShape : public JShape
//{
//public:
//	bool Init() 
//	{ 
//		PNCT_VERTEX vertices[] =
//		{
//			{ D3DXVECTOR3(-1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
//			{ D3DXVECTOR3(1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
//			{ D3DXVECTOR3(1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
//			{ D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
//		};
//
//		m_dxObj.m_iVertexNum = sizeof(vertices) / sizeof(vertices[0]);
//		m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);
//
//		DWORD indices[] =
//		{
//			0,1,2,	0,2,3,
//		};
//		m_dxObj.m_iIndexNum = sizeof(indices) / sizeof(indices[0]);
//		m_dxObj.m_iIndexSize = sizeof(DWORD);
//
//		m_dxObj.g_pVertexBuffer.Attach(DX::CreateVertexBuffer(g_pd3dDevice, vertices, m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum));
//		m_dxObj.g_pIndexBuffer.Attach(CreateIndexBuffer(g_pd3dDevice, indices, m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum));
//		m_dxObj.g_pConstantBuffer.Attach(CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1));
//		m_dxObj.g_pVS.Attach(DX::LoadVertexShader(g_pd3dDevice, L"../../data/shader/shape.vsh", m_dxObj.g_BlobVS.GetAddressOf()));
//		m_dxObj.g_pPS.Attach(DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", m_dxObj.g_BlobPS.GetAddressOf()));
//
//		D3D11_INPUT_ELEMENT_DESC ied[] =
//		{
//			{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//			{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		};
//		int ElementCnt = sizeof(ied) / sizeof(ied[0]);
//		m_dxObj.g_pIL.Attach(DX::CreateLayout(g_pd3dDevice, ied, ElementCnt, m_dxObj.g_BlobVS.Get()));
//		D3DXMatrixIdentity(&m_matWorld);
//		return true; 
//	}
//	bool Frame() { return true; }
//	bool Render(ID3D11DeviceContext* context)
//	{ 
//		context->UpdateSubresource(m_dxObj.g_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
//		m_dxObj.Render(context);
//		return true; 
//	}
//	bool Release() { return true; }
//};


class Sample : public JCore
{
public:
	JShape * Box;
	JShape*  Plane;
	JShape* Line;
	D3DXMATRIX BoxWorld;
	D3DXMATRIX PlaneWorld;
public:
	bool Init()
	{
		Box = new JBoxShape(LB);
		//Line = new JLineShape();
		Plane = new JPlaneShape();
		Box->Init();
		D3DXMatrixRotationY(&BoxWorld, D3DX_PI * 0.25f);
		D3DXMatrixScaling(&PlaneWorld, 2, 2, 2);
		//Line->Init();
		Plane->Init();
		return true;
	}
	bool Frame()
	{
		Box->Frame();
	//	Line->Frame();
		Plane->Frame();
		return true;
	}
	bool Render()
	{
		Box->SetMatrix(&BoxWorld, &m_Camera.m_matView, &m_Camera.m_matProj);
		Box->Render(GetContext());

		Plane->SetMatrix(&PlaneWorld, &m_Camera.m_matView, &m_Camera.m_matProj);
		Plane->Render(GetContext());

	/*	Line->SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
		Line->Draw(GetContext(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
		Line->Draw(GetContext(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1000.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
		Line->Draw(GetContext(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));*/
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;