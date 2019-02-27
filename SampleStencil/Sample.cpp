#include "JCore.h"
#include "JBoxShape.h"
#include "JPlaneShape.h"
class Sample : public JCore
{
public:
	JBoxShape* m_pBox;
	JPlaneShape* m_pPlane;
	D3DXMATRIX m_matWorld[2];
	ID3D11DepthStencilState*			m_pStencilA;
	ID3D11DepthStencilState*			m_pStencilB;
public:
	bool Init()
	{
		m_pBox = new JBoxShape();
		m_pPlane = new JPlaneShape();

		m_pBox->Init();
		m_pPlane->Init();

		int m_iTexture = I_TexMgr.Add(GetDevice(), L"../../Data/Effect/effect_01.png");
		m_pBox->m_dxObj.m_pTexture = I_TexMgr.GetPtr(m_pBox->m_dxObj.m_iTexture);

		m_iTexture = I_TexMgr.Add(GetDevice(), L"../../data/Bitmap/BackGround.bmp");
		m_pPlane->m_dxObj.m_pTexture = I_TexMgr.GetPtr(m_pPlane->m_dxObj.m_iTexture);

		D3DXVECTOR3 Pos = D3DXVECTOR3(0,0,-20);
		D3DXVECTOR3 At = D3DXVECTOR3(0, 0, 0);
		D3DXVECTOR3 Up = D3DXVECTOR3(0, 1, 0);
		m_Camera[0].SetViewMatrix(Pos, At, Up);

//============================================================Stencil
		D3D11_DEPTH_STENCIL_DESC dsd;
		ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));
		dsd.DepthEnable = TRUE;
		dsd.StencilEnable = TRUE;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsd.DepthFunc = D3D11_COMPARISON_ALWAYS;
		dsd.StencilReadMask = 0xff;
		dsd.StencilWriteMask = 0xff;

		dsd.FrontFace.StencilFunc				= D3D11_COMPARISON_ALWAYS;
		dsd.FrontFace.StencilDepthFailOp		= D3D11_STENCIL_OP_KEEP;
		dsd.FrontFace.StencilFailOp				= D3D11_STENCIL_OP_KEEP;
		dsd.FrontFace.StencilPassOp				= D3D11_STENCIL_OP_INCR;

		dsd.BackFace.StencilFunc				= D3D11_COMPARISON_ALWAYS;
		dsd.BackFace.StencilDepthFailOp			= D3D11_STENCIL_OP_KEEP;
		dsd.BackFace.StencilFailOp				= D3D11_STENCIL_OP_KEEP;
		dsd.BackFace.StencilPassOp				= D3D11_STENCIL_OP_KEEP;


		GetDevice()->CreateDepthStencilState(&dsd, &m_pStencilA);

		dsd.DepthEnable = TRUE;
		dsd.StencilEnable = TRUE;
		dsd.FrontFace.StencilFunc				= D3D11_COMPARISON_EQUAL;
		dsd.FrontFace.StencilDepthFailOp		= D3D11_STENCIL_OP_KEEP;
		dsd.FrontFace.StencilFailOp				= D3D11_STENCIL_OP_KEEP;
		dsd.FrontFace.StencilPassOp				= D3D11_STENCIL_OP_KEEP;

		dsd.BackFace.StencilFunc				= D3D11_COMPARISON_ALWAYS;
		dsd.BackFace.StencilDepthFailOp			= D3D11_STENCIL_OP_KEEP;
		dsd.BackFace.StencilFailOp				= D3D11_STENCIL_OP_KEEP;
		dsd.BackFace.StencilPassOp				= D3D11_STENCIL_OP_KEEP;

		GetDevice()->CreateDepthStencilState(&dsd, &m_pStencilB);

		return true;
	}
	bool Frame()
	{
		D3DXMATRIX m_matT,m_matS;
		D3DXMatrixScaling(&m_matS, 3, 3, 3);
		D3DXMatrixTranslation(&m_matT, 0, 0, -10);
		m_matWorld[0] = m_matS *m_matT;
		float fTime = I_Timer.m_fGameTimer * D3DX_PI;
		D3DXMatrixTranslation(&m_matWorld[1], cos(fTime * 0.5f) * 10.0f, 0, 0);

		return true;
	}
	bool Render()
	{
		GetContext()->OMSetDepthStencilState(m_pStencilB, 1);
		GetContext()->PSSetShaderResources(0, 1, &m_pPlane->m_dxObj.m_pTexture->m_pSRV);
		m_pPlane->m_cbData.vColor = D3DXVECTOR4(0, 0, 0, 1);
		m_pPlane->SetMatrix(&m_matWorld[0], &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_pPlane->Render(GetContext());

		GetContext()->OMSetDepthStencilState(m_pStencilA, 1);
		GetContext()->PSSetShaderResources(0, 1, &m_pBox->m_dxObj.m_pTexture->m_pSRV);
		m_pBox->m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
		m_pBox->SetMatrix(&m_matWorld[1], &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_pBox->Render(GetContext());

		return true;
	}
	bool Release()
	{
		m_pBox->Release();
		m_pPlane->Release();
		return true;
	}
};
RUN;