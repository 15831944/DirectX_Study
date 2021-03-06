#pragma once
#include "JGameTools.h"

// MapForm 대화 상자

class MapForm : public CFormView, public JSingleton<MapForm>
{
	DECLARE_DYNAMIC(MapForm)

public:
	MapForm();   // 표준 생성자입니다.
	virtual ~MapForm();
	static MapForm* CreateOne(CWnd* pParent);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddplane();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit2();
	CString m_strTexName;
	CString m_strTemp;
	CString m_strLeft;
	afx_msg void OnCurrentPlaneRectLeft();
	afx_msg void OnCurrentPlaneRectRight();
	afx_msg void OnCurrentPlaneRectTop();
	afx_msg void OnCurrentPlaneRectBottom();
	afx_msg void OnEnUpdateRtLeft();
	afx_msg void OnEnChangeMfceditbrowse1();
	CEdit m_EditLeft;
	CString m_LeftString;
	afx_msg void OnLbnSelchangeList1();
	CListBox m_CtrlList;
};
#define I_UI MapForm::GetInstance()