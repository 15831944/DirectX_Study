#include "Shape.h"

//void Shape::CreateInstance(ID3D11Device* pDevice, UINT iNumInstance)
//{
//	m_pInstance.resize(iNumInstance);
//
//	for (int iSt = 0; iSt < m_pInstance.size(); iSt++)
//	{
//		D3DXMatrixIdentity(&m_pInstance[iSt].matWorld);
//		m_pInstance[iSt].uv[0] = D3DXVECTOR4(0, 0, 0, 0);
//		m_pInstance[iSt].uv[1] = D3DXVECTOR4(0.25f, 0, 0, 0);
//		m_pInstance[iSt].uv[2] = D3DXVECTOR4(0.25f, 0.25f, 0, 0);
//		m_pInstance[iSt].uv[3] = D3DXVECTOR4(0, 0.25f, 0, 0);
//
//		m_pInstance[iSt].vColor = D3DXVECTOR4(
//			(rand() & RAND_MAX) / (float)RAND_MAX,
//			(rand() & RAND_MAX) / (float)RAND_MAX,
//			(rand() & RAND_MAX) / (float)RAND_MAX, 1);
//		D3DXMatrixTranspose(&m_pInstance[iSt].matWorld, &m_pInstance[iSt].matWorld);
//	}
//	m_pInstanceBuffer = DX::CreateVertexBuffer(pDevice, &m_pInstance.at(0), m_pInstance.size(), sizeof(Instance));
//
//	D3D11_INPUT_ELEMENT_DESC layout[] =
//	{
//		{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//
//		{ "mTransform", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA,     1 },
//		{ "mTransform", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA,    1 },
//		{ "mTransform", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA,    1 },
//		{ "mTransform", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA,    1 },
//		{ "POSCOLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 64,	D3D11_INPUT_PER_INSTANCE_DATA,	1 },
//	};
//	UINT numElements = sizeof(layout) / sizeof(layout[0]);
//	m_pIL = DX::CreateLayout(pDevice, layout, numElements, m_BlobVS);
//}
bool Shape::Create(ID3D11Device* pDevice, const char* szPSFunName, const char* szVSFunName, const TCHAR* szShaderName)
{
	return true;
}
void Shape::Draw(ID3D11DeviceContext* context, D3DXVECTOR3 vPos, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor)
{

}
Shape::Shape()
{
}
Shape::~Shape()
{
}