#include "Quad.h"
#include "JInput.h"

HRESULT Quad::CreateConstantBuffer(ID3D11Device* device)
{
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(cbDesc));
	cbDesc.ByteWidth = sizeof(VSCB);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &m_MaskValue;
	hr = device->CreateBuffer(&cbDesc, NULL, &m_pMaskCB);
	return hr;
}
HRESULT Quad::CreateTextures(ID3D11Device* device, UINT iWidth, UINT iHeight)
{
	HRESULT hr = S_OK;
	// Create the offscreen buffer
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width = iWidth;
	texDesc.Height = iHeight;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	device->CreateTexture2D(&texDesc, NULL, &m_pColorTex);
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	device->CreateTexture2D(&texDesc, NULL, &m_pNormalDepthTex);

	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;
	RTVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	RTVDesc.Texture2D.MipSlice = 0;

	device->CreateRenderTargetView(m_pColorTex, &RTVDesc, &m_pColorRTV);
	RTVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	device->CreateRenderTargetView(m_pNormalDepthTex, &RTVDesc, &m_pNormalDepthRTV);

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MostDetailedMip = 0;
	SRVDesc.Texture2D.MipLevels = texDesc.MipLevels;

	device->CreateShaderResourceView(m_pColorTex, &SRVDesc, &m_pColorSRV);
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	device->CreateShaderResourceView(m_pNormalDepthTex, &SRVDesc, &m_pNormalDepthSRV);
	return S_OK;
}
bool Quad::SetBuffer(ID3D11Device* device)
{
	if (FAILED(CreateConstantBuffer(device)))
	{
		return false;
	}
	D3D11_BUFFER_DESC vbDesc =
	{
		MAX_MASKCOUNT * MAX_MASKCOUNT * sizeof(float),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0
	};
	device->CreateBuffer(&vbDesc, NULL, &m_pMaskBuffer);

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));
	SRVDesc.Format = DXGI_FORMAT_R32_FLOAT;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	SRVDesc.Buffer.ElementOffset = 0;
	SRVDesc.Buffer.ElementWidth = MAX_MASKCOUNT * MAX_MASKCOUNT;
	device->CreateShaderResourceView(m_pMaskBuffer, &SRVDesc, &m_pMaskArray);
	return true;
}
bool Quad::Frame()
{
	if (I_Input.KeyCheck('Z') == KEY_HOLD)
	{
		m_MaskValue.g_fMask += 3.0f*g_fSecPerFrame;
		if (m_MaskValue.g_fMask > 30.0f)
			m_MaskValue.g_fMask = 30;
	}
	if (I_Input.KeyCheck('C') == KEY_HOLD)
	{
		m_MaskValue.g_fMask -= 3.0f*g_fSecPerFrame;
		if (m_MaskValue.g_fMask < 3.0f)
			m_MaskValue.g_fMask = 3;
	}
	return true;
}
bool Quad::Render(ID3D11DeviceContext* context)
{
	PreRender(context);
	context->PSSetShaderResources(0, 1, &m_pColorSRV);
	context->PSSetShaderResources(1, 1, &m_pNormalDepthSRV);

	D3D11_BOX box;
	box.left = 0;
	box.right = m_iMask * m_iMask * sizeof(float);
	box.top = 0; box.bottom = 1;
	box.front = 0; box.back = 1;
	context->UpdateSubresource(m_pMaskBuffer, 0, &box, m_pfKernelMask, 0, 0);

	ID3D11ShaderResourceView* aRViews[1] = { m_pMaskArray };
	context->PSSetShaderResources(2, 1, aRViews);

	context->UpdateSubresource(m_pMaskCB, 0, NULL, &m_MaskValue, 0, 0);
	context->PSSetConstantBuffers(1, 1, &m_pMaskCB);

	PostRender(context);
	return true;
}
void Quad::ComputeKernel(int iMask)
{
	float sigma = 1.0f;
	m_iMask = iMask * 2 + 1;
	m_pfKernelMask = new float[m_iMask*m_iMask];
	float mean = m_iMask / 2.0f;
	float sum = 0.0f;
	for (int x = 0; x < m_iMask; ++x)
	{
		for (int y = 0; y < m_iMask; ++y)
		{
			m_pfKernelMask[x*m_iMask + y] = expf(-0.5 * (pow((x - mean) / sigma, 2.0f) + pow((y - mean) / sigma, 2.0f))) / (2 * 3.141592f * sigma * sigma);
			sum += m_pfKernelMask[x*m_iMask + y];
		}
	}
	for (int x = 0; x < m_iMask; ++x)
	{
		for (int y = 0; y < m_iMask; ++y)
		{
			m_pfKernelMask[x*m_iMask + y] /= sum;
		}
	}
}

Quad::Quad()
{
}


Quad::~Quad()
{
}
