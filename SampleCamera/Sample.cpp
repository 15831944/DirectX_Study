#include "JCore.h"
#include "JDxHelper.h"
#include "JDxObject.h"
using namespace DX;
class SampleCamera
{
public:
	D3DXMATRIX					m_matWorld;
	D3DXMATRIX					m_matView;
	D3DXMATRIX					m_matProj;
	D3DXVECTOR3					m_vLook;
	D3DXVECTOR3					m_vRight;
	D3DXVECTOR3					m_vUp;

	D3DXVECTOR3					m_vCameraPos;
	D3DXVECTOR3					m_vTargetPos;
	D3DXVECTOR3					m_vDirection;

	FLOAT						m_fFovy;
	FLOAT						m_fAspect;
	FLOAT						m_fNearPlane;
	FLOAT						m_fFarPlane;

	FLOAT						m_fYaw;    // y
	FLOAT						m_fPitch;  // x
	FLOAT						m_fRoll;   // z
	FLOAT						m_fRadius; // w

	float						m_fSpeed;

	TCHAR						m_szCameraPos[256];
public:
	D3DXMATRIX SetViewMatrix(D3DXVECTOR3 vPosition, D3DXVECTOR3 vTarget, D3DXVECTOR3 vUp)
	{
		m_vCameraPos = vPosition;
		m_vTargetPos = vTarget;

		D3DXMatrixLookAtLH(&m_matView, &vPosition, &vTarget, &vUp);
		m_vLook.x = m_matView._13;
		m_vLook.y = m_matView._23;
		m_vLook.z = m_matView._33;
		m_vRight.x = m_matView._11;
		m_vRight.y = m_matView._21;
		m_vRight.z = m_matView._31;
		m_vUp.x = m_matView._12;
		m_vUp.y = m_matView._22;
		m_vUp.z = m_matView._32;

		return m_matView;
	}
	D3DXMATRIX SetProjMatrix(float Fovy,float Aspect, float Near, float Far)
	{
		m_fFovy = Fovy;
		m_fAspect = Aspect;
		m_fNearPlane = Near;
		m_fFarPlane = Far;
		D3DXMatrixPerspectiveFovLH(&m_matProj, Fovy, Aspect, Near, Far);
		return m_matProj;
	}
	bool Update(float lX, float lY, float lZ, float Radius)
	{
		D3DXMATRIX matRot, matRotX, matRotY, matRotZ;
		D3DXMatrixRotationYawPitchRoll(&matRot, lX,lY,lZ);

		D3DXMatrixRotationX(&matRotX, lX);
		D3DXMatrixRotationY(&matRotY, lY);
		D3DXMatrixRotationZ(&matRotZ, lZ);
		matRot = matRotY * matRotX * matRotZ;
		matRot._41 = m_vCameraPos.x;
		matRot._42 = m_vCameraPos.y;
		matRot._43 = m_vCameraPos.z;
		D3DXMatrixInverse(&m_matView, NULL, &matRot);

		m_vLook.x = m_matView._13;
		m_vLook.y = m_matView._23;
		m_vLook.z = m_matView._33;
		m_vRight.x = m_matView._11;
		m_vRight.y = m_matView._21;
		m_vRight.z = m_matView._31;
		m_vUp.x = m_matView._12;
		m_vUp.y = m_matView._22;
		m_vUp.z = m_matView._32;
		return true;
	}
	bool Frame()
	{
		if (I_InputDx.m_MouseState.rgbButtons[0])
		{
			m_fYaw += D3DXToRadian(I_InputDx.m_MouseState.lX * 0.1f);
			m_fPitch += D3DXToRadian(I_InputDx.m_MouseState.lY * 0.1f);
		}
		m_fRadius = 0.0f;
		if (I_InputDx.m_MouseState.lZ != 0)
		{
			m_fRadius = I_InputDx.m_MouseState.lZ * g_fSecPerFrame;
		}

		if (I_InputDx.IsKeyDown(DIK_SPACE))
		{
			m_fSpeed += g_fSecPerFrame * 3.0f;
		}
		m_fSpeed -= g_fSecPerFrame * 2.0f;
		if (m_fSpeed < 1.0f)
		{
			m_fSpeed = 1.0f;
		}
		if (I_InputDx.IsKeyDown(DIK_W))
		{
			m_vCameraPos += m_vLook * g_fSecPerFrame * m_fSpeed;
		}
		if (I_InputDx.IsKeyDown(DIK_S))
		{
			m_vCameraPos -= m_vLook * g_fSecPerFrame* m_fSpeed;
		}
		if (I_InputDx.IsKeyDown(DIK_A))
		{
			m_vCameraPos += m_vRight * g_fSecPerFrame* m_fSpeed;
		}
		if (I_InputDx.IsKeyDown(DIK_D))
		{
			m_vCameraPos -= m_vRight * g_fSecPerFrame* m_fSpeed;
		}
		if (I_InputDx.IsKeyDown(DIK_Q))
		{
			m_vCameraPos += m_vUp * g_fSecPerFrame* m_fSpeed;
		}
		if (I_InputDx.IsKeyDown(DIK_E))
		{
			m_vCameraPos -= m_vUp * g_fSecPerFrame* m_fSpeed;
		}

		Update(m_fPitch, m_fYaw, 0.0f, m_fRadius);
		_stprintf_s(m_szCameraPos, L"CameraPos(%f,%f,%f)", m_vCameraPos.x, m_vCameraPos.y, m_vCameraPos.z);
		return true;
	}
public:
	SampleCamera()
	{
		m_fYaw = 0.0f;
		m_fPitch = 0.0f;
		m_fRoll = 0.0f;
		m_fSpeed = 3.0f;
	}
	virtual ~SampleCamera()
	{

	}
};

