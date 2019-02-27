#include "JCore.h"
#include "JShape.h"

class JSphereShape : public JShape
{
public:
	ID3D11GeometryShader * LoadGeometryShader(ID3D11Device* device, const TCHAR* szLoadFileName, ID3DBlob** ppBlobOut, const char* szShaderFunc = 0)
	{
		HRESULT hr = S_OK;
		ID3DBlob* pBlob = 0;
		ID3D11GeometryShader* GS = 0;
		if (szShaderFunc == NULL)
		{
			if (FAILED(hr = CompileShader(device, szLoadFileName, &pBlob, "GS", "gs_5_0")))
			{
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = CompileShader(device, szLoadFileName, &pBlob, szShaderFunc, "gs_5_0")))
			{
				return nullptr;
			}
		}
		DWORD dwSize = pBlob->GetBufferSize();
		LPCVOID lpData = pBlob->GetBufferPointer();
		if (FAILED(hr = device->CreateGeometryShader(lpData, dwSize, NULL, &GS)))
		{
			pBlob->Release();
			return nullptr;
		}
		if (ppBlobOut == nullptr)
		{
			pBlob->Release();
			return nullptr;
		}
		else
		{
			*ppBlobOut = pBlob;
		}
		return GS;
	}
	bool Init()
	{
		PNCT_VERTEX vertices[] =
		{
			/* Front */
			{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
		/* Back */
		{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
		/* Right */
		{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
		/* Left */
		{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
		/* Top */
		{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
		/* Bottom */
		{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
		};

		m_dxObj.m_iVertexNum = sizeof(vertices) / sizeof(vertices[0]);
		m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);

		DWORD indices[] =
		{
			0,1,2,		0,2,3,
			4,5,6,		4,6,7,
			8,9,10,		8,10,11,
			12,13,14,	12,14,15,
			16,17,18,	16,18,19,
			20,21,22,	20,22,23,
		};
		m_dxObj.m_iIndexNum = sizeof(indices) / sizeof(indices[0]);
		m_dxObj.m_iIndexSize = sizeof(DWORD);
		m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, vertices, m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
		m_dxObj.m_pIndexBuffer = CreateIndexBuffer(g_pd3dDevice, indices, m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum);
		m_dxObj.m_pConstantBuffer = CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1);
		m_dxObj.m_pVS = DX::LoadVertexShader(g_pd3dDevice, L"../../data/shader/shape.vsh", &m_dxObj.m_BlobVS);
		m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", &m_dxObj.m_BlobPS);
		m_dxObj.m_pGS = LoadGeometryShader(g_pd3dDevice, L"shape.gsh", &m_dxObj.m_BlobGS);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		int ElementCnt = sizeof(ied) / sizeof(ied[0]);
		m_dxObj.m_pIL = DX::CreateLayout(g_pd3dDevice, ied, ElementCnt, m_dxObj.m_BlobVS);
		D3DXMatrixIdentity(&m_matWorld);
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render(ID3D11DeviceContext* context)
	{
		context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
		m_dxObj.Render(context);
		return true;
	}
public:
	JSphereShape()
	{

	}
	virtual ~JSphereShape()
	{

	}
};

class Sample : public JCore
{
public:
	JShape * m_pShpere;
public:
	bool Init()
	{
		m_pShpere = new JSphereShape();
		m_pShpere->Init();
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		m_pShpere->SetMatrix(NULL, &m_Camera.m_matView, &m_Camera.m_matProj);
		m_pShpere->Render(GetContext());
		return true;
	}
	bool Release()
	{
		m_pShpere->Release();
		return true;
	}
};
RUN;