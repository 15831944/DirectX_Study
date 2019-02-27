#include "JCore.h"
#include "AseObject.h"
class Sample : public JCore
{
	AseObject obj;
public:
	bool Init()
	{
		//obj.Load(L"../../Data/box.ase");
		obj.Load(L"../../Data/st02sc00.ase");
		obj.Init();

		//TCHAR Ret[256] = { 0, };
		//wstring abc = L"stalfdj";
		//wsprintf(Ret, L"%s", abc.data());

		for (int iMtrl = 0; iMtrl < obj.m_Mtrl.size(); iMtrl++)
		{
			if (obj.m_Mtrl[iMtrl].subMtrl.size() > 0)
			{
				for (int iSubMtrl = 0; iSubMtrl < obj.m_Mtrl[iMtrl].subMtrl.size(); iSubMtrl++)
				{
					TCHAR Ret[256] = { 0, };
					wstring strTemp = mtow(obj.m_Mtrl[iMtrl].subMtrl[iSubMtrl].tex[0].strTexName);
					wsprintf(Ret, _T("%s"), strTemp.data());

					int iTex = I_TexMgr.Add(GetDevice(), Ret);
					obj.m_SubAseObj[iSubMtrl].m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTex);
				}
			}

			if (obj.m_Mtrl[iMtrl].tex.size() > 0)
			{
				for (int iTex = 0; iTex < obj.m_Mtrl[iMtrl].tex.size(); iTex++)
				{
					TCHAR Ret[256] = { 0, };
					wstring strTemp = mtow(obj.m_Mtrl[iMtrl].tex[0].strTexName);
					wsprintf(Ret, _T("%s"), strTemp.data());
					
					int iTexture = I_TexMgr.Add(GetDevice(), Ret);
					obj.m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTexture);
				}
			}
		}

		//int iTex = I_TexMgr.Add(GetDevice(), Ret);
		//obj.m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTex);
		
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		for (int iMtrl = 0; iMtrl < obj.m_Mtrl.size(); iMtrl++)
		{
			if (obj.m_Mtrl[iMtrl].subMtrl.size() > 0)
			{
				for (int iSubMtrl = 0; iSubMtrl < obj.m_Mtrl[iMtrl].subMtrl.size(); iSubMtrl++)
				{
					obj.m_SubAseObj[iSubMtrl].SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
				}
			}
			else
			{
				obj.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
			}
		}
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