#include "JDxHelper.h"
namespace UI
{
	ID3D11Buffer* CreateIndexBuffer(ID3D11Device* device, void* pData, UINT iSize, UINT iNumCount, bool bDynamic)
	{
		HRESULT hr = S_OK;
		ID3D11Buffer* pBuffer = 0;
		D3D11_BUFFER_DESC pDesc;
		ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
		if (bDynamic)
		{
			pDesc.Usage = D3D11_USAGE_DYNAMIC;
			pDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			pDesc.Usage = D3D11_USAGE_DEFAULT;
			pDesc.CPUAccessFlags = 0;
		}
		pDesc.ByteWidth = iSize * iNumCount;
		pDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		pDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA pInitialData;
		ZeroMemory(&pInitialData, sizeof(D3D11_SUBRESOURCE_DATA));
		pInitialData.pSysMem = pData;

		if (FAILED(hr = device->CreateBuffer(&pDesc, &pInitialData, &pBuffer)))
		{
			return NULL;
		}
		return pBuffer;
	}
	ID3D11Buffer* CreateConstantBuffer(ID3D11Device* device, void* pData, UINT iSize, UINT iNumCount, bool bDynamic)
	{
		HRESULT hr = S_OK;
		ID3D11Buffer* pBuffer = 0;
		D3D11_BUFFER_DESC pDesc;
		ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
		pDesc.ByteWidth = iSize * iNumCount;
		if (bDynamic)
		{
			pDesc.Usage = D3D11_USAGE_DYNAMIC;
			pDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			pDesc.Usage = D3D11_USAGE_DEFAULT;
			pDesc.CPUAccessFlags = 0;
		}
		pDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		pDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA pInitialData;
		ZeroMemory(&pInitialData, sizeof(D3D11_SUBRESOURCE_DATA));
		pInitialData.pSysMem = pData;
		if (pData == NULL)
		{
			if (FAILED(hr = device->CreateBuffer(&pDesc, NULL, &pBuffer)))
			{
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = device->CreateBuffer(&pDesc, &pInitialData, &pBuffer)))
			{
				return nullptr;
			}
		}
		return pBuffer;
	}
	ID3D11Buffer* CreateVertexBuffer(ID3D11Device* device, void* pData, UINT iSize, UINT iNumCount, bool bDynamic)
	{
		HRESULT hr = S_OK;
		ID3D11Buffer* pBuffer = 0;
		D3D11_BUFFER_DESC pDesc;
		ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
		pDesc.ByteWidth = iSize * iNumCount;
		if (bDynamic)
		{
			pDesc.Usage = D3D11_USAGE_DYNAMIC;
			pDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			pDesc.Usage = D3D11_USAGE_DEFAULT;
			pDesc.CPUAccessFlags = 0;
		}
		pDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		pDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA pInitialData;
		ZeroMemory(&pInitialData, sizeof(D3D11_SUBRESOURCE_DATA));
		pInitialData.pSysMem = pData;

		if (FAILED(hr = device->CreateBuffer(&pDesc, &pInitialData, &pBuffer)))
		{
			return NULL;
		}
		return pBuffer;
	}

	ID3D11VertexShader* LoadVertexShader(ID3D11Device* device, const TCHAR* szLoadFileName, ID3DBlob** ppBlobOut, const char* szShaderFunc)
	{
		HRESULT hr = S_OK;
		ID3DBlob* pBlob = 0;
		ID3D11VertexShader* VS = 0;
		if (szShaderFunc == 0)
		{
			if (FAILED(hr = CompileShader(szLoadFileName, &pBlob, "VS", "vs_5_0")))
			{
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = CompileShader(szLoadFileName, &pBlob, szShaderFunc, "vs_5_0")))
			{
				return nullptr;
			}
		}
		DWORD dwSize = 0;
		LPCVOID lpData = 0;
		dwSize = (DWORD)pBlob->GetBufferSize();
		lpData = pBlob->GetBufferPointer();

		if (FAILED(hr = device->CreateVertexShader(lpData, dwSize, NULL, &VS)))
		{
			pBlob->Release();
			return nullptr;
		}
		if (ppBlobOut == nullptr)
		{
			pBlob->Release();
			return nullptr;
		}
		else
		{
			*ppBlobOut = pBlob;
		}
		return VS;
	}
	ID3D11PixelShader* LoadPixelShader(ID3D11Device* device, const TCHAR* szLoadFileName, ID3DBlob** ppBlobOut, const char* szShaderFunc)
	{
		HRESULT hr = S_OK;
		ID3DBlob* pBlob = 0;
		ID3D11PixelShader* PS = 0;
		if (szShaderFunc == 0)
		{
			if (FAILED(hr = CompileShader(szLoadFileName, &pBlob, "PS", "ps_5_0")))
			{
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = CompileShader(szLoadFileName, &pBlob, szShaderFunc, "ps_5_0")))
			{
				return nullptr;
			}
		}
		DWORD dwSize = 0;
		LPCVOID lpData = 0;
		dwSize = (DWORD)pBlob->GetBufferSize();
		lpData = pBlob->GetBufferPointer();

		if (FAILED(hr = device->CreatePixelShader(lpData, dwSize, NULL, &PS)))
		{
			pBlob->Release();
			return nullptr;
		}
		if (ppBlobOut == nullptr)
		{
			pBlob->Release();
			return nullptr;
		}
		else
		{
			*ppBlobOut = pBlob;
		}
		return PS;
	}
	ID3D11InputLayout* CreateLayout(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* IED, int ElementCnt, ID3DBlob* pVSBlob)
	{
		HRESULT hr = S_OK;
		ID3D11InputLayout* ILOut = 0;
		DWORD dwSize = (DWORD)pVSBlob->GetBufferSize();
		LPCVOID dwPoint = pVSBlob->GetBufferPointer();
		if (FAILED(hr = device->CreateInputLayout(IED, ElementCnt, dwPoint, dwSize, &ILOut)))
		{
			return nullptr;
		}
		return ILOut;
	}
	HRESULT CompileShader(const TCHAR* szLoadFileName, ID3DBlob** pBlob, const char* szShaderFunc, const char* szShaderModel)
	{
		HRESULT hr = S_OK;
		ID3DBlob* pErrorBlob = 0;
		if (FAILED(hr = D3DX11CompileFromFile(szLoadFileName, NULL, NULL, szShaderFunc, szShaderModel, 0, 0, NULL, pBlob, &pErrorBlob, NULL)))
		{
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
			return hr;
		}
		return hr;
	}
}