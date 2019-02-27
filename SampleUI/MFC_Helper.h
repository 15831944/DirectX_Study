#pragma once
class MFC_Helper
{
public:
	POINT m_ptMouse;
	TCHAR m_szMouse[256];
	TCHAR m_szRect[256];
public:
	bool fRectInPt(fRECT rt, POINT pt);
	CString PathDivide(CString strName);
public:
	MFC_Helper();
	virtual ~MFC_Helper();
};

