#include "JState.h"
namespace UI
{
	ID3D11RasterizerState*	 JState::g_pRSWireFrame = 0;
	ID3D11RasterizerState*	 JState::g_pRSBackCullSolid = 0;
	ID3D11RasterizerState*	 JState::g_pRSNoneCullSolid = 0;
	ID3D11RasterizerState* 	 JState::g_pRSFrontCullSolid = 0;
	ID3D11RasterizerState*   JState::g_pRSDepthShadow = 0;

	ID3D11DepthStencilState* JState::g_pEnableDSS = 0;
	ID3D11DepthStencilState* JState::g_pDisableDSS = 0;

	ID3D11BlendState*		 JState::g_pAlphaBlend = 0;
	ID3D11BlendState*		 JState::g_pNoAlphaBlend = 0;
	ID3D11BlendState*		 JState::g_pColorBlend = 0;

	ID3D11SamplerState*		 JState::g_pTexSS = 0;
	ID3D11SamplerState*		 JState::g_pSSShadowMap = 0;
	ID3D11SamplerState*		 JState::g_pClampLinear = 0;

	HRESULT JState::SetState(ID3D11Device*	pd3dDevice)
	{
		//===========================================================
		//=======================SamplerState========================
		//===========================================================
		HRESULT hr = S_OK;
		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.BorderColor[0] = 1.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 1.0f;
		samplerDesc.MaxAnisotropy = 16;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.MaxLOD = FLT_MAX;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MinLOD = FLT_MIN;
		if (FAILED(hr = pd3dDevice->CreateSamplerState(&samplerDesc, &g_pTexSS)))
			return hr;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		if (FAILED(hr = pd3dDevice->CreateSamplerState(&samplerDesc, &g_pClampLinear)))
			return hr;
		//===========================================================
		//=======================AlphaBlend==========================
		//===========================================================
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
		blendDesc.AlphaToCoverageEnable = FALSE;
		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		pd3dDevice->CreateBlendState(&blendDesc, &g_pAlphaBlend);

		blendDesc.RenderTarget[0].BlendEnable = FALSE;
		pd3dDevice->CreateBlendState(&blendDesc, &g_pNoAlphaBlend);

		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		pd3dDevice->CreateBlendState(&blendDesc, &JState::g_pColorBlend);

		//===========================================================
		//=======================DepthState==========================
		//===========================================================
		D3D11_DEPTH_STENCIL_DESC dsd;
		ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));
		dsd.DepthEnable = TRUE;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsd.StencilEnable = FALSE;

		pd3dDevice->CreateDepthStencilState(&dsd, &g_pEnableDSS);
		dsd.DepthEnable = FALSE;
		pd3dDevice->CreateDepthStencilState(&dsd, &g_pDisableDSS);
		//=============================================================
		//=======================RasterizeState========================
		//=============================================================
		D3D11_RASTERIZER_DESC rsDesc;
		ZeroMemory(&rsDesc, sizeof(rsDesc));
		rsDesc.DepthClipEnable = TRUE;
		rsDesc.FillMode = D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_BACK;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &JState::g_pRSWireFrame)))
			return hr;
		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_BACK;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &JState::g_pRSBackCullSolid)))
			return hr;

		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_NONE;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &JState::g_pRSNoneCullSolid)))
			return hr;

		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_FRONT;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &JState::g_pRSFrontCullSolid)))
			return hr;

		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_BACK;
		rsDesc.DepthBias = 5000;
		rsDesc.DepthBiasClamp = 0.0f;
		rsDesc.SlopeScaledDepthBias = 1.0f;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &JState::g_pRSDepthShadow)))
			return hr;

		D3D11_SAMPLER_DESC SamDescShad =
		{
			D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,// D3D11_FILTER Filter;
			D3D11_TEXTURE_ADDRESS_BORDER, //D3D11_TEXTURE_ADDRESS_MODE AddressU;
			D3D11_TEXTURE_ADDRESS_BORDER, //D3D11_TEXTURE_ADDRESS_MODE AddressV;
			D3D11_TEXTURE_ADDRESS_BORDER, //D3D11_TEXTURE_ADDRESS_MODE AddressW;
			0,//FLOAT MipLODBias;
			0,//UINT MaxAnisotropy;
			D3D11_COMPARISON_LESS , //D3D11_COMPARISON_FUNC ComparisonFunc;
			0.0,0.0,0.0,0.0,//FLOAT BorderColor[ 4 ];
			0,//FLOAT MinLOD;
			0//FLOAT MaxLOD;   
		};
		if (FAILED(hr = pd3dDevice->CreateSamplerState(&SamDescShad, &g_pSSShadowMap)))
		{
			return hr;
		}
		return hr;
	}
	bool JState::Release()
	{
		SAFE_RELEASE(g_pTexSS);
		SAFE_RELEASE(g_pAlphaBlend);
		SAFE_RELEASE(g_pNoAlphaBlend);
		SAFE_RELEASE(g_pColorBlend);
		SAFE_RELEASE(g_pEnableDSS);
		SAFE_RELEASE(g_pDisableDSS);
		SAFE_RELEASE(g_pRSWireFrame);
		SAFE_RELEASE(g_pRSBackCullSolid);
		SAFE_RELEASE(g_pRSNoneCullSolid);
		SAFE_RELEASE(g_pRSFrontCullSolid);
		return true;
	}
}