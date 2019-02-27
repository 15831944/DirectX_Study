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
	vector<Mtl*>	m_pMtlList;		//���͸��� ����Ʈ	
	vector<JMtl>	m_Material;// ��� �� ���� ����Ʈ	
	TSTR			m_CurtFileName; // �ƽ������̸�
	TCHAR			m_tmpBuffer[MAX_PATH];//�ӽù���
public:
	bool	CheckFile(Interface* pMax);
	bool	Initialize(Interface*	p3dsMax = NULL);
	void	PreProcess(INode* pNode);
	void	AddObject(INode* pNode);
	void	AddMtl(INode* pNode);// �ߺ����� �ʰ� ���͸��� �߰�
	int		GetMtlRef(Mtl* pMtl); // pMtl�� ����� �ε����� ��ȯ�Ѵ�.
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
	void	GetMaterial();//���͸��� ����Ʈ���� ���� ���
	void	GetTexture(JMtl* pDestMtl, Mtl* pSrcMtl);//���͸��� ����Ʈ���� ���� ���
public:
	void	UpdateObject();
	void	GetObject(MatrixIndex* pPoint);//������Ʈ ����Ʈ���� ���� ���
	// ������Ʈ ���� 
	void	GetNodeHeader(INode* node, JMesh*	pMesh);
	void	GetNodeTM(INode* node, JMesh*	pMesh);
	// �޽� ����
	void	GetMesh(INode* node, JMesh*	pMesh);
	Point3	GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv);
	TriObject* GetTriObjectFromNode(INode *node, TimeValue t, int &deleteIt);
	//���ϸ��̼�
public:
	int		m_iDeltaTick;
	// ���ø�
	void	GetAnimKeys(INode* pNode, JMesh* pMesh);
	void	DumpScaleSample(INode* node, JMesh* Mesh);
	void	DumpRotSample(INode* node, JMesh* Mesh);
	void	DumpPosSample(INode* node, JMesh* Mesh);
	BOOL	CheckForAnimation(INode* node, BOOL& bPos, BOOL& bRot, BOOL& bScale);
	bool	GetDecompAffine(TimeValue t, INode* pNode, AffineParts* ap,
		Point3* rotAxis = NULL, float* rotAngle = NULL);
	// Ű ������ 
	void	DumpFloatKeys(Control* cont, JMesh* pMesh);
	//void	DumpPosKeys(Control* cont, TMesh* pMesh);
	//void	DumpRotKeys(Control* cont, TMesh* pMesh);
	//void	DumpScaleKeys(Control* cont, TMesh* pMesh) ;
	//BOOL	IsKnownController(Control* cont);	
public:
	ExpObject();
	virtual ~ExpObject();
};

