#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
//#include "resource.h"
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
#define CTL_CHARS		31
#define SINGLE_QUOTE	39 // ( ' )
#define ALMOST_ZERO		1.0e-3f
#define SAFE_NEW(A, B)				{ if (!A) A = new B; }
/* ===== Utility ===== */
typedef basic_string<TCHAR>				T_STR;
typedef basic_string<CHAR>				CHAR_STRING;
typedef vector<basic_string<TCHAR>>		T_STR_VECTOR;
typedef vector<DWORD>					DWORD_VECTOR;
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
struct JAnimTrack
{
	int				iType;
	int				iTick;
	Quat			qValue;
	Point3			vValue;
};
const enum OBJECTCLASSTYPE {
	CLASS_GEOM = 0,
	CLASS_BONE,
	CLASS_DUMMY,
	CLASS_BIPED,
};
struct JTri
{
	PNCT_VERTEX	v[3];
	int			iSubIndex;
};
struct JScene
{
	int iVersion;		// 파일 버전
	int	iFirstFrame;    // 시작 프레임
	int	iLastFrame;     // 마지막 프레임
	int	iFrameSpeed;    // 1초당 프레임 개수(30)
	int	iTickPerFrame;  // 1프레임의 틱 값(160)
	int iNumMesh;		// 메쉬오브젝트 개수
	int iMaxWeight;		// 정점 당 가중치
	int iBindPose;		// 바인딩 포즈 에니메이션 여부
};
struct JTexMap
{
	int		iIndex;
	int		iType; 	// 텍스쳐 타입 인덱스
	TSTR	strTextureName; 	// 텍스쳐 이름.
};
struct JMtl
{
	int				iIndex;
	int				iNumSubMtl;	// 서브 매터리얼 개수	
	int				iNumMap;	// 텍스쳐 맵 갯수
	TSTR			strName; // 매터리얼 이름	
	TSTR			strClassName;// 맵클래스 이름
	vector<JTexMap>	TexMaps; // 맵 타입들	
	vector<JMtl>	SubMaterial; // 서브 매터리얼 저장벡터
};
struct JMESH_HEADER
{
	OBJECTCLASSTYPE		m_ClassType;
	Box3				m_Box;
	D3D_MATRIX			m_matWorld;
	int					m_iNumVertex;
	int					m_iNumFace;
	int					m_iMtrlRef;
	int					m_iNumTrack[4];
};
struct JMesh : public JMESH_HEADER
{
	TSTR				m_strNodeName;
	TSTR				m_strParentName;
	vector<JAnimTrack>	m_PosTrack;
	vector<JAnimTrack>	m_RotTrack;
	vector<JAnimTrack>	m_SclTrack;
	vector<JAnimTrack>	m_VisTrack;
	vector<JTri>		m_TriList;
	vector<JMesh*>		m_pSubMesh;

