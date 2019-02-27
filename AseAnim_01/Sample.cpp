#include "JCore.h"
#include "AseObject.h"
/*
	디버그 -> 그래픽 -> 그래픽디버그시작
*/
class Sample : public JCore
{
	AseObject box;
	D3DXMATRIX matWorld;
	D3DXMATRIX matPos;
	D3DXMATRIX matRot;
public:
	bool Init()
	{
		//box.Load(GetDevice(), L"../../data/scaleanimationmodel.ase"); 
		box.Load(GetDevice(), L"../../data/Turret_Deploy.ase"); 
		box.Init();
		return true;
	}
	bool Frame()
	{
		box.Frame();
		return true;
	}
	bool Render()
	{
		box.Draw(GetContext(), NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		TCHAR buf[256] = { 0, };
		_stprintf_s(buf, L"%f", box.m_fCurrentTick);
		I_Write.Draw(buf, 15, { 0,150,800,600 });
		return true;
	}
	bool Release()
	{
		box.Release();
		return true;
	}
};
RUN;