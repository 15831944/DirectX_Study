#pragma once
#include <windows.h>
#include "resource.h"
#include <tchar.h>
#include <vector>
#include <map>
/* ===== 3dxMax ===== */
#include <istdplug.h>
#include <iparamb2.h>
#include <iparamm2.h>
#include <maxtypes.h>
#include <utilapi.h>
#include <max.h>
#include <stdmat.h>
#include <decomp.h>
#include <cs/bipexp.h>
#include <cs/phyexp.h>
#include <iskin.h>
/* ================== */
using namespace std;
/* ===== Utility ===== */
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
class HAnimTrack
{
	int		iType;
	int		iTick;
	Quat	q;
	Point3	v;
};
struct HScene
{
	int iFirstFrame;
	int iLastFrame;
	int iFrameSpeed;
	int iTickPerFrame;
};
struct HTexMap
{
	int iIndex;
	int iType;
	TSTR szTexName;
};
struct HMtrl
{
	int iIndex;
	int iNumSubMtrl;
	int iNumMap;
	TSTR strName;
	TSTR strClassName;
	vector<HTexMap> TexMapList;
	vector<HMtrl> SubMtrl;
};
struct PNCT_VERTEX
{
	Point3 p;
	Point3 n;
	Point4 c;
	Point2 t;
	PNCT_VERTEX(Point3 pos, Point3 nol, Point4 col, Point2 tex)
	{
		p = pos; n = nol; c = col; t = tex;
	}
	PNCT_VERTEX() {}
};
struct HTri
{
	PNCT_VERTEX v[3];
	int			iRef;
};
struct D3D_MATRIX {
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};