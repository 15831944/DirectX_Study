#pragma once


// InfoPane
#include "InfoForm.h"
class InfoPane : public CDockablePane
{
	DECLARE_DYNAMIC(InfoPane)
	InfoForm* m_pInfo;
public:
	InfoPane();
	virtual ~InfoPane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


