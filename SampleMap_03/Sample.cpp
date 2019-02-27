#include "JCore.h"
#include "JMap.h"

class Sample : public JCore
{
public:
	JMap map;
public:
	bool Init()
	{
		map.SetHeightTexture(GetContext(), L"../../data/Map512.png");
		map.Create(GetDevice(), map.m_iWidth, map.m_iHeight, 1);
		//int m_iTexture = I_TexMgr.Add(GetDevice(), L"../../data/Castle.jpg");
		//map.m_pTexture = I_TexMgr.GetPtr(m_iTexture);
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		map.Render(GetContext());
		return true;
	}
	bool Release()
	{
		map.Release();
		return true;
	}
};
RUN;