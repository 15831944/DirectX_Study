#include "JInterface.h"

bool JInterface::Create(ID3D11Device* device, const char* szVSVersion, const char* szPSVersion,
	const TCHAR* szVSFileName, const TCHAR* szPSFileName)
{
	CreateVertexShader(device, szVSFileName, szVSVersion);
	m_pPS = CreatePixelShader(device, szPSFileName, szPSVersion);
	CreateLayout(device);
	m_pSS[0] = CreateSamplerState(device, D3D11_TEXTURE_ADDRESS_WRAP);
	m_pSS[1] = CreateSamplerState(device, D3D11_TEXTURE_ADDRESS_MIRROR);
	m_pSS[2] = CreateSamplerState(device, D3D11_TEXTURE_ADDRESS_CLAMP);
	if (pVSBuffer) pVSBuffer->Release();
	if (pPSBuffer) pPSBuffer->Release();
	if (pErrorBuffer) pErrorBuffer->Release();

	return true;
}
HRESULT JInterface::CreateVertexShader(ID3D11Device* device, const TCHAR* szLoadFileName, const char* szVSVersion)
{
	HRESULT hr;
	if (FAILED(hr = D3DX11CompileFromFile(szLoadFileName, NULL, NULL, szVSVersion, "vs_5_0", 0, 0, NULL, &pVSBuffer, &pErrorBuffer, NULL)))
	{
		OutputDebugStringA((char*)pErrorBuffer->GetBufferPointer());
		return hr;
	}
	device->CreateVertexShader(pVSBuffer->GetBufferPointer(), pVSBuffer->GetBufferSize(), NULL, &m_pVS);
	return hr;
}
ID3D11PixelShader* JInterface::CreatePixelShader(ID3D11Device* device, const TCHAR* szLoadFileName, const char* szPSVersion)
{
	HRESULT hr;
	ID3D11PixelShader* PS;
	if (FAILED(hr = D3DX11CompileFromFile(szLoadFileName, NULL, NULL, szPSVersion, "ps_5_0", 0, 0, NULL, &pPSBuffer, &pErrorBuffer, NULL)))
	{
		OutputDebugStringA((char*)pErrorBuffer->GetBufferPointer());
		return NULL;
	}
	if (FAILED(hr = device->CreatePixelShader(pPSBuffer->GetBufferPointer(), pPSBuffer->GetBufferSize(), NULL, &PS)))
	{
		return NULL;
	}
	return PS;
}
HRESULT JInterface::CreateLayout(ID3D11Device* device)
{
	HRESULT hr;
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};
	int iNumElement = sizeof(ied) / sizeof(ied[0]);
	if (FAILED(hr = device->CreateInputLayout(ied, iNumElement, pVSBuffer->GetBufferPointer(), pVSBuffer->GetBufferSize(), &m_pIL)))
	{
		return hr;
	}
	return hr;
}

ID3D11SamplerState* JInterface::CreateSamplerState(ID3D11Device* device, D3D11_TEXTURE_ADDRESS_MODE adress, D3D11_FILTER filer)
{
	HRESULT hr;
	ID3D11SamplerState* SamplerState;
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
	sd.Filter = filer;
	sd.AddressU = adress;
	sd.AddressV = adress;
	sd.AddressW = adress;
	if (FAILED(hr = device->CreateSamplerState(&sd, &SamplerState)))
	{
		return SamplerState;
	}

	return SamplerState;
}

bool JInterface::Release()
{
	for (int iIndex = 0; iIndex < 3; iIndex++)
	{
		m_pSS[iIndex]->Release();
	}
	m_pPS->Release();
	m_pVS->Release();
	m_pIL->Release();
	return true;
}

JInterface::JInterface()
{
}


JInterface::~JInterface()
{
}
