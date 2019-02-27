#include "JDxObjectSample.h"
#include "JInput.h"
#include "JState.h"
bool JDxObjectSample::PreRender(ID3D11DeviceContext* context, UINT VertexSize)
{
	UINT Strides = VertexSize;
	UINT Offsets = 0;
	context->PSSetSamplers(0, 1, &JState::g_pTexSS);
	context->VSSetShader(m_pVS, NULL, NULL);
	context->PSSetShader(m_pPS, NULL, NULL);
	context->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	context->IASetInputLayout(m_pIL);
	context->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Strides, &Offsets);
	context->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	if (m_ImageMask != NULL)
	{
		context->PSSetShaderResources(1, 1, &m_ImageMask->m_pTexSRV);
		context->PSSetShaderResources(0, 1, &m_Image->m_pTexSRV);
	}
	if(m_Image != NULL)
	{
		context->PSSetShaderResources(0, 1, &m_Image->m_pTexSRV);
	}
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return true;
}
bool JDxObjectSample::Render(ID3D11DeviceContext* context, UINT VertexSize, UINT VertexCnt)
{
	PreRender(context, VertexSize);
	PostRender(context, VertexCnt);
	return true;
}
bool JDxObjectSample::PostRender(ID3D11DeviceContext* context, UINT VertexCnt)
{
	//context->Draw(VertexCnt, 0);
	context->DrawIndexed(VertexCnt, 0, 0);
	return true;
}


bool JDxObjectSample::Load(ID3D11Device* device, const TCHAR* pszTexLoadName, const TCHAR* pszTexMaskLoadName)
{
	if (pszTexMaskLoadName != NULL)
	{
		m_iImageMask = I_ImgMgr.Add(device, pszTexMaskLoadName);
		m_ImageMask = I_ImgMgr.GetPtr(m_iImageMask);
	}
	m_iImage = I_ImgMgr.Add(device, pszTexLoadName);
	m_Image = I_ImgMgr.GetPtr(m_iImage);

	return true;
}
ID3D11Buffer * JDxObjectSample::CreateIndexBuffer(ID3D11Device* device, void* pSysMem, UINT VertexSize, UINT VertexCnt)
{
	HRESULT hr;
	D3D11_BUFFER_DESC pDesc;
	ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
	pDesc.ByteWidth = VertexSize * VertexCnt;
	pDesc.Usage = D3D11_USAGE_DEFAULT;
	pDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	pDesc.CPUAccessFlags = 0;
	pDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA pInitialData;
	ZeroMemory(&pInitialData, sizeof(D3D11_SUBRESOURCE_DATA));
	pInitialData.pSysMem = pSysMem;

	if (FAILED(hr = device->CreateBuffer(&pDesc, &pInitialData, &m_pIndexBuffer)))
	{
		return NULL;
	}
	return m_pIndexBuffer;
}
ID3D11Buffer* JDxObjectSample::CreateConstantBuffer(ID3D11Device* device, void* pSysMem, UINT VertexSize, UINT VertexCnt)
{
	HRESULT hr;
	D3D11_BUFFER_DESC pDesc;
	ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
	pDesc.ByteWidth = VertexSize * VertexCnt;// sizeof(JVertex) * 6;
	pDesc.Usage = D3D11_USAGE_DEFAULT;
	pDesc.CPUAccessFlags = 0;
	pDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	pDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA pInitialData;
	ZeroMemory(&pInitialData, sizeof(D3D11_SUBRESOURCE_DATA));
	pInitialData.pSysMem = pSysMem;

	if (FAILED(hr = device->CreateBuffer(&pDesc, &pInitialData, &m_pConstantBuffer)))
	{
		return NULL;
	}
	return m_pConstantBuffer;
}
ID3D11Buffer* JDxObjectSample::CreateVertexBuffer(ID3D11Device* device, void* pSysMem, UINT VertexSize, UINT VertexCnt)
{
	HRESULT hr;
	D3D11_BUFFER_DESC pDesc;
	ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
	pDesc.ByteWidth = VertexSize * VertexCnt;// sizeof(JVertex) * 6;
	pDesc.Usage = D3D11_USAGE_DEFAULT;
	pDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	pDesc.CPUAccessFlags = 0;
	pDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA pInitialData;
	ZeroMemory(&pInitialData, sizeof(D3D11_SUBRESOURCE_DATA));
	pInitialData.pSysMem = pSysMem;

	if (FAILED(hr = device->CreateBuffer(&pDesc, &pInitialData, &m_pVertexBuffer)))
	{
		return NULL;
	}
	return m_pVertexBuffer;
}

