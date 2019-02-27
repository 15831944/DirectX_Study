#include "JDxSprite.h"
bool JDxSprite::PreRender(ID3D11DeviceContext* context)
{
	UINT Strides = sizeof(JVertex);
	UINT Offsets = 0;
	context->PSSetSamplers(0, 1, &m_pSS[0]);
	context->IASetInputLayout(m_pIL);
	context->VSSetShader(m_pVS, NULL, NULL);
	context->PSSetShader(m_pPS, NULL, NULL);
	context->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Strides, &Offsets);
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
	SetUp(0.5f);
	SetTex(m_rtEffect[m_iStart], m_ImageSize);
	Update();
	return true;
}
bool JDxSprite::Release()
{
	m_rtEffect.clear();
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
