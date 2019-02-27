#include "JCore.h"
#include "JMap.h"
class Sample :public JCore
{
public:
	ID3D11HullShader* m_pHS;
	ID3D11DomainShader* m_pDS;
	ID3DBlob* m_pBlob;
	JMap map; 
public:
	ID3D11HullShader* LoadHullShader(ID3D11Device* device, const TCHAR* szLoadFileName, ID3DBlob** ppBlobOut = 0, const char* szShaderFunc = 0)
	{
		HRESULT hr = S_OK;
		ID3DBlob* pBlob = 0;
		ID3D11HullShader* HS = 0;
		if (szShaderFunc == 0)
		{
			if (FAILED(hr = CompileShader(device, szLoadFileName, &pBlob, "HS", "hs_5_0")))
			{
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = CompileShader(device, szLoadFileName, &pBlob, szShaderFunc, "hs_5_0")))
			{
				return nullptr;
			}
		}
		DWORD dwSize = 0;
		LPCVOID lpData = 0;
		dwSize = pBlob->GetBufferSize();
		lpData = pBlob->GetBufferPointer();

		if (FAILED(hr = device->CreateHullShader(lpData, dwSize, NULL, &HS)))
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
		return HS;
	}
public:
	bool Init()
	{
		map.Init();
		map.SetHeightTexture(GetContext(), L"../../Data/Height_Castle.bmp");
		map.Create(GetDevice(), 64, 64, 1.0f);
		map.m_dxObj.m_pTexture = I_TexMgr.GetPtr(I_TexMgr.Add(GetDevice(), L"../../Data/Castle.jpg"));
		m_pHS = LoadHullShader(GetDevice(), L"hs.hlsl", &m_pBlob);
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		return true;
	}
	bool Release()
	{
		return true;
	}
}; RUN;