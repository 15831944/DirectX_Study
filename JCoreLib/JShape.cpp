#include "JShape.h"
void JShape::ChangedVertexShader(const char* szFuntionName, const TCHAR* szShaderName)
{
	m_dxObj.m_pVS = DX::LoadVertexShader(g_pd3dDevice, szShaderName, &m_dxObj.m_BlobVS, szFuntionName);
}
void JShape::ChangedPixelShader(const char* szFuntionName, const TCHAR* szShaderName)
{
	m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice, szShaderName, &m_dxObj.m_BlobPS, szFuntionName);
}
void JShape::SetTexture(const TCHAR* szTexName)
{
	m_dxObj.m_pTexture = I_TexMgr.GetPtr(I_TexMgr.Add(g_pd3dDevice, szTexName));
}
void JShape::CreateInstance(UINT iNumInstance)
{
	m_pInstance.resize(iNumInstance);

	for (int iSt = 0; iSt < m_pInstance.size(); iSt++)
	{
		D3DXMatrixIdentity(&m_pInstance[iSt].matWorld);
		m_pInstance[iSt].uv[0] = D3DXVECTOR4(0, 0, 0, 0);
		m_pInstance[iSt].uv[1] = D3DXVECTOR4(0.25f, 0, 0, 0);
		m_pInstance[iSt].uv[2] = D3DXVECTOR4(0.25f, 0.25f, 0, 0);
		m_pInstance[iSt].uv[3] = D3DXVECTOR4(0, 0.25f, 0, 0);

		m_pInstance[iSt].vColor = D3DXVECTOR4(
			(rand() & RAND_MAX) / (float)RAND_MAX, 
			(rand() & RAND_MAX) / (float)RAND_MAX,
			(rand() & RAND_MAX) / (float)RAND_MAX, 1);
		D3DXMatrixTranspose(&m_pInstance[iSt].matWorld, &m_pInstance[iSt].matWorld);
	}
	m_pInstanceBuffer = DX::CreateVertexBuffer(g_pd3dDevice, &m_pInstance.at(0), m_pInstance.size(), sizeof(Instance));
}
void JShape::SetInstanceIL()
{
	HRESULT hr = S_OK;
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{ "mTransform", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA,     1 },
		{ "mTransform", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA,    1 },
		{ "mTransform", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA,    1 },
		{ "mTransform", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA,    1 },
		{ "POSCOLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 64,	D3D11_INPUT_PER_INSTANCE_DATA,	1 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	m_dxObj.m_pIL = DX::CreateLayout(g_pd3dDevice, layout,numElements, m_dxObj.m_BlobVS);
}
void JShape::SetCount(int iCount)
{
	m_iCount = iCount;
}
bool  JShape::Create(const char* szPSFunName, const char* szVSFunName, const TCHAR* szShaderName)
{
	return true;
}
bool JShape::Init()
{
	return true;
}
bool JShape::Frame()
{
	return true;
}
bool JShape::PreRender(ID3D11DeviceContext* context, UINT iVertexSize)
{
	return true;
}
bool JShape::Render(ID3D11DeviceContext* context, UINT iVertexSize, UINT iCount)
{
	return true;
}
bool JShape::PostRender(ID3D11DeviceContext* context, UINT iCount)
{
	return true;
}
bool JShape::Release()
{
	m_dxObj.Release();
	return true;
}
void JShape::Draw(ID3D11DeviceContext* context, D3DXVECTOR3 vPos, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor)
{

}
void JShape::SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	if (matWorld != NULL)
		m_matWorld = *matWorld;
	if (matView != NULL)
		m_matView = *matView;
	if (matProj != NULL)
		m_matProj = *matProj;

	m_vRight.x = m_matWorld._11;
	m_vRight.y = m_matWorld._12;
	m_vRight.z = m_matWorld._13;

	m_vUp.x = m_matWorld._21;
	m_vUp.y = m_matWorld._22;
	m_vUp.z = m_matWorld._23;

	m_vLook.x = m_matWorld._31;
	m_vLook.y = m_matWorld._32;
	m_vLook.z = m_matWorld._33;

	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;

	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
}
JShape::JShape()
{
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vUp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
}
JShape::~JShape()
{

}