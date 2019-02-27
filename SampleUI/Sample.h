#pragma once
#include "JCore.h"
#include "CtrlUI.h"
#include "ImageCtrl.h"
#include "SpriteCtrl.h"
/*
	Q, E, SpaceBar  :: Rotation
	W, S, A, D		:: Scaling
	MouseClick		:: Transition
*/
/*
	x1. Plane Create -> Mouse Clicked :: CurrentPlane이 선택되었다는 것을 알려주기
	x2. S, R, T
	3. TexList 가질수있는 구조
	4. Sprite :: Second -> SpriteMgr? TexMgr?
	x5. Plane이 뒤집어졌을때 LRBT 교체 작업
	6. Plane.Pos, Plane.Pos - 10 (정도) 가지고 충돌처리 해보기 -> Pos 를 2개가지고있으면될듯
	   Composite(디자인패턴), 2D, 3D, particle, sprite, Info :: (Pane)
	   빌보드 :: Inv( matView :: _41 = 0, _42 = 0, _43 = 0 ) :: 회전( + 스케일 ?)만 남음
*/
/*
	1. Parent Name 중복제거
	2. Sprite bool bPlay, Loop, State ...
	3. 
*/
class Sample : public JCore
{
public:
	vector<UserInterface*>	m_pPlaneList;
	vector<UserInterface*>	m_pSelectList;
	UserInterface*			m_pCurrentPlane;
public:
	RECT				m_rtClientSize;
public:
	bool				CreateSprite(D3DXMATRIX Scl, D3DXMATRIX Rot, D3DXMATRIX Trans, const TCHAR* szNodeName, const TCHAR* szParentName);
	bool				CreatePlane(D3DXMATRIX Scl, D3DXMATRIX Rot, D3DXMATRIX Trans, const TCHAR* szNodeName, const TCHAR* szParentName);
	bool				UpdateMouse();
	bool				ClickedFindCurrentPlane();
	UserInterface*		FindBigZValuePlane(UserInterface* pSrc, UserInterface* pDesk);
	UserInterface*		FindParent(const TCHAR* szString);
public:
	bool				Transition();
	bool				Rotation();
	bool				Scaling();
	bool				ChangeCurrentPlane(UserInterface* pPlane);
public:
	/* Helper */
	POINT				m_ptMouse;
	TCHAR				m_szMouse[256];
	TCHAR				m_szRect[256];
	TCHAR				m_Client[256];
public:
	bool				SetWindows(LONG Width, LONG Height);
	bool				fRectInPt(fRECT rt, POINT pt);
	CString				PathDivide(CString strName);
	bool				LoadSingleTexture(CString szTexName);
	bool				LoadMultyTexture(CString szTexName);
	bool				DeleteTexture(CString szTexName);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	Sample();
	virtual ~Sample();
};