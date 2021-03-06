// UI_Pane.cpp: 구현 파일
//

#include "stdafx.h"
#include "SampleUI.h"
#include "UI_Pane.h"


// UI_Pane

IMPLEMENT_DYNAMIC(UI_Pane, CDockablePane)

UI_Pane::UI_Pane()
{

}

UI_Pane::~UI_Pane()
{
}


BEGIN_MESSAGE_MAP(UI_Pane, CDockablePane)
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// UI_Pane 메시지 처리기




void UI_Pane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if (m_pUIForm)
	{
		m_pUIForm->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


int UI_Pane::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFrameWnd* pParentFrame = GetParentFrame();
	if (pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	return MA_NOACTIVATE;
}


int UI_Pane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	this->m_pUIForm = UI_Form::CreateOne(this);
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}