#include "JCore.h"
#include "JTextureMgr.h"
#include "JPlaneShape.h"
//==========================================================================
//===========================행렬결합 + Texture=============================
//==========================================================================
enum SRTO { S = 0, R,T,O};
class Sample : public JCore
{
public:
	JShape * m_ParentBox;
	JShape * m_ChildBox;
	JShape * m_LeafBox[3];
	JShape * m_Plane;
	D3DXMATRIX m_matWorld[6];
	D3DXMATRIX ParentSRTO[4];
	D3DXMATRIX ChildSRTO[4];
	D3DXMATRIX LeafSRTO[4];
	D3DXMATRIX Leaf2SRTO[4];
	D3DXMATRIX Leaf3SRTO[4];
public:
	bool Init()
	{
		m_ParentBox = new JBoxShape();
		m_ChildBox = new JBoxShape();
		m_LeafBox[0] = new JBoxShape();
		m_LeafBox[1] = new JBoxShape();
		m_LeafBox[2] = new JBoxShape();
		m_Plane = new JPlaneShape();
		int m_iTexture = I_TexMgr.Add(GetDevice(), L"../../data/Bitmap/BackGround.bmp");
		m_ParentBox->m_dxObj.m_pTexture = I_TexMgr.GetPtr(m_ParentBox->m_dxObj.m_iTexture);
		//m_ChildBox->m_dxObj.m_iTexture = I_TexMgr.Add(GetDevice(), L"../../data/Bitmap/BackGround.bmp");
		//m_ChildBox->m_dxObj.m_pTexture = I_TexMgr.GetPtr(m_ChildBox->m_dxObj.m_iTexture);
		//m_LeafBox[0]->m_dxObj.m_iTexture = I_TexMgr.Add(GetDevice(), L"../../data/Bitmap/BackGround.bmp");
		//m_LeafBox[0]->m_dxObj.m_pTexture = I_TexMgr.GetPtr(m_LeafBox[0]->m_dxObj.m_iTexture);
		//m_LeafBox[1]->m_dxObj.m_iTexture = I_TexMgr.Add(GetDevice(), L"../../data/Bitmap/BackGround.bmp");
		//m_LeafBox[1]->m_dxObj.m_pTexture = I_TexMgr.GetPtr(m_LeafBox[1]->m_dxObj.m_iTexture);
		//m_LeafBox[2]->m_dxObj.m_iTexture = I_TexMgr.Add(GetDevice(), L"../../data/Bitmap/BackGround.bmp");
		//m_LeafBox[2]->m_dxObj.m_pTexture = I_TexMgr.GetPtr(m_LeafBox[2]->m_dxObj.m_iTexture);

		m_ParentBox->Init();
		m_ChildBox->Init();
		m_LeafBox[0]->Init();
		m_LeafBox[1]->Init();
		m_LeafBox[2]->Init();
		m_Plane->Init();
		return true;
	}
	bool Frame()
	{
		float fTime = I_Timer.m_fGameTimer * D3DX_PI;
		D3DXMatrixScaling(&ParentSRTO[S], 1, 1, 1);
		D3DXMatrixRotationY(&ParentSRTO[R], 0);
		D3DXMatrixTranslation(&ParentSRTO[T], 0, 0, 0);
		m_matWorld[0] =
			ParentSRTO[S] *
			ParentSRTO[R] *
			ParentSRTO[T];

		D3DXMatrixScaling(&ChildSRTO[S], 0.5f, 0.5f, 0.5f);
		D3DXMatrixRotationY(&ChildSRTO[R], fTime * 1.2f);
		D3DXMatrixTranslation(&ChildSRTO[T], 2, 0, 0);
		m_matWorld[1] =
			ChildSRTO[S] *
			ChildSRTO[R] *
			ChildSRTO[T] *

			ParentSRTO[R] *
			ParentSRTO[T];

		D3DXMatrixScaling(&LeafSRTO[S], 0.25f, 0.25f, 0.25f);
		D3DXMatrixRotationY(&LeafSRTO[R], fTime * 1.4f);
		D3DXMatrixTranslation(&LeafSRTO[T], 1, 0, 0);
		m_matWorld[2] =
			LeafSRTO[S] *
			LeafSRTO[R] *
			LeafSRTO[T] *

			ChildSRTO[R] *
			ChildSRTO[T] *

			ParentSRTO[R] *
			ParentSRTO[T];

		D3DXMatrixScaling(&Leaf2SRTO[S], 0.125f, 0.125f, 0.125f);
		D3DXMatrixRotationY(&Leaf2SRTO[R], fTime * 1.6f);
		D3DXMatrixTranslation(&Leaf2SRTO[T], 1, 0, 0);
		m_matWorld[3] =
			Leaf2SRTO[S] *
			Leaf2SRTO[R] *
			Leaf2SRTO[T] *

			LeafSRTO[R] *
			LeafSRTO[T] *

			ChildSRTO[R] *
			ChildSRTO[T] *

			ParentSRTO[R] *
			ParentSRTO[T];

		D3DXMatrixScaling(&Leaf3SRTO[S], 0.125f / 2.0f, 0.125f / 2.0f, 0.125f / 2.0f);
		D3DXMatrixRotationY(&Leaf3SRTO[R], fTime * 1.8f);
		D3DXMatrixTranslation(&Leaf3SRTO[T], 1, 0, 0);
		m_matWorld[4] =
			Leaf3SRTO[S] *
			Leaf3SRTO[R] *
			Leaf3SRTO[T] *

			Leaf2SRTO[R] *
			Leaf2SRTO[T] *

			LeafSRTO[R] *
			LeafSRTO[T] *

			ChildSRTO[R] *
			ChildSRTO[T] *

			ParentSRTO[R] *
			ParentSRTO[T];

		D3DXMatrixScaling(&m_matWorld[5], 3, 3,3);
		return true;
	}

	bool Render()
	{
		// spin 자체회전 orbit 궤도회전
		//GetContext()->OMSetDepthStencilState(JState::g_pEnableDSS, 1);
		m_ParentBox->SetMatrix(&m_matWorld[0], GetView(), GetProj());
		m_ParentBox->Render(GetContext());

		m_ChildBox->SetMatrix(&m_matWorld[1], GetView(), GetProj());
		m_ChildBox->Render(GetContext());

		m_LeafBox[0]->SetMatrix(&m_matWorld[2], GetView(), GetProj());
		m_LeafBox[0]->Render(GetContext());

		m_LeafBox[1]->SetMatrix(&m_matWorld[3], GetView(), GetProj());
		m_LeafBox[1]->Render(GetContext());

		m_LeafBox[2]->SetMatrix(&m_matWorld[4], GetView(), GetProj());
		m_LeafBox[2]->Render(GetContext());
		//GetContext()->OMSetDepthStencilState(JState::g_pStencilA, 1);
		m_Plane->SetMatrix(&m_matWorld[5], GetView(), GetProj());
		m_Plane->Render(GetContext());

		return true;
	}
	bool Release()
	{
		m_ParentBox->Release();
		return true;
	}
};
RUN;