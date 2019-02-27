#include "JDxSprite.h"
bool JDxSprite::PreRender(ID3D11DeviceContext* context)
{
	UINT Strides = sizeof(JVertex);
	UINT Offsets = 0;
	if (m_ImageList[m_iStart].m_ImageMask != NULL)
	{
		context->PSSetSamplers(0, 1, &m_ImageList[m_iStart].m_pSS[0]);
		context->IASetInputLayout(m_ImageList[m_iStart].m_pIL);
		context->VSSetShader(m_ImageList[m_iStart].m_pVS, NULL, NULL);
		context->PSSetShader(m_ImageList[m_iStart].m_pPS, NULL, NULL);
		context->IASetVertexBuffers(0, 1, &m_ImageList[m_iStart].m_pVertexBuffer, &Strides, &Offsets);
		context->PSSetShaderResources(1, 1, &m_ImageList[m_iStart].m_ImageMask->m_pTexSRV);
		context->PSSetShaderResources(0, 1, &m_ImageList[m_iStart].m_Image->m_pTexSRV);
	}
	else
	{
		context->PSSetSamplers(0, 1, &m_ImageList[m_iStart].m_pSS[0]);
		context->IASetInputLayout(m_ImageList[m_iStart].m_pIL);
		context->VSSetShader(m_ImageList[m_iStart].m_pVS, NULL, NULL);
		context->PSSetShader(m_ImageList[m_iStart].m_pPS, NULL, NULL);
		context->IASetVertexBuffers(0, 1, &m_ImageList[m_iStart].m_pVertexBuffer, &Strides, &Offsets);
		context->PSSetShaderResources(0, 1, &m_ImageList[m_iStart].m_Image->m_pTexSRV);
	}
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return true;
}
bool JDxSprite::Render(ID3D11DeviceContext* context)
{
	if (!m_bPlay) return false;
	PreRender(context);
	PostRender(context);
	return true;
}
bool JDxSprite::PostRender(ID3D11DeviceContext* context)
{
	context->Draw(VertexListCnt, 0);
	return true;
}
bool JDxSprite::Frame(ID3D11DeviceContext* context)
{
	//SetTex(m_ImageList[m_iStart]., m_ImageSize);
	Update();
	return true;
}
void JDxSprite::SetUp(float fSec)
{
	m_fFrameUpdateSec = fSec / m_iMax;
}
void JDxSprite::Update()
{
	if (!m_bPlay) return;
	m_fFrameElapseSec += g_fSecPerFrame;
	if (m_fFrameElapseSec >= m_fFrameUpdateSec)
	{
		if (m_iStart++ >= m_iMax - 1)
		{
			m_iStart = 0;
			m_bPlay = false;
		}
		m_fFrameElapseSec = 0.0f;
	}
}
bool JDxSprite::Release()
{
	for (int iFrameCnt = 0; iFrameCnt < m_ImageList.size(); iFrameCnt++)
	{
		m_ImageList[iFrameCnt].m_pVertexBuffer->Release();
		if (m_ImageList[iFrameCnt].m_Image == NULL)
			m_ImageList[iFrameCnt].m_Image->m_pTexSRV->Release();
		if (m_ImageList[iFrameCnt].m_ImageMask != NULL)
			m_ImageList[iFrameCnt].m_ImageMask->m_pTexSRV->Release();
	}
	return true;
}
JDxSprite::JDxSprite()
{
	m_iStart = 0;
	m_iMax = 0;
	m_fFrameUpdateSec = 1.0f;
	m_fFrameElapseSec = 0.0f;
	m_bPlay = false;
	m_bLoop = true;
}

JDxSprite::~JDxSprite()
{

}
