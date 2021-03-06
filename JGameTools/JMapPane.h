#pragma once
#include "MapForm.h"
// JMapPane

class JMapPane : public CDockablePane
{
	DECLARE_DYNAMIC(JMapPane)
public:
	JMapPane();
	virtual ~JMapPane();
	MapForm* m_wndForm;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