	JMesh()
	{
		m_iMtrlRef = -1;
		m_iNumFace = 0;
		m_iNumTrack[0] = 0;
		m_iNumTrack[1] = 0;
		m_iNumTrack[2] = 0;
		m_iNumTrack[3] = 0;
		m_ClassType = CLASS_GEOM;
	};
	~JMesh()
	{
		m_PosTrack.clear();
		m_RotTrack.clear();
		m_SclTrack.clear();
		m_VisTrack.clear();
		m_TriList.clear();
	};
};
struct MatrixIndex
{
	OBJECTCLASSTYPE m_ClassType;
	int m_iIndex;
	T_STR m_szName;
	vector<PNCT_VERTEX> m_pVertexList;
	Matrix3 m_NodeTM;
	Matrix3 m_InvNodeTM;
	INode* m_pINode;
	Object* m_pObj;
	Control* m_pControl;
	JMesh m_Mesh;
	void		Add(int iIndex, T_STR szName)
	{
		m_pObj = NULL;
		m_pControl = NULL;
		m_iIndex = iIndex;
		m_szName = szName;
	}
	void		SetNode(INode* pNode, int iTick, MatrixIndex* pParentIndex = 0)
	{
		m_pINode = pNode;
		m_pObj = m_pINode->GetObjectRef();
		m_pControl = m_pINode->GetTMController();

		m_ClassType = CLASS_GEOM;

		if (m_pObj && m_pObj->ClassID() == Class_ID(BONE_CLASS_ID, 0))// 본 오브젝트   
		{
			m_ClassType = CLASS_BONE;
		}
		if (m_pObj && m_pObj->ClassID() == Class_ID(DUMMY_CLASS_ID, 0))  // 더미 오브젝트
		{
			m_ClassType = CLASS_DUMMY;
		}
		if (m_pControl->ClassID() == BIPSLAVE_CONTROL_CLASS_ID ||        // 루트 바이패드 제외한 모든 바이패드들							 
			m_pControl->ClassID() == BIPBODY_CONTROL_CLASS_ID)	     // 루트 바이패드 1개
		{
			m_ClassType = CLASS_BIPED;
		}

		m_NodeTM = pNode->GetNodeTM(iTick);
		m_InvNodeTM = Inverse(m_NodeTM);
	}
	void					Release()
	{
		for (int iSub = 0; iSub < m_Mesh.m_pSubMesh.size(); iSub++)
		{
			delete m_Mesh.m_pSubMesh[iSub];
		}
		m_Mesh.m_pSubMesh.clear();
	};
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
struct HTri
{
	PNCT_VERTEX v[3];
	int			iRef;
};
template <class Child>
class TemplateMap
{
public:
	typedef map<int, Child*> TMap;
	typedef typename TMap::iterator TITOR;
	TITOR ITOR;
	TMap Map;
	int m_iCurrentIndex;
public:
	bool Init();
	int Add(Child* child);
	int Add(const TCHAR* pFileName);
	Child* GetPtr(DWORD iIndex);
	Child* GetPtr(const TCHAR* pFileName);
	int GetID(Child* child);
	int GetID(const TCHAR* pFileName);
	int Count();
	bool Release();
public:
	TemplateMap();
	virtual ~TemplateMap();
};
template < class Child >
int TemplateMap< Child >::GetID(Child* pChild)
{
	int iIndex = -1;
	for (TITOR itor = Map.begin(); itor != Map.end(); itor++)
	{
		Child *pPoint = (Child *)(*itor).second;
		if (pChild == pPoint)
		{
			iIndex = (*itor).first;
			break;
		}
	}
	return dwIndex;
}
template < class Child >
int TemplateMap< Child >::GetID(const TCHAR* szName)
{
	int iIndex = -1;
	for (TITOR itor = Map.begin(); itor != Map.end(); itor++)
	{
		Child *pPoint = (Child *)(*itor).second;
		if (!_tcsicmp(pPoint->m_szName.c_str(), szName))
		{
			iIndex = (*itor).first;
			break;
		}
	}
	return iIndex;
}

template < class Child >
bool TemplateMap< Child >::Init()
{
	m_iCurIndex = 0;
	Map.clear();
	return true;
}
template < class Child >
int TemplateMap< Child >::Count()
{
	return (int)Map.size();
}
template < class Child >
bool TemplateMap< Child >::Release()
{
	for (TITOR itor = Map.begin(); itor != Map.end(); itor++)
	{
		Child *pPoint = (Child *)(*itor).second;
		if (pPoint)
			pPoint->Release();
		else
			return false;
		delete pPoint;
	}
	Map.clear();
	m_iCurrentIndex = 0;
	return true;
}
template < class Child >
int TemplateMap< Child >::Add(Child* pChild)
{
	if (pChild == NULL)
	{
		return 0;
	}
	for (TITOR itor = Map.begin(); itor != Map.end(); itor++)
	{
		Child *pPoint = (Child *)(*itor).second;
		if (pPoint == pChild)
		{
			return 0;
		}
	}
	Map.insert(make_pair(m_iCurIndex++, pChild));
	return m_iCurIndex - 1;
}
template < class Child >
int TemplateMap< Child >::Add(const TCHAR *pFileName)
{
	// 종복 방지 
	if (pFileName)
	{
		TCHAR szFileName[256];
		TCHAR Drive[MAX_PATH];
		TCHAR Dir[MAX_PATH];
		TCHAR FName[MAX_PATH];
		TCHAR Ext[MAX_PATH];
		_tsplitpath_s(pFileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		_stprintf_s(szFileName, _T("%s%s"), FName, Ext);

		for (TITOR itor = Map.begin(); itor != Map.end(); itor++)
		{
			Child *pPoint = (Child *)(*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szFileName))
			{
				return (*itor).first;
			}
		}
	}

	Child *pPoint = NULL;
	SAFE_NEW(pPoint, Child);
	pPoint->Add(m_iCurrentIndex, pFileName);
	Map.insert(make_pair(m_iCurrentIndex++, pPoint));
	return m_iCurrentIndex - 1;
}
template < class Child >
Child *TemplateMap< Child >::GetPtr(DWORD dwIndex)
{
	TITOR itor = Map.find(dwIndex);
	if (itor == Map.end()) return NULL;
	Child *pPoint = (*itor).second;
	return pPoint;
}
template < class Child >
Child* TemplateMap< Child >::GetPtr(const TCHAR* szName)
{
	for (TITOR itor = Map.begin(); itor != Map.end(); itor++)
	{
		Child *pPoint = (Child *)(*itor).second;
		if (!_tcsicmp(pPoint->m_szName.c_str(), szName))
		{
			return pPoint;
		}
	}
	return NULL;
}

template < class Child >
TemplateMap< Child >::TemplateMap()
{
	m_iCurrentIndex = 0;
	Map.clear();
}

template < class Child >
TemplateMap< Child >::~TemplateMap()
{
	Release();
}