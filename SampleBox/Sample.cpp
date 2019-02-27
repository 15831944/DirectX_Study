#include "JCore.h"
#include "JDxObjectSample.h"
UINT VertexCnt = 0;
UINT indiceCnt = 0;
int a = 0;
class Sample : public JCore
{
public:
	JDxObjectSample				m_dxobj;
	VSCB					m_cbData;
	D3DXMATRIX				m_matWorld[2];
	D3DXMATRIX				m_matView;
	D3DXMATRIX				m_matProj;
	float						m_fAngleY;
	D3DXVECTOR3					m_vInitCameraPosition;
	D3DXVECTOR3					m_vCameraPosition;
	D3DXVECTOR3					m_vTargetPosition;

public:
	bool Init()
	{
		SimpleVertex vertices[] =
		{
			{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f),	D3DXVECTOR4(0.4f, 1.0f, 5.0f, 1.0f) },
			{ D3DXVECTOR3(1.0f, 1.0f, -1.0f),	D3DXVECTOR4(0.7f, 0.5f, 1.0f, 1.0f) },
			{ D3DXVECTOR3(1.0f, 1.0f, 1.0f),	D3DXVECTOR4(0.5f, 1.0f, 0.5f, 1.0f) },
			{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f),	D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f) },
			{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 1.0f, 1.0f) },
			{ D3DXVECTOR3(1.0f, -1.0f, -1.0f),	D3DXVECTOR4(0.5f, 1.0f, 0.5f, 1.0f) },
			{ D3DXVECTOR3(1.0f, -1.0f, 1.0f),	D3DXVECTOR4(0.5f, 1.0f, 0.5f, 1.0f) },
			{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f),	D3DXVECTOR4(1.0f, 0.6f, 0.5f, 1.0f) },
		};
		VertexCnt = sizeof(vertices) / sizeof(vertices[0]);
		m_dxobj.CreateVertexBuffer(GetDevice(),vertices, sizeof(SimpleVertex), VertexCnt);

		DWORD indices[] =
		{
			3,1,0,        2,1,3,        0,5,4,        1,5,0,

			3,4,7,        0,4,3,        1,6,5,        2,6,1,

			2,7,6,        3,7,2,        6,4,5,        7,4,6,
		};
		indiceCnt = sizeof(indices) / sizeof(indices[0]);
		m_dxobj.CreateIndexBuffer(GetDevice(), indices, sizeof(DWORD), indiceCnt);

		m_dxobj.CreateConstantBuffer(GetDevice(), &m_cbData, 1, sizeof(VSCB));

		m_dxobj.CreateVertexShader(GetDevice(), L"Sample.hlsl");
		m_dxobj.CreatePixelShader(GetDevice(), L"Sample.hlsl");
		m_dxobj.CreateLayout(GetDevice());

		D3DXMatrixIdentity(&m_matWorld[0]);
		D3DXMatrixIdentity(&m_matWorld[1]);

		m_vInitCameraPosition = D3DXVECTOR3(0.0f, 5.0f, -20.0f);
		m_vCameraPosition = m_vInitCameraPosition;
		m_vTargetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
		// 뷰 행렬
		D3DXMatrixLookAtLH(&m_matView, &m_vInitCameraPosition, &m_vTargetPosition, &Up);
		// 투영행렬
		D3DXMatrixPerspectiveFovLH(&m_matProj,
			(float)D3DX_PI * 0.25f,
			g_rtClient.right / (FLOAT)g_rtClient.bottom,
			1.0f,
			100.0f);
		D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
		return true;
	}
	bool Frame()
	{
		D3DXMATRIX mOrbit;
		D3DXMATRIX mSpin[2];
		D3DXMATRIX mScale;
		D3DXMATRIX mTranslate[2];
		float fTime = I_Timer.m_fGameTimer * D3DX_PI;
		D3DXMatrixRotationZ(&mSpin[0], fTime);
		D3DXMatrixScaling(&mScale, 0.5f, 0.5f, 0.5f); 
		D3DXMatrixTranslation(&mTranslate[0], -4.0f, 0.0f, 0.0f);
		D3DXMatrixRotationY(&mOrbit, fTime);
		m_matWorld[1] = mScale * mSpin[0] * mTranslate[0] * mOrbit;

		D3DXMatrixIdentity(&mTranslate[0]);
		D3DXMatrixIdentity(&mTranslate[1]);
		D3DXMatrixIdentity(&mSpin[0]);
		D3DXMatrixIdentity(&mSpin[1]);
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixIdentity(&mOrbit);
		static float RotateZ = 0;
		static float RotateY = 0;
		static float Scales = 0.5f;

		static float3 TranslatePos;
		static float3 RotatePos;

		if (I_Input.KeyCheck('D') == KEY_PUSH || I_Input.KeyCheck('D') == KEY_HOLD)
		{
			RotatePos.y -= g_fSecPerFrame * D3DX_PI;
			D3DXMatrixRotationY(&m_matWorld[0], RotatePos.y);
		}
		if (I_Input.KeyCheck('A') == KEY_PUSH || I_Input.KeyCheck('A') == KEY_HOLD)
		{
			RotatePos.y += g_fSecPerFrame * D3DX_PI;
			D3DXMatrixRotationY(&m_matWorld[0], RotatePos.y);
		}
		if (I_Input.KeyCheck('W') == KEY_PUSH || I_Input.KeyCheck('W') == KEY_HOLD)
		{
			RotatePos.x += g_fSecPerFrame * D3DX_PI;
			D3DXMatrixRotationZ(&m_matWorld[0], RotatePos.x);
		}
		if (I_Input.KeyCheck('S') == KEY_PUSH || I_Input.KeyCheck('S') == KEY_HOLD)
		{
			RotatePos.x -= g_fSecPerFrame * D3DX_PI;
			D3DXMatrixRotationZ(&m_matWorld[0], RotatePos.x);
		}
		if (I_Input.KeyCheck(VK_UP) == KEY_PUSH || I_Input.KeyCheck(VK_UP) == KEY_HOLD)
		{
			TranslatePos.y += g_fSecPerFrame * 3.0f;
			//D3DXMatrixTranslation(&mTranslate[1], 0.0f, TranslatePos.y, 0.0f);
		}
		if (I_Input.KeyCheck(VK_DOWN) == KEY_PUSH || I_Input.KeyCheck(VK_DOWN) == KEY_HOLD)
		{
			TranslatePos.y -= g_fSecPerFrame * 3.0f;
			//D3DXMatrixTranslation(&mTranslate[1], 0.0f, TranslatePos.y, 0.0f);
		}
		if (I_Input.KeyCheck(VK_LEFT) == KEY_PUSH || I_Input.KeyCheck(VK_LEFT) == KEY_HOLD)
		{
			TranslatePos.x -= g_fSecPerFrame * 3.0f;
			//D3DXMatrixTranslation(&mTranslate[0], TranslatePos.x, 0.0f, 0.0f);
		}
		if (I_Input.KeyCheck(VK_RIGHT) == KEY_PUSH || I_Input.KeyCheck(VK_RIGHT) == KEY_HOLD)
		{
			TranslatePos.x += g_fSecPerFrame * 3.0f;
			//	D3DXMatrixTranslation(&mTranslate[0], TranslatePos.x, 0.0f, 0.0f);
		}
		if (I_Input.KeyCheck(VK_F4) == KEY_PUSH || I_Input.KeyCheck(VK_F4) == KEY_HOLD)
		{
			Scales += g_fSecPerFrame;
			D3DXMatrixScaling(&mScale, Scales, Scales, Scales);
		}
		if (I_Input.KeyCheck(VK_F3) == KEY_PUSH || I_Input.KeyCheck(VK_F3) == KEY_HOLD)
		{
			Scales -= g_fSecPerFrame;
			D3DXMatrixScaling(&mScale, Scales, Scales, Scales);
		}
		
		D3DXMatrixRotationZ(&mSpin[0], RotatePos.x);  
		D3DXMatrixRotationY(&mSpin[1], RotatePos.y);
		D3DXMatrixTranslation(&mTranslate[0], TranslatePos.x, 0.0f, 0.0f);
		D3DXMatrixTranslation(&mTranslate[1], 0.0f, TranslatePos.y, 0.0f);
		D3DXMatrixScaling(&mScale, Scales, Scales, Scales);
		
		m_matWorld[0] = mSpin[0] * mSpin[1] * mScale * mTranslate[0] * mTranslate[1] * mOrbit;
		D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);

		//새로운 카메라 위치 = 현재 카메라 위치 * 결합된 회전 행렬; 
		//D3DXVec3TransformCoord(&m_vCameraPosition, &m_vInitCameraPosition, &mSpin[0]);
		//D3DXVec3TransformCoord(&Up, &Up, &mSpin[1]);
		D3DXMatrixLookAtLH(&m_matView, &m_vCameraPosition, &m_vTargetPosition, &Up);
		D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
		return true;
	}
	bool Render()
	{
		D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld[0]);
		GetContext()->UpdateSubresource(m_dxobj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
		m_dxobj.Render(GetContext(), sizeof(SimpleVertex), 36);

		D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld[1]);
		GetContext()->UpdateSubresource(m_dxobj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
		m_dxobj.Render(GetContext(), sizeof(SimpleVertex), 36);
		return true;
	}
	bool Release()
	{
		return true;
	}
	Sample()
	{
	}
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow)
{
	Sample core;
	if (core.SetWindow(hInstance, 800, 600, L"DirectX Sample Box"))
	{
		core.Run();
		return 0;
	}
	return 1;
}
//RenderTarget+ ResourceView + DepthStencilView + Viewport Class 