void JDxObjectSample::SetRect(float left, float top, float right, float bottom,float fZ)
{
	m_rt.left = left; m_rt.top = top; m_rt.right = right - left; m_rt.bottom = bottom - top;
	float fLeft = (left / g_rtClient.right) * 2.0f - 1.0f;
	float fRight = (right / g_rtClient.right) * 2.0f - 1.0f;
	float fTop = ((top / g_rtClient.bottom) * 2.0f - 1.0f) * -1.0f;
	float fBottom = ((bottom / g_rtClient.bottom) * 2.0f - 1.0f) * -1.0f;

	VertexList[0].Pos = Vector3(fLeft, fTop, fZ);
	VertexList[0].Tex = Vector2(0.0f, 0.0f);
	VertexList[0].Col = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	VertexList[1].Pos = Vector3(fRight, fTop, fZ);
	VertexList[1].Tex = Vector2(1.0f, 0.0f);
	VertexList[1].Col = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	VertexList[2].Pos = Vector3(fRight, fBottom, fZ);
	VertexList[2].Tex = Vector2(1.0f, 1.0f);
	VertexList[2].Col = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	VertexList[3] = VertexList[0];
	VertexList[4] = VertexList[2];
	VertexList[5].Pos = Vector3(fLeft, fBottom, fZ);
	VertexList[5].Tex = Vector2(0.0f, 1.0f);
	VertexList[5].Col = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}
void JDxObjectSample::SetTex(fRECT& rt, fPOINT& m_Size)
{
	fRECT rtTmp = rt;
	rtTmp.right += rtTmp.left;
	rtTmp.bottom += rtTmp.top;
	float fLeft = (rtTmp.left / m_Size.x);
	float fRight = (rtTmp.right / m_Size.x);
	float fTop = (rtTmp.top / m_Size.y);
	float fBottom = (rtTmp.bottom / m_Size.y);
	VertexList[0].Tex = Vector2(fLeft, fTop);
	VertexList[1].Tex = Vector2(fRight, fTop);
	VertexList[2].Tex = Vector2(fRight, fBottom);
	VertexList[3] = VertexList[0];
	VertexList[4] = VertexList[2];
	VertexList[5].Tex = Vector2(fLeft, fBottom);
}

void JDxObjectSample::UpdatePos(fRECT deck)
{
	fRECT tmp = deck;
	tmp.right = tmp.right + tmp.left;
	tmp.bottom = tmp.bottom + tmp.top;
	tmp.left = (tmp.left / 960.0f) * 2.0f - 1.0f;
	tmp.right = (tmp.right / 960.0f) * 2.0f - 1.0f;
	tmp.top = ((tmp.top / 480.0f) * 2.0f - 1.0f) * -1.0f;
	tmp.bottom = ((tmp.bottom / 480.0f) * 2.0f - 1.0f) * -1.0f;
	VertexList[0].Pos = Vector3(tmp.left, tmp.top, 0.5f);
	VertexList[1].Pos = Vector3(tmp.right, tmp.top, 0.5f);
	VertexList[2].Pos = Vector3(tmp.right, tmp.bottom, 0.5f);
	VertexList[3].Pos = VertexList[0].Pos;
	VertexList[4].Pos = VertexList[2].Pos;
	VertexList[5].Pos = Vector3(tmp.left, tmp.bottom, 0.5f);
	CreateVertexBuffer(g_pd3dDevice, VertexList);
}
bool JDxObjectSample::UpdatePosition(fRECT rt)
{
	m_rt.left = m_Pos.x;
	m_rt.top = m_Pos.y;
	//m_rt.right = m_Pos.x + 100.0f;
	//m_rt.bottom = m_Pos.y + 100.0f;
	UpdatePos(m_rt);
	return true;
}
bool JDxObjectSample::Frame()
{
	//Left();
	//UpdatePos();
	return true;
}

bool JDxObjectSample::Init()
{
	return true;
}
bool JDxObjectSample::Release()
{
	m_pVertexBuffer->Release(); 
	m_pIndexBuffer->Release();
	if(m_Image) 
		m_Image->m_pTexSRV->Release();
	if(m_ImageMask) 
		m_ImageMask->m_pTexSRV->Release();
	return true;
}
JDxObjectSample::JDxObjectSample()
{
}
JDxObjectSample::~JDxObjectSample()
{
}
