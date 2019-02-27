#include "JCore.h"
#include "NormalMap.h"
struct VS_CBChangesEveryFrame
{
	D3DXMATRIX      matNormal;
	D3DXVECTOR3		vLightPos;
	float			f1;
	D3DXVECTOR3		vEye;
	float			f2;
	D3DXVECTOR3		vEyeDir;
	float			f3;
};
struct VS_CBNeverChanges
{
	D3DXVECTOR4				cb_AmbientLightColor;
	D3DXVECTOR4				cb_DiffuseLightColor;
	D3DXVECTOR4				cb_SpecularLightColor;
};
class Sample : public JCore
{
public:
	NormalMap map;
	ID3D11Buffer*			m_pConstantBuffer;
	VS_CBNeverChanges		m_cbNeverChanges;
	ID3D11Buffer*			m_pCBNeverChanges;

	D3DXMATRIX				m_mLightWorld;
	D3DXVECTOR3				m_vInitLightPos;
	bool					m_bDebugRender;
	bool					m_bNormalMapRender;
	D3DXMATRIX				m_matInitWorld;
	D3DXMATRIX				m_matWorld;
public:
	bool Init()
	{
		map.Init();
		//map.SetHeightTexture(GetContext(), L"../../Data/heightMap513.bmp");
		map.m_strNormalMapName = L"../../Data/hr_n.bmp";
		map.Create(GetDevice(), 513, 513,1);
		map.LoadTextures(GetDevice(), L"../../Data/hr_n.bmp");
		map.UpdateBuffer();
		CreateConstantBuffer();
		D3DXMATRIX matScale, matTrans;
		D3DXMatrixScaling(&m_matInitWorld, 1.0f, 1.0f, 1.0f);
		m_vInitLightPos = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
		return true;
	}
	bool Frame()
	{
		float t = I_Timer.m_fGameTimer * D3DX_PI;
		D3DXMatrixMultiply(&m_matWorld, &m_matInitWorld, &m_MainCam->m_matWorld);

		D3DXMATRIX mTranslate, mRotation;
		D3DXMatrixTranslation(&mTranslate, m_vInitLightPos.x, m_vInitLightPos.y, m_vInitLightPos.z);
		D3DXMatrixRotationY(&mRotation, t*0.0f);
		D3DXMatrixMultiply(&m_mLightWorld, &mTranslate, &mRotation);

		// Ãß°¡

		D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
		if (SUCCEEDED(GetContext()->Map((ID3D11Resource*)m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedFaceDest)))
		{
			VS_CBChangesEveryFrame* pConstData = (VS_CBChangesEveryFrame*)MappedFaceDest.pData;

			pConstData->matNormal = map.m_matNormal;
			pConstData->vLightPos = D3DXVECTOR3(100,300,0);
			pConstData->vEye = m_MainCam->m_vLook;
			pConstData->vEyeDir = m_MainCam->m_vLook;
			GetContext()->Unmap(m_pConstantBuffer, 0);
		}
		
		return true;
	}
	bool Render()
	{
		map.SetMatrix(&m_matWorld, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		map.PreRender(GetContext());

		ID3D11Buffer* Buffer[2] = { map.m_dxObj.m_pVertexBuffer, map.m_pTangentVB };
		UINT stride[2] = { sizeof(PNCT_VERTEX), sizeof(D3DXVECTOR3) };
		UINT offset[2] = { 0, 0 };
		GetContext()->IASetVertexBuffers(0, 2, Buffer, stride, offset);

		GetContext()->PSSetShaderResources(1, 1, &map.m_pNormalTexture->m_pSRV);
		GetContext()->VSSetConstantBuffers(1, 1, &m_pConstantBuffer);
		GetContext()->VSSetConstantBuffers(2, 1, &m_pCBNeverChanges);
		GetContext()->PSSetConstantBuffers(1, 1, &m_pConstantBuffer);
		GetContext()->PSSetConstantBuffers(2, 1, &m_pCBNeverChanges);
		map.PostRender(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
	HRESULT CreateConstantBuffer();
};
RUN;
HRESULT Sample::CreateConstantBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(VS_CBChangesEveryFrame);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	hr = GetDevice()->CreateBuffer(&cbDesc, NULL, &m_pConstantBuffer);
	if (FAILED(hr))
		return hr;

	cbDesc.ByteWidth = sizeof(VS_CBNeverChanges);
	m_cbNeverChanges.cb_AmbientLightColor = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1);
	m_cbNeverChanges.cb_DiffuseLightColor = D3DXVECTOR4(1, 1, 1, 1);
	m_cbNeverChanges.cb_SpecularLightColor = D3DXVECTOR4(1, 1, 1, 30.0f);

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &m_cbNeverChanges;
	hr = GetDevice()->CreateBuffer(&cbDesc, &InitData, &m_pCBNeverChanges);
	if (FAILED(hr))
		return hr;

	return hr;
}