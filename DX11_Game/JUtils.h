#pragma once
#include <WinSock2.h>	
#include <windows.h>
#include <windowsx.h>
#include <time.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
//#include <wrl.h>
#include <dinput.h>
//#include "JVector.h"
using namespace std;
//using namespace Microsoft::WRL;

typedef basic_string<TCHAR> T_STR;
typedef basic_string<wchar_t> W_STG;
typedef basic_string<char>  C_STR;
typedef vector<T_STR>		T_STR_VECTOR;
struct AnimTrack
{
	int iTick;
	D3DXQUATERNION qRot;
	D3DXVECTOR3    vPos;
	AnimTrack*		   PrevTrack;
	AnimTrack*		   NextTrack;

};
struct PNCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;
	PNCT_VERTEX()
	{

	}
	PNCT_VERTEX(D3DXVECTOR3 vp,	D3DXVECTOR3 vn,	D3DXVECTOR4 vc,	D3DXVECTOR2 vt)
	{
		p = vp;
		n = vn;
		c = vc;
		t = vt;
	}
};
struct ASE_SCENE
{
	int iFirstFrame;
	int iLastFrame;
	int iFrameSpeed;
	int iTickPerFrame;
};
struct ASE_TEXTURE
{
	int iType;
	string strTexName;
};
struct ASE_MATERIAL
{
	string strMtrlName;
	vector<ASE_TEXTURE> tex;
	vector<ASE_MATERIAL> subMtrl;
};
struct ASE_TRIANGLE
{
	PNCT_VERTEX v[3];
	DWORD dwSubID;
};
struct ASE_INDEX
{
	DWORD i[3];
	DWORD dwSubID;
};
struct ASE_FACENORMAL
{
	float fn[3];
	float vn[3][3];
};
struct ASE_GEOMETRY
{
	int							iGeomMtrlRef;
	string						strNodeName;
	string						strParentName;
	vector<PNCT_VERTEX>			VertexPosList;
	vector<ASE_INDEX>			IndexPosList;
	vector<PNCT_VERTEX>			VertexColList;
	vector<ASE_INDEX>			IndexColList;
	vector<PNCT_VERTEX>			VertexTexList;
	vector<ASE_INDEX>			IndexTexList;
	vector<ASE_TRIANGLE>		TriangleList;
	vector<ASE_FACENORMAL>		TriNormalList;
	D3DXMATRIX					m_matWorld;
	DWORD						m_dwFaceSize;
	vector<AnimTrack*>			m_pTransTrack;
	vector<AnimTrack*>			m_pRotateTrack;
	vector<AnimTrack*>			m_pScaleTrack;
};
struct SimpleVertex
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
};

struct PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
};

struct VSCB
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;
};

