#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)
#include "JCore.h"
#include "Minimap.h"
#include "JMap.h"
struct SHADOW_CONSTANT_BUFFER
{
	D3DXMATRIX			g_matShadow;
	float				g_ShadowID;
	float				g_iNumKernel;
	float				fZ, fW;
};

class Sample : public JCore
{
public:
	ID3D11Buffer* pDepthBuffer;
	SHADOW_CONSTANT_BUFFER cbDepth;

	Minimap Mmap;
	JMap map;
	JCamera ShadowCam;
	D3DXVECTOR3 vLight;
	JBoxShape box;
	D3DXMATRIX matbox[2], matTexture;
	ID3D11VertexShader* m_pShadowVS;
	ID3D11PixelShader* m_pShadowPS;
public:
	bool Init()
	{
		ID3DBlob* pVSBlob;
		ID3DBlob* pPSBlob;
		m_pShadowVS = DX::LoadVertexShader(g_pd3dDevice, L"DepthShadow.hlsl", &pVSBlob, "SHADOW_VS");
		m_pShadowPS = DX::LoadPixelShader(g_pd3dDevice, L"DepthShadow.hlsl", &pPSBlob, "SHADOW_PS");
		pDepthBuffer = CreateConstantBuffer(GetDevice(), &cbDepth, sizeof(SHADOW_CONSTANT_BUFFER), 1);

		matTexture = D3DXMATRIX(
			  0.5f, 0.0f, 0.0f, 0.0f
			, 0.0f, -0.5f, 0.0f, 0.0f
			, 0.0f, 0.0f, 1.0f, 0.0f
			, 0.5f, 0.5f, 0.0f, 1.0f);
			
		Mmap.Init();
		Mmap.Create(GetDevice(), 0, 400, 200, 200, 2048,2048);
		map.Create(GetDevice(), 33, 33, 1.0f,L"DepthShadow.hlsl");
		map.SetTexture(L"../../Data/Castle.jpg");

		box.Create("PS", "VS", L"DepthShadow.hlsl");
		box.SetTexture(L"../../Data/flagstone.bmp");
		float fX = map.m_iNumCols * 1.0f * map.m_iNumCols * 1.0f;
		float fY = map.m_iNumRows * 1.0f * map.m_iNumRows * 1.0f;
		float fD = sqrt(fX + fY);

		vLight = D3DXVECTOR3(15, 40, -35);
		D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 10.0f, -10.0f);
		D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		ShadowCam.SetViewMatrix(vLight, vTarget, vUp);
		D3DXMatrixOrthoOffCenterLH(&ShadowCam.m_matProj, -fD / 2.0f, fD / 2.0f, -fD / 2.0f, fD / 2.0f, 0, 100.0f);

		for (int iObj = 0; iObj < 2; iObj++)
		{
			D3DXMATRIX matScale, matRotation;
			if (iObj == 0)
			{
				D3DXMatrixTranslation(&matbox[iObj], 0,2,0);
				D3DXMatrixScaling(&matScale, 3, 1, 3);
			}
			else
			{
				D3DXMatrixTranslation(&matbox[iObj], 0, 4, 0);
				D3DXMatrixScaling(&matScale, 1, 1, 1);
			}
			matbox[iObj]._11 = matScale._11;
			matbox[iObj]._22 = matScale._22;
			matbox[iObj]._33 = matScale._33;

			//matbox[iObj]._41 = 0.0f;
			//matbox[iObj]._42 = matbox[iObj]._22 * (iObj + 1);
			//matbox[iObj]._43 = 0.0f;
		}
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		if (Mmap.BeginRender(GetContext(), D3DXVECTOR4(0, 0, 0, 1)))
		{
			GetContext()->RSSetState(JState::g_pRSDepthShadow);
			GetContext()->OMSetBlendState(JState::g_pAlphaBlend, 0, -1);
			GetContext()->OMSetDepthStencilState(JState::g_pEnableDSS, 0x00);

			map.SetMatrix(NULL, &ShadowCam.m_matView, &ShadowCam.m_matProj);
			map.PreRender(GetContext());
			GetContext()->VSSetShader(m_pShadowVS, NULL, 0);
			GetContext()->PSSetShader(NULL, NULL, 0);
			map.PostRender(GetContext());

			for (int ibox = 0; ibox < 3; ibox++)
			{
				box.SetMatrix(&matbox[ibox], &ShadowCam.m_matView, &ShadowCam.m_matProj);
				box.PreRender(GetContext());
				GetContext()->VSSetShader(m_pShadowVS, NULL, 0);
				GetContext()->PSSetShader(NULL, NULL, 0);
				box.PostRender(GetContext());
			}

			Mmap.EndRender(GetContext());
		}
		GetContext()->PSSetSamplers(1, 1, &JState::g_pClampLinear);
		GetContext()->PSSetSamplers(2, 1, &JState::g_pSSShadowMap);
		GetContext()->RSSetState(JState::g_pRSBackCullSolid);
		//GetContext()->OMSetBlendState(JState::g_pNoAlphaBlend, 0, -1);
		map.SetMatrix(NULL, GetView(), GetProj());
		map.PreRender(GetContext());

		D3DXMATRIX matWVPT = ShadowCam.m_matView * ShadowCam.m_matProj * matTexture;
		D3DXMatrixTranspose(&cbDepth.g_matShadow, &matWVPT);
		cbDepth.g_ShadowID = 0;
		cbDepth.g_iNumKernel = 3;
		GetContext()->UpdateSubresource(pDepthBuffer, 0, NULL, &cbDepth, 0, 0);
		GetContext()->VSSetConstantBuffers(1, 1, &pDepthBuffer);
		GetContext()->PSSetConstantBuffers(1, 1, &pDepthBuffer);
		GetContext()->PSSetShaderResources(1, 1, &Mmap.m_RT.m_pDSV_SRV);

		map.PostRender(GetContext());

		for (int ibox = 0; ibox < 2; ibox++)
		{
			box.SetMatrix(&matbox[ibox], GetView(), GetProj());
			box.PreRender(GetContext());

			D3DXMATRIX matWVPT = matbox[ibox] * ShadowCam.m_matView * ShadowCam.m_matProj * matTexture;
			D3DXMatrixTranspose(&cbDepth.g_matShadow, &matWVPT);
			cbDepth.g_ShadowID = 0;
			cbDepth.g_iNumKernel = 3;
			GetContext()->UpdateSubresource(pDepthBuffer, 0, NULL, &cbDepth, 0, 0);
			GetContext()->VSSetConstantBuffers(1, 1, &pDepthBuffer);
			GetContext()->PSSetConstantBuffers(1, 1, &pDepthBuffer);
			GetContext()->PSSetShaderResources(1, 1, &Mmap.m_RT.m_pDSV_SRV);

			box.PostRender(GetContext());
		}
		Mmap.Render(GetContext(), Mmap.m_RT.m_pDSV_SRV);


		I_Write.Draw(L"asdfjklasdjflkjsadlkf", 15);
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;