#pragma once
#include "UI_Std.h"
class JState
{
public:
	static ID3D11RasterizerState*			g_pRSWireFrame;
	static ID3D11RasterizerState*			g_pRSBackCullSolid;
	static ID3D11RasterizerState*			g_pRSDepthShadow;
	static ID3D11RasterizerState*			g_pRSNoneCullSolid;
	static ID3D11RasterizerState*			g_pRSFrontCullSolid;
	static ID3D11DepthStencilState*			g_pEnableDSS;
	static ID3D11DepthStencilState*			g_pDisableDSS;
	static ID3D11SamplerState*				g_pSSShadowMap;
	static ID3D11SamplerState*				g_pTexSS;
	static ID3D11SamplerState*				g_pClampLinear;
	static ID3D11BlendState*				g_pAlphaBlend;
	static ID3D11BlendState*				g_pNoAlphaBlend;
	static ID3D11BlendState*				g_pColorBlend;
public:
	static HRESULT SetState(ID3D11Device*	pd3dDevice);
	static void SetRSState(ID3D11DeviceContext* pContext, ID3D11RasterizerState* pState);
	static void SetDSState(ID3D11DeviceContext* pContext, ID3D11DepthStencilState* pState);
	static void SetSamplerState(ID3D11DeviceContext* pContext, ID3D11SamplerState* pState);
	static void SetAlphaBlendState(ID3D11DeviceContext* pContext, ID3D11BlendState* pState);
	static bool Release();
};