struct fRECT
{
public:
	float left;
	float top;
	float right;
	float bottom;
	fRECT& operator +=(float a)
	{
		left += a;
		top += a;
		right += a;
		bottom += a;
		return *this;
	}
};
struct Vector2
{
	float x, y;
	Vector2(float fx, float fy)
	{
		x = fx; y = fy;
	}
	Vector2() {}
};
struct Vector3
{
	float x, y, z;
	Vector3(float fx, float fy, float fz)
	{
		x = fx; y = fy; z = fz;
	}
	Vector3() {}
};
struct Vector4
{
	float x, y, z, w;
	Vector4(float fx, float fy, float fz, float fw)
	{
		x = fx; y = fy; z = fz; w = fw;
	}
	Vector4() {}
};
struct JVertex
{
	Vector3 Pos;
	Vector2 Tex;
	Vector4 Col;
};
struct fPOINT
{
	float x;
	float y;
};
template<class T>
class JSingleton
{
public:
	static T& GetInstance()
	{
		static T SingleInstance;
		return SingleInstance;
	}
};
class JBasis
{
public:
	virtual bool Init()
	{
		return true;
	}
	virtual bool Frame()
	{
		return true;
	}
	virtual bool Render()
	{
		return true;
	}
	virtual bool Release()
	{
		return true;
	}
};
static TCHAR* NameDivide(const TCHAR* pszFileName)
{
	TCHAR szFileName[MAX_PATH] = { 0, };
	TCHAR Dirve[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR FileName[MAX_PATH] = { 0, };
	TCHAR FileExt[MAX_PATH] = { 0, };
	if (pszFileName != NULL)
	{
		_tsplitpath_s(pszFileName, Dirve, Dir, FileName, FileExt);
		_stprintf_s(szFileName, _T("%s%s"), FileName, FileExt);
	}
	return szFileName;
}
static char* NameDivide(const char* pszFileName)
{
	char szFileName[MAX_PATH] = { 0, };
	char Dirve[MAX_PATH] = { 0, };
	char Dir[MAX_PATH] = { 0, };
	char FileName[MAX_PATH] = { 0, };
	char FileExt[MAX_PATH] = { 0, };
	if (pszFileName != NULL)
	{
		_splitpath_s(pszFileName, Dirve, Dir, FileName, FileExt);
		printf_s(szFileName, _T("%s%s"), FileName, FileExt);
	}
	return szFileName;
}
static std::wstring mtow(std::string str)
{
	// 멀티바이트 -> 유니코드
	std::wstring ret = std::wstring(str.begin(), str.end());
	return ret;
}
static bool RectInRect(RECT rtDesk, RECT rtSrc)
{
	POINT  cDesk, cSrc, Radius, DeskRadius, SrcRadius;
	cDesk.x = (rtDesk.left + rtDesk.right) / 2;
	cDesk.y = (rtDesk.top + rtDesk.bottom) / 2;
	cSrc.x = (rtSrc.left + rtSrc.right) / 2;
	cSrc.y = (rtSrc.top + rtSrc.bottom) / 2;
	Radius.x = abs(cDesk.x - cSrc.x);
	Radius.y = abs(cDesk.y - cSrc.y);
	DeskRadius.x = (rtDesk.right - rtDesk.left) / 2;
	DeskRadius.y = (rtDesk.bottom - rtDesk.top) / 2;
	SrcRadius.x = (rtSrc.right - rtSrc.left) / 2;
	SrcRadius.y = (rtSrc.bottom - rtSrc.top) / 2;
	if (Radius.x <= (DeskRadius.x + SrcRadius.x) &&
		Radius.y <= (DeskRadius.y + SrcRadius.y))
	{
		return true;
	}
	return false;
}
static bool RectInRect(fRECT rtDesk, fRECT rtSrc)
{
	fRECT rtdesk = rtDesk; fRECT rtsrc = rtSrc;
	rtdesk += 1.0f; rtsrc += 1.0f;
	fPOINT  cDesk, cSrc, Radius, DeskRadius, SrcRadius;
	cDesk.x = (rtdesk.left + rtdesk.right) / 2;
	cDesk.y = (rtdesk.top + rtdesk.bottom) / 2;
	cSrc.x = (rtsrc.left + rtsrc.right) / 2;
	cSrc.y = (rtsrc.top + rtsrc.bottom) / 2;
	Radius.x = abs(cDesk.x - cSrc.x);
	Radius.y = abs(cDesk.y - cSrc.y);
	DeskRadius.x = (rtdesk.right - rtdesk.left) / 2;
	DeskRadius.y = (rtdesk.bottom - rtdesk.top) / 2;
	SrcRadius.x = (rtsrc.right - rtsrc.left) / 2;
	SrcRadius.y = (rtsrc.bottom - rtsrc.top) / 2;
	if (Radius.x <= (DeskRadius.x + SrcRadius.x) &&
		Radius.y <= (DeskRadius.y + SrcRadius.y))
	{
		return true;
	}
	return false;
}
static bool DxRectInRect(fRECT rtDesk, fRECT rtSrc)
{
	fRECT rtdesk = rtDesk; fRECT rtsrc = rtSrc;
	fPOINT  cDesk, cSrc, Radius;
	cDesk.x = rtdesk.left + (rtdesk.right - rtdesk.left) / 2;
	cDesk.y = rtdesk.top + (rtdesk.bottom - rtdesk.top) / 2;
	cSrc.x = rtsrc.left + (rtsrc.right - rtsrc.left) / 2;
	cSrc.y = rtsrc.top + (rtsrc.bottom - rtsrc.top) / 2;
	//float fX = cDesk.x - cSrc.x;
	Radius.x = abs(cDesk.x - cSrc.x);
	Radius.y = abs(cDesk.y - cSrc.y);
	if (Radius.x <= 40.0f)
	{
		return true;
	}
	return false;
	//DeskRadius.x = (rtdesk.right - rtdesk.left) / 2;
	//DeskRadius.y = (rtdesk.bottom - rtdesk.top) / 2;
	//SrcRadius.x = (rtsrc.right - rtsrc.left) / 2;
	//SrcRadius.y = (rtsrc.bottom - rtsrc.top) / 2;
	//if (Radius.x <= (DeskRadius.x + SrcRadius.x) &&
	//	Radius.y <= (DeskRadius.y + SrcRadius.y))
	//{
	//	return true;
	//}
	//return false;
}
static bool RectInPt(RECT rt, POINT pt)
{
	if (rt.left <= pt.x && rt.right >= pt.x)
	{
		if (rt.top <= pt.y && rt.bottom >= pt.y)
		{
			return true;
		}
	}
	return false;
}
static bool RectInPt(fRECT rt, POINT pt)
{
	fRECT temp;
	temp.left = rt.left;
	temp.top = rt.top;
	temp.right = rt.left + rt.right;
	temp.bottom = rt.top + rt.bottom;
	if (temp.left <= pt.x && temp.right >= pt.x)
	{
		if (temp.top <= pt.y && temp.bottom >= pt.y)
		{
			return true;
		}
	}
	return false;
}
class JUtils
{
public:
	JUtils();
	virtual ~JUtils();
};