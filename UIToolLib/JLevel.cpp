#include "JLevel.h"
namespace UI
{
	JPanel& JLevel::find_child(wstring findname)
	{
		for (int iC = 0; iC < m_pChildList.size(); iC++)
		{
			if (m_pChildList[iC]->m_NodeName == findname)
			{
				return *m_pChildList[iC];
			}
		}
		JPanel* pNull = new JPanel(L"nullptr");
		return *pNull;
	}
	void JLevel::push_child(JPanel& pChild)
	{
		//pChild->m_pParent = this;
		//pChild->m_ParentName = this->m_NodeName;
		m_pChildList.push_back(&pChild);
	}
	bool JLevel::Init()
	{
		return true;
	}
	bool JLevel::Frame()
	{
		for (int iC = 0; iC < m_pChildList.size(); iC++)
		{
			//m_pChildList[iC]->Frame();
		}
		return true;
	}
	bool JLevel::Render(ID3D11DeviceContext* pContext)
	{
		for (int iC = 0; iC < m_pChildList.size(); iC++)
		{
			m_pChildList[iC]->Render(pContext);
		}
		return true;
	}
	bool JLevel::Release()
	{
		for (int iC = 0; iC < m_pChildList.size(); iC++)
		{
			m_pChildList[iC]->Release();
		}
		return true;
	}

	JLevel::JLevel(wstring NodeName)
	{
		m_NodeName = NodeName;
	}


	JLevel::~JLevel()
	{
	}
}