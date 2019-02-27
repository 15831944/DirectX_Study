#pragma once
#include "JImageMgr.h"
class JInterface : public JImageMgr
{
public:
	ID3D11SamplerState * m_pSS[3];
	ID3D11PixelShader* m_pPS;
	ID3D11VertexShader* m_pVS;
	ID3D11InputLayout* m_pIL;
	ID3DBlob* pVSBuffer;
	ID3DBlob* pPSBuffer;
	ID3DBlob* pErrorBuffer;
public:
	bool Create(ID3D11Device* device, const char* szVSVersion = "VS", const char* szPSVersion = "PS", 
		const TCHAR* szVSFileName = L"VertexShader.vsh", const TCHAR* szPSFileName = L"PixelShader.psh");

	HRESULT CreateVertexShader(ID3D11Device* device, const TCHAR* szLoadFileName, const char* szVSVersion = "VS");
	ID3D11PixelShader* CreatePixelShader(ID3D11Device* device, const TCHAR* szLoadFileName, const char* szPSVersion = "PS");
	HRESULT CreateLayout(ID3D11Device* device);
	ID3D11SamplerState* CreateSamplerState(ID3D11Device* device, D3D11_TEXTURE_ADDRESS_MODE adress, D3D11_FILTER filer = D3D11_FILTER_MIN_MAG_MIP_POINT);
public:
	bool Release();
public:
	JInterface();
	virtual ~JInterface();
};

