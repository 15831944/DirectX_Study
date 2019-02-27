#include "JCore.h"
#include "AseObject.h"
class Sample : public JCore
{
public:
	AseObject Box;
public:
	bool Init()
	{
		Box.AseLoad(L"../../Data/Box.ase");
		Box.Init();

		TCHAR temp[256] = { 0, };
		for (int i = 0; i < Box.m_MaterialList[0].m_Texture.m_TextureName.size(); i++)
		{
			temp[i] = Box.m_MaterialList[0].m_Texture.m_TextureName[i];
		}

		int iTex = I_TexMgr.Add(g_pd3dDevice, temp);
		Box.m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTex);
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		Box.SetMatrix(&Box.m_matWorld, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		Box.Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;