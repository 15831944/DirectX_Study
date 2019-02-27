#include "JCore.h"
#include "AseObject.h"
class Sample : public JCore
{
	AseObject obj;
	D3DXMATRIX matWorld;
public:
	bool Init()
	{
		obj.Init();
		//obj.Load(GetDevice(), L"../../Data/box.ase");
		//obj.Load(GetDevice(), L"../../Data/box2.ase");
		obj.Load(GetDevice(), L"Turret_Deploy.ase");
		D3DXMatrixIdentity(&matWorld);
		return true;
	}
	bool Frame()
	{
		float fTime = I_Timer.m_fGameTimer * 3.141592;
		D3DXMatrixTranslation(&matWorld, 0, 0, -fTime * 3.141592);
		return true;
	}
	bool Render()
	{
		obj.SetMatrix(&matWorld, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		obj.Render(GetContext());
		return true;
	}
	bool Release()
	{
		obj.Release();
		return true;
	}
};
RUN;