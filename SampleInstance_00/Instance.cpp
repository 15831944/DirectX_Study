#include "Instance.h"

bool Instance::SetInputLayOut()
{
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 24,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,		0, 40,	D3D11_INPUT_PER_VERTEX_DATA,	0 },

		{ "mTransform", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA,     1 },
		{ "mTransform", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA,    1 },
		{ "mTransform", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA,    1 },
		{ "mTransform", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA,    1 },
		{ "POSCOLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 64,	D3D11_INPUT_PER_INSTANCE_DATA,	1 },
	};
	int ElementCnt = sizeof(ied) / sizeof(ied[0]);
	m_dxObj.m_pIL = DX::CreateLayout(g_pd3dDevice, ied, ElementCnt, m_dxObj.m_BlobVS);
	return true;
}
bool Instance::SetInstance(Instance* pInstanceList)
{
	m_pInstanceBuffer = DX::CreateVertexBuffer(g_pd3dDevice, pInstanceList, sizeof(PNCT_VERTEX), sizeof(JInstance), true);
	SetInputLayOut();
	m_bInstanced = true;
	return true;
}
bool Instance::InstFrame(ID3D11DeviceContext* context, int iSize, Instance* pInstanceList)
{
	JInstance* pInstances = NULL;
	D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
	if (SUCCEEDED(context->Map((ID3D11Resource*)m_pInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedFaceDest)))
	{
		pInstances = (JInstance*)MappedFaceDest.pData;
		memcpy(pInstances, pInstanceList, sizeof(JInstance) * iSize);
		context->Unmap(m_pInstanceBuffer, 0);
	}
}
bool Instance::PostRender(ID3D11DeviceContext* context, UINT iSize)
{
	ID3D11Buffer* Buffer[2] = { m_dxObj.m_pVertexBuffer, m_pInstanceBuffer };
	UINT stride[2] = { sizeof(PNCT_VERTEX), sizeof(JInstance) };
	UINT offset[2] = { 0, 0 };

	context->IASetVertexBuffers(0, 2, Buffer, stride, offset);
	context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	context->DrawIndexedInstanced(m_dxObj.m_iIndexNum, iSize, 0, 0, 0);
	return true;
}
Instance::Instance()
{
	m_bInstanced = false;
}


Instance::~Instance()
{
}
