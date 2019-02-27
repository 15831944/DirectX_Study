#include "stdafx.h"
#include "CtrlUI.h"
bool CtrlUI::Add(UserInterface* pUI)
{
	if (pUI == NULL) return false;
	m_pUIList.push_back(pUI);
	return true;
}
UserInterface* CtrlUI::GetChild(int iIndex)
{
	return NULL;
}
bool CtrlUI::ChangedColor(ID3D11DeviceContext* context, D3DXVECTOR4 vColor)
{
	for (int iUI = 0; iUI < m_pUIList.size(); iUI++)
	{
		for (int iVer = 0; iVer < m_pUIList[iUI]->m_pVertices.size(); iVer++)
		{
			m_pUIList[iUI]->m_pVertices[iVer].c = vColor;
		}
		context->UpdateSubresource(m_pUIList[iUI]->m_dxObj.m_pVertexBuffer, 0, NULL, &m_pUIList[iUI]->m_pVertices.at(0), 0, 0);
	}
	return true;
}
bool CtrlUI::Frame()
{
	for (int iUI = 0; iUI < m_pUIList.size(); iUI++)
	{
		m_pUIList[iUI]->Frame();
	}
	return true;
}
bool CtrlUI::Render(ID3D11DeviceContext* context)
{
	for (int iUI = 0; iUI < m_pUIList.size(); iUI++)
	{
		m_pUIList[iUI]->Render(context);
	}
	return true;
}

CtrlUI::CtrlUI()
{
}


CtrlUI::~CtrlUI()
{
}
