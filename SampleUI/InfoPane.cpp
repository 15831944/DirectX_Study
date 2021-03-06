// InfoPane.cpp: 구현 파일
//

#include "stdafx.h"
#include "SampleUI.h"
#include "InfoPane.h"


// InfoPane

IMPLEMENT_DYNAMIC(InfoPane, CDockablePane)

InfoPane::InfoPane()
{

}

InfoPane::~InfoPane()
{
}


BEGIN_MESSAGE_MAP(InfoPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// InfoPane 메시지 처리기

void InfoPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if (m_pInfo)
	{
		m_pInfo->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

int InfoPane::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFrameWnd* pParentFrame = GetParentFrame();
	if (pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	return MA_NOACTIVATE;
}


int InfoPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	this->m_pInfo = InfoForm::CreateOne(this);
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}