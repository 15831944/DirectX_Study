#pragma once
#include "JCore.h"
#include "JPlaneShape.h"
#include "JBoxShape.h"

struct PlaneUI
{
	JPlaneShape* m_Plane;
	JPlaneShape* m_ColLeft;
	JPlaneShape* m_ColRight;
	JPlaneShape* m_ColTop;
	JPlaneShape* m_ColBottom;
	PlaneUI()
	{
		m_Plane = new JPlaneShape;
		m_ColLeft = new JPlaneShape;
		m_ColRight = new JPlaneShape;
		m_ColTop = new JPlaneShape;
		m_ColBottom = new JPlaneShape;
	}
};
class MFCSample : public JCore
{
public:
	vector<PlaneUI*> m_PlaneList;
	PlaneUI* m_CurrentPlane;
	//D3DXMATRIX m_matWorld;
	float m_fZ;
	POINT m_MFCMouse;
	TCHAR MousePos[256];
	TCHAR temp[256];
	// debug
	JBoxShape box;
public:
	bool CreatePlane();
	bool UpdateRect(PlaneUI* Plane);
	POINT UpdatePt();
	bool SelectPlane();
	bool LoadTexture(CString szTexName);
	CString NameDivide(CString strName);
	bool SwapZ(D3DXMATRIX& desk);
	bool SwapLR(fRECT& rt);
	bool SwapTB(fRECT& rt);
	BOOL FindBiggerZ(D3DXMATRIX mat);
	BOOL CollisionCheck();
	bool fRectInRect(fRECT rtDesk, fRECT rtSrc);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	MFCSample();
	virtual ~MFCSample();
};

