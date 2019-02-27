#pragma once
#include "dllStd.h"

class ExpObject
{
public:
	Interface* m_pMax;
	INode* m_pRootNode;
	Interval m_Interval;
	JScene m_Scene;
	TemplateMap< MatrixIndex >		m_MatrixMap;
	vector<Mtl*>	m_pMtlList;		//매터리얼 리스트	
	vector<JMtl>	m_Material;// 출력 할 정보 리스트	
	TSTR			m_CurtFileName; // 맥스파일이름
	TCHAR			m_tmpBuffer[MAX_PATH];//임시버퍼
public:
	bool	CheckFile(Interface* pMax);
	bool	Initialize(Interface*	p3dsMax = NULL);
	void	PreProcess(INode* pNode);
	void	AddObject(INode* pNode);
	void	AddMtl(INode* pNode);// 중복되지 않고 매터리얼 추가
	int		GetMtlRef(Mtl* pMtl); // pMtl이 저장된 인덱스를 반환한다.
	void	SetBindPose(bool bBindPose = false) { m_Scene.iBindPose = bBindPose; }
	int		GetIndex(const TCHAR* strNodeName);
public:
	void	DumpMatrix3(Matrix3* m, D3D_MATRIX& mat);
	void	DumpPoint3(Point3& pDest, Point3& pSrc);
	bool	TMNegParity(Matrix3 &m);
	bool	EqualPoint2(Point2 p1, Point2 p2);
	bool	EqualPoint3(Point3 p1, Point3 p2);
	bool	EqualPoint4(Point4 p1, Point4 p2);
	TCHAR*	FixupName(MSTR name);
public:
	void	GetMaterial();//매터리얼 리스트에서 정보 얻기
	void	GetTexture(JMtl* pDestMtl, Mtl* pSrcMtl);//매터리얼 리스트에서 정보 얻기
public:
	void	UpdateObject();
	void	GetObject(MatrixIndex* pPoint);//오브젝트 리스트에서 정보 얻기
	// 오브젝트 정보 
	void	GetNodeHeader(INode* node, JMesh*	pMesh);
	void	GetNodeTM(INode* node, JMesh*	pMesh);
	// 메쉬 정보
	void	GetMesh(INode* node, JMesh*	pMesh);
	Point3	GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv);
	TriObject* GetTriObjectFromNode(INode *node, TimeValue t, int &deleteIt);
	//에니메이션
public:
	int		m_iDeltaTick;
	// 샘플링
	void	GetAnimKeys(INode* pNode, JMesh* pMesh);
	void	DumpScaleSample(INode* node, JMesh* Mesh);
	void	DumpRotSample(INode* node, JMesh* Mesh);
	void	DumpPosSample(INode* node, JMesh* Mesh);
	BOOL	CheckForAnimation(INode* node, BOOL& bPos, BOOL& bRot, BOOL& bScale);
	bool	GetDecompAffine(TimeValue t, INode* pNode, AffineParts* ap,
		Point3* rotAxis = NULL, float* rotAngle = NULL);
	// 키 프레임 
	void	DumpFloatKeys(Control* cont, JMesh* pMesh);
	//void	DumpPosKeys(Control* cont, TMesh* pMesh);
	//void	DumpRotKeys(Control* cont, TMesh* pMesh);
	//void	DumpScaleKeys(Control* cont, TMesh* pMesh) ;
	//BOOL	IsKnownController(Control* cont);	
public:
	ExpObject();
	virtual ~ExpObject();
};

