#include "JCore.h"
#include "JDxHelper.h"
#include "JShape.h"

enum SRTO { S = 0, R, T };

class Sample : public JCore
{
public:
	JShape * m_ParentBox[2];
	JShape* m_ChildBox[2];
	JShape* m_LeafBox[2];


	D3DXMATRIX m_matWorld[6];
	D3DXMATRIX m_matParent1[3];
	D3DXMATRIX m_matParent2[3];
	D3DXMATRIX m_matChild[3];
	D3DXMATRIX m_matChild2[3];

	D3DXMATRIX m_matLeaf[3];
	D3DXMATRIX m_matLeaf2[3];

public:
	bool Init()
	{
		m_ParentBox[0] = new JBoxShape(LB);
		m_ParentBox[0]->Init();
		m_ParentBox[1] = new JBoxShape(LB);
		m_ParentBox[1]->Init();

		m_ChildBox[0] = new JBoxShape(LB);
		m_ChildBox[0]->Init();
		m_ChildBox[1] = new JBoxShape(LB);
		m_ChildBox[1]->Init();

		m_LeafBox[0] = new JBoxShape(LB);
		m_LeafBox[0]->Init();
		m_LeafBox[1] = new JBoxShape(LB);
		m_LeafBox[1]->Init();
		return true;
	}
	bool Frame()
	{
		float fTime =  I_Timer.m_fGameTimer * 2.0f;
		// left
		D3DXMatrixScaling(&m_matParent1[S], 1.0f, 0.25f, 0.25f);
		D3DXMatrixRotationY(&m_matParent1[R], fTime);
		D3DXMatrixTranslation(&m_matParent1[T], 0, 0, 0);
		m_matWorld[0] =
			m_matParent1[S] *
			m_matParent1[R] *
			m_matParent1[T];
		// right
		D3DXMatrixScaling(&m_matParent2[S], -1.0f, 0.25f, 0.25f);
		D3DXMatrixRotationY(&m_matParent2[R], fTime);
		D3DXMatrixTranslation(&m_matParent2[T], 0, 0, 0);
		m_matWorld[1] =
			m_matParent2[S] *
			m_matParent2[R] *
			m_matParent2[T];

		D3DXMatrixScaling(&m_matChild[S], -0.25f, 1.0f, 0.25f);
		D3DXMatrixRotationX(&m_matChild[R], fTime);
		D3DXMatrixTranslation(&m_matChild[T], 2, 0, 0);
		m_matWorld[2] =
			m_matChild[S] *
			m_matChild[R] *
			m_matChild[T] *
			m_matParent2[R] *
			m_matParent2[T];

		D3DXMatrixScaling(&m_matChild2[S], -0.25f, 1.0f, 0.25f);
		D3DXMatrixRotationX(&m_matChild2[R], -fTime);
		D3DXMatrixTranslation(&m_matChild2[T], -1.5f, 0, 0);
		m_matWorld[3] =
			m_matChild2[S] *
			m_matChild2[R] *
			m_matChild2[T] *
			m_matParent1[R] *
			m_matParent1[T];

		D3DXMatrixScaling(&m_matLeaf[S], 0.75f, 0.25f, 0.25f);
		D3DXMatrixRotationY(&m_matLeaf[R], fTime);
		D3DXMatrixTranslation(&m_matLeaf[T], 0, 1.5f, 0);
		m_matWorld[4] =
			m_matLeaf[S] *
			m_matLeaf[R] *
			m_matLeaf[T] *
			m_matChild2[R] *
			m_matChild2[T] *
			m_matParent1[R] *
			m_matParent1[T];

		D3DXMatrixScaling(&m_matLeaf2[S], -1.0f, 0.25f, 0.25f);
		D3DXMatrixRotationY(&m_matLeaf2[R], -fTime);
		D3DXMatrixTranslation(&m_matLeaf2[T], 0, 1.5f, 0);
		m_matWorld[5] =
			m_matLeaf2[S] *
			m_matLeaf2[R] *
			m_matLeaf2[T] *
			m_matChild[R] *
			m_matChild[T] *
			m_matParent2[R] *
			m_matParent2[T];
		return true;
	}
	bool Render()
	{
		m_ParentBox[0]->SetMatrix(&m_matWorld[0], &m_Camera.m_matView, &m_Camera.m_matProj);
		m_ParentBox[0]->Render(GetContext());

		GetContext()->RSSetState(JState::g_pRSFrontCullSolid);
		m_ParentBox[1]->SetMatrix(&m_matWorld[1], &m_Camera.m_matView, &m_Camera.m_matProj);
		m_ParentBox[1]->Render(GetContext());

		m_ChildBox[0]->SetMatrix(&m_matWorld[2], &m_Camera.m_matView, &m_Camera.m_matProj);
		m_ChildBox[0]->Render(GetContext());

		m_ChildBox[1]->SetMatrix(&m_matWorld[3], &m_Camera.m_matView, &m_Camera.m_matProj);
		m_ChildBox[1]->Render(GetContext());
		GetContext()->RSSetState(JState::g_pRSBackCullSolid);
		m_LeafBox[0]->SetMatrix(&m_matWorld[4], &m_Camera.m_matView, &m_Camera.m_matProj);
		m_LeafBox[0]->Render(GetContext());

		GetContext()->RSSetState(JState::g_pRSFrontCullSolid);
		m_LeafBox[1]->SetMatrix(&m_matWorld[5], &m_Camera.m_matView, &m_Camera.m_matProj);
		m_LeafBox[1]->Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;