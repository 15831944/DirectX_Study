#include "JObject.h"
#include "JInput.h"
bool JObject::PreRender(ID3D11DeviceContext* context)
{
	UINT Strides = sizeof(JVertex);
	UINT Offsets = 0;
	context->IASetInputLayout(m_pIL);
	context->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Strides, &Offsets);
	context->VSSetShader(m_pVS, NULL, NULL);
	context->PSSetSamplers(0, 1, &m_pSS[0]);
	context->PSSetShader(m_pPS, NULL, NULL);
	if (m_ImageMask != NULL)
	{
		context->PSSetShaderResources(1, 1, &m_ImageMask->m_pTexSRV);
		context->PSSetShaderResources(0, 1, &m_Image->m_pTexSRV);
	}
	else
	{
		context->PSSetShaderResources(0, 1, &m_Image->m_pTexSRV);
	}
	return true;
}
bool JObject::Render(ID3D11DeviceContext* context)
{
	PreRender(context);
	PostRender(context);
	return true;
}
bool JObject::PostRender(ID3D11DeviceContext* context)
{
	context->Draw(VertexListCnt, 0);
	return true;
}


bool JObject::Load(ID3D11Device* device, const TCHAR* pszTexLoadName, const TCHAR* pszTexMaskLoadName)
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
ID3D11Buffer* JObject::CreateVertexBuffer(ID3D11Device* device)
{
	HRESULT hr;
	//ID3D11Buffer* TempBuffer;
	D3D11_BUFFER_DESC pDesc;
	ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
	pDesc.ByteWidth = sizeof(JVertex) * VertexListCnt;// sizeof(JVertex) * 6;
	pDesc.Usage = D3D11_USAGE_DEFAULT;
	pDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	pDesc.CPUAccessFlags = 0;
	pDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA pInitialData;
	ZeroMemory(&pInitialData, sizeof(D3D11_SUBRESOURCE_DATA));
	pInitialData.pSysMem = &VertexList;

	if (FAILED(hr = device->CreateBuffer(&pDesc, &pInitialData, &m_pVertexBuffer)))
	{
		return NULL;
	}
	return m_pVertexBuffer;
}
void JObject::SetRect(float left, float top, float right, float bottom)
{
	m_rt.left = left; m_rt.top = top; m_rt.right = right - left; m_rt.bottom = bottom - top;
	float fLeft = (left / 960.0f) * 2.0f - 1.0f;
	float fRight = (right / 960.0f) * 2.0f - 1.0f;
	float fTop = ((top / 480.0f) * 2.0f - 1.0f) * -1.0f;
	float fBottom = ((bottom / 480.0f) * 2.0f - 1.0f) * -1.0f;

	VertexList[0].Pos = Vector3(fLeft, fTop, 0.5f);
	VertexList[0].Tex = Vector2(0.0f, 0.0f);
	VertexList[0].Col = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	VertexList[1].Pos = Vector3(fRight, fTop, 0.5f);
	VertexList[1].Tex = Vector2(1.0f, 0.0f);
	VertexList[1].Col = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	VertexList[2].Pos = Vector3(fRight, fBottom, 0.5f);
	VertexList[2].Tex = Vector2(1.0f, 1.0f);
	VertexList[2].Col = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	VertexList[3] = VertexList[0];
	VertexList[4] = VertexList[2];
	VertexList[5].Pos = Vector3(fLeft, fBottom, 0.5f);
	VertexList[5].Tex = Vector2(0.0f, 1.0f);
	VertexList[5].Col = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}
void JObject::SetTex(fRECT& rt, fPOINT& m_Size)
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
void JObject::UpdatePos(fRECT deck)
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
	CreateVertexBuffer(g_pd3dDevice);
}
bool JObject::UpdatePosition(fRECT rt)
{
	m_rt.left = m_Pos.x;
	m_rt.top = m_Pos.y;
	UpdatePos(m_rt);
	return true;
}
bool JObject::Frame()
{
	return true;
}

bool JObject::Init()
{
	return true;
}
bool JObject::Release()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_Image);
	SAFE_RELEASE(m_ImageMask);

	return true;
}
JObject::JObject()
{
}
JObject::~JObject()
{
}
