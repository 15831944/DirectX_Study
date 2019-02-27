#include "JCore.h"
#include "JPlaneShape.h"
class Sample : public JCore
{
public:
	JPlaneShape plane;
public:
	bool Init()
	{
		plane.Init();
		plane.Create();
		plane.SetTexture(L"../../Data/snow.png");
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		float fTime = I_Timer.m_fGameTimer;
		D3DXMATRIX world, trans, scl, rot;
		D3DXMatrixRotationZ(&rot, cos(fTime));
		D3DXMatrixScaling(&scl, 10, 10, 1);

		world = scl * rot;
		world._41 = cos(fTime);
		plane.SetMatrix(&world, GetView(), GetProj());
		plane.Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;