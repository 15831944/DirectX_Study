
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "GameTools.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기
//if(dlg.GetSafeHwnd() == NULL)
//{	dlg.Create(); }
// 체크버튼 -> InInitDialog(재정의) :: 초기화작업
// m_bAlphaBlend = TURE -> UpdateData(FALSE); // updatedata(TRUE) -> 변수가바뀜(컨트롤의 이벤트 발생 -> 변수 업데이트)
// Ctrl + D -> Dialog Number
/* 패인윈도우 -> 오피스 or 비주얼스튜디오 (스타일) */
/*
	mainframe :: TabbedPane->Create(_T(""), this, CRect(0,0,250,250),TRUE, -1, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLE, WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI);// 선생님샘플 ㄱㄱ
	MFC클래스 추가 MapPane -> 기본클래스 CDockablePane <- 탈부탁가능
					Effectpane ->       "
	mainframe -> mappane, effectpane 연결 (객체생성)
	mappane->Createex(), effectpane->Createex();
	mappane.enabledocking(CBRS_ALIGN_ANY); effectpane.enabledocking(CBRS_ALIGN_ANY);  :: CBRS_ALIGN_ANY-> ANY는 상하좌우 다 붙일수있음 right,left같은거로바꾸면 그곳에만 부착가능
	Dockpane(&mappane); Dockpane(&effectpane); :: 여기서 도킹함
	taabbedpane->addtab(mappane); taabbedpane->addtab(effectpane);
	taabedpane.enabledocking(CBRS_ALIGN_ANY);
	Dockpane(taabedpane); -> mappane이랑 effectpane 연결된 탭도 도킹되야함

	///////////////////////////////////////////리프레시 작업///////////////////////////////////////////
	mappane, effectpane ->  메세지 -> WM_CREATE 재정의 // 초기화작업
							메세지 -> WM_SIZE  재정의 // 
							메세지 -> WM_MOUSEACTIVATE  재정의 // 패인윈도우의 마우스 포커스가 맞앗을때 
	dialog 하나생성(속성) -> title bar -> false, style -> child
	dialog-> 클래스추가(MFC X) : mapform(name) -> CFormView상속
	mapform -> static MapForm* CreateOne(CWnd* pParent) // 생성자 매개변수없이
	{
		MapForm* form = new MapForm;
		form->Create(NULL,NULL,WS_CHILD | WS_VISIBLE, SRect(0,0,500,500),pParent,0,NULL);
		return form;
	}
	mappane class -> mapform* 객체생성 effectpane class -> effectform* 객체생성
	mappain class -> OnCreate -> m_form = mapform::createone();
					 OnSize ->
					 if(m_form)
					 {
						m_form->SetWindowPos(NULL,0,0,cx,cy,SWP_NOZORDER); //패인윈도우가 바뀌면 dialog도 같이움직인다.
					 }
					 OnMouseActivate -> cframewnd* pParentframe = getparentframe(); // 이 form 저 form 클릭하다보면 부모를 잃을때도있다.
					 if(pparentframe == pdesktopwnd || pdesktopwnd->ischild(pParentframe))
					 {
						return CDockablePane::OnMouseActivate(~~~);
					 }
					 return  MA_NOACTIVATE;
/////////////////////////////////////////////////////////////////////////////////////////////////////
1) dialog 생성 -> style, titlebar 수정 -> 클래스추가
2) MFC클래스생성 -> CDockablepane -> OnCreate, OnSize, OnMouseActivate 재정의
	pane, form 같이 따라다님
*/