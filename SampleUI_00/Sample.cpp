#include "JCore.h"
#include "JButton.h"
class Sample : public JCore
{
public:
	JButton btn;
public:
	bool Init()
	{
		btn.Create({0,0,1,1}, 0.2f,0.2f,0.2f,0.2f);
		int iTex = I_TexMgr.Add(GetDevice(), L"../../Data/popup_normal.png");
		btn.m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTex);
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		btn.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		btn.Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;