#pragma once

// InfoForm 대화 상자

class InfoForm : public CFormView
{
	DECLARE_DYNAMIC(InfoForm)
public:
	static InfoForm* CreateOne(CWnd* pParent);
public:
	InfoForm(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InfoForm();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Info };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_NodeName;
	afx_msg void OnBnClickedGetinfo();
	CListBox m_CtrlTextureList;
//	virtual void OnActivateFrame(UINT nState, CFrameWnd* pDeactivateFrame);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
};
