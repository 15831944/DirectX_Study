#pragma once
#include "UserInterface.h"
class CtrlUI : public UserInterface
{
public:
	UserInterface* GetChild(int iIndex);
	//UserInterface* GetParent(int iIndex);
	bool ChangedColor(ID3D11DeviceContext* context, D3DXVECTOR4 vColor);
	bool			Add(UserInterface* pUI);
	bool Frame();
	bool Render(ID3D11DeviceContext* context);
public:
	CtrlUI();
	virtual ~CtrlUI();
private:
	vector<UserInterface*> m_pUIList;
};

