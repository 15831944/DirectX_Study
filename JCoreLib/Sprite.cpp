#include "Sprite.h"
bool Sprite::Create(bool bInstance, const char* szPSFunName, const char* szVSFunName, const TCHAR* szShaderName)
{
	PNCT_VERTEX vertices[] =
	{
		{ D3DXVECTOR3(-1.0f, 1.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.9f, 0.9f, 0.9f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f, 1.0f, 0.0f),   D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.9f, 0.9f, 0.9f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f, -1.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.9f, 0.9f, 0.9f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.9f, 0.9f, 0.9f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
	};
	for (int iVer = 0; iVer < sizeof(vertices) / sizeof(vertices[0]); iVer++)
	{
		m_pVertices.push_back(vertices[iVer]);
	}
	m_dxObj.m_iVertexNum = sizeof(vertices) / sizeof(vertices[0]);
	m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);

	DWORD indices[] =
	{
		0,1,2,	0,2,3,
	};
	m_dxObj.m_iIndexNum = sizeof(indices) / sizeof(indices[0]);
	m_dxObj.m_iIndexSize = sizeof(DWORD);

	m_dxObj.m_pIndexBuffer = CreateIndexBuffer(g_pd3dDevice, indices, m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum);
	m_dxObj.m_pConstantBuffer = CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1);

	if (!bInstance)
	{
		m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, vertices, m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
		m_dxObj.m_pVS = DX::LoadVertexShader(g_pd3dDevice, szShaderName, &m_dxObj.m_BlobVS, szVSFunName);
		m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice,  szShaderName, &m_dxObj.m_BlobPS, szPSFunName);
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		int ElementCnt = sizeof(ied) / sizeof(ied[0]);
		m_dxObj.m_pIL = DX::CreateLayout(g_pd3dDevice, ied, ElementCnt, m_dxObj.m_BlobVS);
	}
	else
	{
		m_bInstanced = true;
		m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, vertices, m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
		m_dxObj.m_pVS = DX::LoadVertexShader(g_pd3dDevice, L"../../data/shader/Instance.hlsl", &m_dxObj.m_BlobVS);
		m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/Instance.hlsl", &m_dxObj.m_BlobPS);
		SetInstanceIL();
	}
	D3DXMatrixIdentity(&m_matWorld);
	return true;
}
void Sprite::SetRectAnimation(float fAnimTime, int iWidth, int iWidthSize, int iHeight, int iHeightSize)
{
	m_fAnimTime = fAnimTime;

	m_rtSet.left = iWidth;
	m_rtSet.right = iWidthSize; // 텍스쳐 가로 셋 갯수 및 크기	
	m_rtSet.top = iHeight;
	m_rtSet.bottom = iHeightSize; // 텍스쳐 세로 셋 갯수 및 크기

	if (iWidth*iHeight <= 1)
	{
		m_fSecPerRender = fAnimTime / m_iNumTexture;
		return;
	}
	else
	{
		m_fSecPerRender = fAnimTime / (iWidth*iHeight);
		m_iNumTexture = iWidth * iHeight;
	}

	for (int iHeight = 0; iHeight < m_rtSet.left; iHeight++)
	{
		for (int iWidth = 0; iWidth < m_rtSet.top; iWidth++)
		{
			RECTUV  Rect;
			Rect.rt.left = iWidth * m_rtSet.right;
			Rect.rt.right = (iWidth + 1) * m_rtSet.right;
			Rect.rt.top = iHeight * m_rtSet.bottom;
			Rect.rt.bottom = (iHeight + 1)* m_rtSet.bottom;

			Rect.vUV = SetUV(Rect.rt);
			m_rtList.push_back(Rect);
		}
	}
}
D3DXVECTOR4 Sprite::SetUV(RECT& rt)
{
	D3DXVECTOR4 vUV;
	float fOffSetX = 0.0f;
	if (rt.left > 0)
	{
		fOffSetX = (float)rt.left / (float)(m_rtSet.left * m_rtSet.right);
	}
	float fOffSetY = 0.0f;
	if (rt.top > 0)
	{
		fOffSetY = (float)rt.top / (float)(m_rtSet.top * m_rtSet.bottom);
	}

	vUV.x = fOffSetX;
	vUV.y = fOffSetY;

	fOffSetX = 1.0f;
	if (rt.right > 0)
	{
		fOffSetX = (float)rt.right / (float)(m_rtSet.left * m_rtSet.right);
	}
	fOffSetY = 1.0f;
	if (rt.bottom > 0)
	{
		fOffSetY = (float)rt.bottom / (float)(m_rtSet.top * m_rtSet.bottom);
	}
	vUV.z = fOffSetX;
	vUV.w = fOffSetY;
	return vUV;
}
void Sprite::SetTextureArray(vector<T_STR> FileList)
{
	HRESULT hr = S_OK;
	for (int iList = 0; iList < FileList.size(); iList++)
	{
		INT iIndex = I_TexMgr.Add(g_pd3dDevice, FileList[iList].c_str());
		if (iIndex < 0)
		{
			MessageBox(0, _T("m_Texture.Load 실패"), _T("Fatal error"), MB_OK);
			return;
		}
		m_pIndexList.push_back(iIndex);
	}
	m_iNumTexture = m_pIndexList.size();
}
void Sprite::Update(ID3D11DeviceContext* context, float& pfCurrentTimer, int& iApplyIndex, float fGlobalTime, float fElapsedTime)
{
	// 스프라이트 발생 경과 시간
	m_fElapseTime += fElapsedTime;
	// 에니메이션 교체 주기 누적 시간
	pfCurrentTimer += fElapsedTime;

	if (pfCurrentTimer >= m_fSecPerRender)
	{
		if (++iApplyIndex >= m_iNumTexture)
			iApplyIndex = 0;

		pfCurrentTimer = 0.0f;
	}
	// 텍스처 애니메이션
	if (m_pIndexList.size())
	{
		m_dxObj.m_pTexture = I_TexMgr.GetPtr(m_pIndexList[iApplyIndex]);
	}
	else // UV 텍스처 에니메이션
	{
		if (m_rtList.size() < 0) return;
		if (m_bInstanced)
		{
			for (int iSt = 0; iSt < m_pInstance.size(); iSt++)
			{
				D3DXVECTOR4 vUV = m_rtList[m_pInstance[iSt].uv[0].z].vUV;
				D3DXVECTOR4 vColor = m_pInstance[iSt].vColor;
				m_pInstance[iSt].uv[0] = D3DXVECTOR4(vUV.x, vUV.y, 0, 0);
				m_pInstance[iSt].uv[1] = D3DXVECTOR4(vUV.z, vUV.y, 0, 0);
				m_pInstance[iSt].uv[2] = D3DXVECTOR4(vUV.z, vUV.w, 0, 0);
				m_pInstance[iSt].uv[3] = D3DXVECTOR4(vUV.x, vUV.w, 0, 0);
				D3DXMatrixTranspose(&m_pInstance[iSt].matWorld, &m_pInstance[iSt].matWorld);
			}
			context->UpdateSubresource(m_pInstanceBuffer, 0, NULL, &m_pInstance.at(0), 0, 0);
		}
		else
		{
			D3DXVECTOR4 vUV = m_rtList[iApplyIndex].vUV;
			D3DXVECTOR4 vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			if (m_dxObj.m_pTexture != nullptr && m_rtList.size())
			{
				PNCT_VERTEX vertices[] =
				{
					{ D3DXVECTOR3(-1.0f, 1.0f, 0.0f),D3DXVECTOR3(-1.0f, 1.0f, 0.0f), vColor,D3DXVECTOR2(vUV.x, vUV.y) },
					{ D3DXVECTOR3(1.0f, 1.0f, 0.0f),D3DXVECTOR3(-1.0f, 1.0f, 0.0f), vColor,D3DXVECTOR2(vUV.z, vUV.y) },
					{ D3DXVECTOR3(1.0f, -1.0f, 0.0f),D3DXVECTOR3(-1.0f, 1.0f, 0.0f), vColor,D3DXVECTOR2(vUV.z, vUV.w) },
					{ D3DXVECTOR3(-1.0f, -1.0f, 0.0f),D3DXVECTOR3(-1.0f, 1.0f, 0.0f), vColor,D3DXVECTOR2(vUV.x, vUV.w) },
				};
				context->UpdateSubresource(m_dxObj.m_pVertexBuffer, 0, NULL, &vertices, 0, 0);
			}
		}
	}
}
bool Sprite::Frame(ID3D11DeviceContext* context, float fGlobalTime, float fElapsedTime)
{
	Update(context, m_fTime, m_iCurrentIndex, fGlobalTime, fElapsedTime);
	return true;
}
bool Sprite::PreRender(ID3D11DeviceContext* context)
{
	JPlaneShape::PreRender(context);
	context->PSSetShaderResources(0, 1, &m_dxObj.m_pTexture->m_pSRV);
	return true;
}
bool Sprite::Render(ID3D11DeviceContext* context)
{
	context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	this->PreRender(context);
	this->PostRender(context);
	return true;
}
bool Sprite::RenderInstancing(ID3D11DeviceContext* context)
{
	PreRender(context);
	{
		ID3D11Buffer* vb[2] = { m_dxObj.m_pVertexBuffer, m_pInstanceBuffer };
		UINT stride[2] = { sizeof(PNCT_VERTEX), sizeof(Instance) };
		UINT offset[2] = { 0, 0 };
		context->IASetVertexBuffers(0, 2, vb, stride, offset);
		context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	}
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->DrawIndexedInstanced(m_dxObj.m_iIndexNum, m_pInstance.size(), 0, 0, 0);
	return true;
}
bool Sprite::PostRender(ID3D11DeviceContext* context)
{
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	JPlaneShape::PostRender(context);
	return true;
}

Sprite::Sprite()
{
	m_fAnimTime = 0.0f;
	m_fElapseTime = 0.0f;
	m_fTime = 0.0f;
	m_iCurrentIndex = 0;
	m_fSecPerRender = 0.2f;
	m_iNumTexture = 0;
	m_rtSet.left = 4;
	m_rtSet.right = 64; // 텍스쳐 가로 셋 갯수 및 크기	
	m_rtSet.top = 4;
	m_rtSet.bottom = 64; // 텍스쳐 세로 셋 갯수 및 크기
	m_pSRV = NULL;
}


Sprite::~Sprite()
{
}
