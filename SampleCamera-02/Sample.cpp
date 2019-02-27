#include "JCore.h"
#include "JShape.h"
class Sample : public JCore
{
public:
	JShape* m_Shape;
	D3DXMATRIX m_matWorld;
public:
	bool Init()
	{
		m_Shape = new JBoxShape(CENTER);
		m_Shape->Init();
		return true;
	}
	bool Frame()
	{
		float fTime = I_Timer.m_fGameTimer * 3.141592f;
		D3DXMATRIX matTrans;
		D3DXMatrixTranslation(&m_matWorld, cos(fTime), 0, 0);
		return true;
	}
	bool Render()
	{
		m_Shape->SetMatrix(&m_matWorld, &m_Camera.m_matView, &m_Camera.m_matProj);
		m_Shape->Render(GetContext());
		return true;
	}
	bool Release()
	{
		m_Shape->Release();
		return true;
	}
};
RUN;