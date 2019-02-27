#include "stdafx.h"
#include "MFC_Helper.h"

CString MFC_Helper::PathDivide(CString strName)
{
	CString retStr;
	TCHAR RetData[MAX_PATH] = { 0, };
	TCHAR Drive[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR FileName[MAX_PATH] = { 0, };
	TCHAR Ext[MAX_PATH] = { 0, };
	_tsplitpath_s(strName, Drive, Dir, FileName, Ext);
	retStr = FileName;
	retStr += Ext;
	if (m_pCurrentPlane)
	{
		m_pCurrentPlane->m_strTexName = retStr;
		LoadTexture(strName);
	}
	else
	{
		AfxMessageBox(L"Plane이 하나도 없네요.");
	}
	return retStr;
}
MFC_Helper::MFC_Helper()
{
}


MFC_Helper::~MFC_Helper()
{
}