class Sample : public JCore
{
public:
	JDxObject obj;
	VSCB      m_cbData;
	D3DXMATRIX					m_matWorld[4];
	SampleCamera   camera;

public:
	bool Init()
	{
		SimpleVertex vertices[] =
		{
			{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR4(0.4f, 1.0f, 5.0f, 1.0f) },
			{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR4(0.7f, 0.5f, 1.0f, 1.0f) },
			{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR4(0.5f, 1.0f, 0.5f, 1.0f) },
			{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f) },
			{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 1.0f, 1.0f) },
			{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR4(0.5f, 1.0f, 0.5f, 1.0f) },
			{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR4(0.5f, 1.0f, 0.5f, 1.0f) },
			{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR4(1.0f, 0.6f, 0.5f, 1.0f) },
		};
		obj.m_iVertexNum = sizeof(vertices) / sizeof(vertices[0]);
		obj.m_iVertexSize = sizeof(SimpleVertex);

		DWORD indices[] =
		{
			3,1,0,        2,1,3,        0,5,4,        1,5,0,

			3,4,7,        0,4,3,        1,6,5,        2,6,1,

			2,7,6,        3,7,2,        6,4,5,        7,4,6,
		};
		obj.m_iIndexNum = sizeof(indices) / sizeof(indices[0]);
		obj.m_iIndexSize = sizeof(DWORD);

		obj.m_pVertexBuffer = CreateVertexBuffer(GetDevice(), vertices, obj.m_iVertexSize, obj.m_iVertexNum);
		obj.m_pIndexBuffer = CreateIndexBuffer(GetDevice(), indices, obj.m_iIndexSize, obj.m_iIndexNum);
		obj.m_pConstantBuffer = CreateConstantBuffer(GetDevice(), &m_cbData, sizeof(VSCB), 1);
		obj.m_pVS = DX::LoadVertexShader(GetDevice(), L"Sample.hlsl", &obj.m_BlobVS);
		obj.m_pPS = DX::LoadPixelShader(GetDevice(), L"Sample.hlsl", &obj.m_BlobPS);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		int ElementCnt = sizeof(ied) / sizeof(ied[0]);
		obj.m_pIL = DX::CreateLayout(GetDevice(), ied, ElementCnt, obj.m_BlobVS));

		//===========================================================================
		//=================================Camera====================================
		//===========================================================================
		D3DXVECTOR3 vPos = D3DXVECTOR3(0, 5.0f, -20.0f);
		D3DXVECTOR3 vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		camera.SetViewMatrix(vPos, vAt, vUp);
		camera.SetProjMatrix(D3DX_PI* 0.25f,
			(float)g_rtClient.right / (float)g_rtClient.bottom,
			1.0f, 100.0f);
		camera.SetViewMatrix(D3DXVECTOR3(0.0f, 5.0f, -20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		camera.SetProjMatrix((float)D3DX_PI * 0.25f, g_rtClient.right / (FLOAT)g_rtClient.bottom, 1.0f, 100.0f);
		return true;
	}
	bool Frame()
	{
		D3DXMATRIX mSpin;
		D3DXMATRIX mScale;
		D3DXMATRIX mTranslate;

		D3DXMatrixIdentity(&mSpin);
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixIdentity(&mTranslate);

		D3DXMatrixIdentity(&m_matWorld[0]);
		D3DXMatrixRotationY(&mSpin, I_Timer.m_fGameTimer*D3DX_PI);
		//m_matWorld[0] = mSpin * mScale * mTranslate;
		//D3DXMatrixTranslation(&mTranslate, 1.0f, 0.0f, 0.0f);
		//D3DXMatrixScaling(&mScale, 1.0f, 0.1f, 0.1f);

		//m_matWorld[1] = mSpin * mScale * mTranslate;

		//D3DXMatrixTranslation(&mTranslate, 0.0f, 1.0f, 0.0f);
		//D3DXMatrixScaling(&mScale, 0.1f, 1.0f, 0.1f);
		//m_matWorld[2] = mSpin * mScale * mTranslate;

		//D3DXMatrixTranslation(&mTranslate, 0.0f, 0.0f, 1.0f);
		//D3DXMatrixScaling(&mScale, 0.1f, 0.1f, 1.0f);
		//m_matWorld[3] = mSpin * mScale * mTranslate;

		//camera.Frame();
		D3DXMatrixTranspose(&m_cbData.matView, &camera.m_matView);
		D3DXMatrixTranspose(&m_cbData.matProj, &camera.m_matProj);
		D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld[0]);

		//m_matWorld[0] = (m_cbData.matWorld * m_cbData.matView) * m_cbData.matProj;
		return true;
	}
	bool Render()
	{
		GetContext()->UpdateSubresource(obj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
		obj.Render(GetContext());

		D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld[1]);
		GetContext()->UpdateSubresource(obj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
		obj.Render(GetContext());

		D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld[2]);
		GetContext()->UpdateSubresource(obj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
		obj.Render(GetContext());

		D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld[3]);
		GetContext()->UpdateSubresource(obj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
		obj.Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow)
{
	Sample core;
	if (core.SetWindow(hInstance, 800, 600, L"DirectX Sample Box3D"))
	{
		core.Run();
		return 0;
	}
	return 1;
};
// YawPitchRoll ( Quaternion, Rotation )
// 세타 <-> Matrix <-> Quaternion(이동없음)