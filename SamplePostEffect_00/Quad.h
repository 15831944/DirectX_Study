#pragma once
#include "JPlaneShape.h"
#define MAX_MASKCOUNT 25
struct KernelMask
{
	float fMask[MAX_MASKCOUNT * MAX_MASKCOUNT];
};
struct VSCB2
{
	float g_fMask;
	float g_fTexSizeX;
	float g_fTexSizeY;
	float a;
};
class Quad : public JPlaneShape
{
public:
	ID3D11Texture2D* m_pColorTex;
	ID3D11ShaderResourceView* m_pColorSRV;
	ID3D11RenderTargetView* m_pColorRTV;

	ID3D11Texture2D* m_pNormalDepthTex;
	ID3D11ShaderResourceView* m_pNormalDepthSRV;
	ID3D11RenderTargetView* m_pNormalDepthRTV;

	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11Buffer* m_pMaskCB;
	VSCB2 m_MaskValue;
	ID3D11Buffer* m_pMaskBuffer;
	ID3D11ShaderResourceView* m_pMaskArray;
	int m_iMask;
	float* m_pfKernelMask;
public:
	HRESULT CreateConstantBuffer(ID3D11Device* device);
	HRESULT CreateTextures(ID3D11Device* device, UINT iWidth, UINT iHeight);
	bool SetBuffer(ID3D11Device* device);
	bool Frame();
	bool Render(ID3D11DeviceContext* context);
	void ComputeKernel(int iMask = 3);
public:
	Quad();
	virtual ~Quad();
};

