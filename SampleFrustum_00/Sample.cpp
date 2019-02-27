#include "JCore.h"
//#include "HFrustum.h"
#include "DxRT.h"
#include "Plane.h"
#include "Minimap.h"
/*
	¹Ì´Ï¸Ê :: 42°­
	ÇÁ·¯½ºÅÒ :: 51°­
	ÄõµåÆ®¸®
	¿ÁÆ®¸®
*/


class Sample : public JCore
{
public:
	//HFrustum fru;
	JBoxShape Box;
	// ¹Ì´Ï¸Ê
	Minimap m_Minimap;
public:
	bool Init()
	{
		m_Camera[0].CreateFrustum(GetContext(),m_Camera[0].m_matView, m_Camera[0].m_matProj);
		Box.Init();
		// ¹Ì´Ï¸Ê
		m_Minimap.Create(GetDevice(),0, g_rtClient.bottom - 200, 200, 200);
		return true;
	}
	bool Frame()
	{	
		return true;// m_Minimap.Frame();
	}
	bool Render()
	{
		//Minimap Render
		if (m_Minimap.BeginRender(GetContext(), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1)))
		{
			Box.SetMatrix(NULL, &m_Minimap.m_matView, &m_Minimap.m_matProj);
			Box.Render(GetContext());

			m_Camera[0].SetMatrix(&m_Camera[0].m_matWorld, &m_Minimap.m_matView, &m_Minimap.m_matProj);
			m_Camera[0].Render(GetContext());

			m_Minimap.EndRender(GetContext());
		}
		Box.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		Box.Render(GetContext());

		m_Minimap.Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;