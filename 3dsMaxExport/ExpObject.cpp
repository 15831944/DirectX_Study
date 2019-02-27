#include "ExpObject.h"

int ExpObject::GetIndex(const TCHAR* strNodeName)
{
	return m_MatrixMap.GetID(strNodeName);
}
bool ExpObject::CheckFile(Interface* pMax)
{
	TSTR curtFileName = FixupName(pMax->GetCurFileName());
	if (curtFileName.isNull() == false && m_CurtFileName == curtFileName)
	{
		return false;
	}

	m_MatrixMap.Release();
	m_pMtlList.clear();		//매터리얼 리스트	

	m_CurtFileName = curtFileName;
	return true;
}
bool ExpObject::Initialize(Interface* pMax)
{
	m_pMax = pMax;
	m_pRootNode = pMax->GetRootNode();

	if (pMax == NULL && m_pRootNode == NULL)
	{
		return false;
	}

	if (CheckFile(pMax) == false) return true;

	// Scene 정보얻기
	m_Interval = m_pMax->GetAnimRange();

	memset(&m_Scene, 0, sizeof(m_Scene));

	m_Scene.iFirstFrame = m_Interval.Start() / GetTicksPerFrame();
	m_Scene.iLastFrame = m_Interval.End() / GetTicksPerFrame();
	m_Scene.iFrameSpeed = GetFrameRate();
	m_Scene.iTickPerFrame = GetTicksPerFrame();

	//  최상위 INode 얻기
	PreProcess(m_pMax->GetRootNode());

	return true;
}
void ExpObject::PreProcess(INode* pNode)
{
	if (pNode == NULL) return;

	AddObject(pNode);
	AddMtl(pNode);

	// 재귀 호출
	int iNumChildren = pNode->NumberOfChildren(); // pNode의 자식 노드 개수를 반환함.
	for (int iCnt = 0; iCnt < iNumChildren; iCnt++)
	{
		INode* pChild = pNode->GetChildNode(iCnt); // iCnt 번째의 자식 노드를 반환함.
		PreProcess(pChild);
	}
}
void ExpObject::AddObject(INode* pNode)
{
	// 오브젝트 추가
	ObjectState os = pNode->EvalWorldState(m_Interval.Start());
	// 타켓 클래스인 오브젝트는 불필요한 오브젝트이다.
	if (os.obj)
	{
		// 타켓 클래스인 오브젝트는 불필요한 오브젝트이다.
		if (os.obj->ClassID() == Class_ID(TARGET_CLASS_ID, 0))
		{
			return;
		}
		switch (os.obj->SuperClassID())
		{
		case GEOMOBJECT_CLASS_ID:
		case HELPER_CLASS_ID:
		{
			int iIndex = m_MatrixMap.Add(pNode->GetName());
			TSTR parentName = pNode->GetParentNode()->GetName();
			m_MatrixMap.GetPtr(iIndex)->SetNode(pNode, m_Interval.Start(), m_MatrixMap.GetPtr(parentName));
		}
		break;
		}
	}
}
void ExpObject::AddMtl(INode* pNode)
{
	// 매터리얼 추가( 중복 제거 )
	Mtl* pMtl = pNode->GetMtl();
	if (pMtl != NULL)
	{
		bool bAdd = true;
		for (int iCnt = 0; iCnt < m_pMtlList.size(); iCnt++)
		{
			if (m_pMtlList[iCnt] == pMtl) // 중복 제거
			{
				bAdd = false;
				break;
			}
		}
		if (bAdd)
		{
			m_pMtlList.push_back(pMtl);
		}
	}
}
int ExpObject::GetMtlRef(Mtl* pMtl)
{
	for (int iMtl = 0; iMtl < m_pMtlList.size(); iMtl++)
	{
		if (m_pMtlList[iMtl] == pMtl)
		{
			return iMtl;
		}
	}
	return  -1;
}
TCHAR* ExpObject::FixupName(MSTR name)
{
	memset(m_tmpBuffer, 0, sizeof(TCHAR)*MAX_PATH);

	TCHAR* cPtr;
	_tcscpy(m_tmpBuffer, name);
	cPtr = m_tmpBuffer;

	while (*cPtr)
	{
		if (*cPtr == '"')		*cPtr = SINGLE_QUOTE;
		else if (*cPtr == ' ' || *cPtr <= CTL_CHARS)
			*cPtr = _T('_');
		cPtr++;
	}
	return m_tmpBuffer;
}
void ExpObject::DumpMatrix3(Matrix3* m, D3D_MATRIX& mat)
{
	Point3 row;
	row = m->GetRow(0);
	mat._11 = row.x; mat._13 = row.y; mat._12 = row.z;
	row = m->GetRow(2);
	mat._21 = row.x; mat._23 = row.y; mat._22 = row.z;
	row = m->GetRow(1);
	mat._31 = row.x; mat._33 = row.y; mat._32 = row.z;
	row = m->GetRow(3);
	mat._41 = row.x; mat._43 = row.y; mat._42 = row.z;
	mat._14 = mat._24 = mat._34 = 0.0f;
	mat._44 = 1.0f;
}
void ExpObject::DumpPoint3(Point3& pDest, Point3& pSrc)
{
	pDest.x = pSrc.x;
	pDest.y = pSrc.z;
	pDest.z = pSrc.y;
}
bool ExpObject::TMNegParity(Matrix3 &m)
{
	return (DotProd(CrossProd(m.GetRow(0), m.GetRow(1)),
		m.GetRow(2)) < 0.0) ? 1 : 0;
}
bool ExpObject::EqualPoint2(Point2 p1, Point2 p2)
{
	if (fabs(p1.x - p2.x) > ALMOST_ZERO)
		return false;
	if (fabs(p1.y - p2.y) > ALMOST_ZERO)
		return false;
	return true;
}
bool ExpObject::EqualPoint3(Point3 p1, Point3 p2)
{
	if (fabs(p1.x - p2.x) > ALMOST_ZERO)
		return false;
	if (fabs(p1.y - p2.y) > ALMOST_ZERO)
		return false;
	if (fabs(p1.z - p2.z) > ALMOST_ZERO)
		return false;

	return true;
}
bool ExpObject::EqualPoint4(Point4 p1, Point4 p2)
{
	if (fabs(p1.x - p2.x) > ALMOST_ZERO)
		return false;
	if (fabs(p1.y - p2.y) > ALMOST_ZERO)
		return false;
	if (fabs(p1.z - p2.z) > ALMOST_ZERO)
		return false;
	if (fabs(p1.w - p2.w) > ALMOST_ZERO)
		return false;
	return true;
}
ExpObject::ExpObject(void)
{
	m_pMax = NULL;	// 맥스 인터페이스
	m_pRootNode = NULL;
}

ExpObject::~ExpObject(void)
{
	m_MatrixMap.Release();
}

void ExpObject::GetMaterial()
{
	for (int iMtl = 0; iMtl < m_pMtlList.size(); iMtl++)
	{
		Mtl* pSrcMtl = m_pMtlList[iMtl];

		JMtl AddMtl;
		TSTR className;
		pSrcMtl->GetClassName(className);
		AddMtl.strName = FixupName(pSrcMtl->GetName());
		AddMtl.strClassName = FixupName(className);
		AddMtl.iNumSubMtl = pSrcMtl->NumSubMtls();
		AddMtl.iIndex = iMtl;

		if (pSrcMtl->NumSubMtls() > 0)
		{
			for (int iSubMtrl = 0; iSubMtrl < pSrcMtl->NumSubMtls(); iSubMtrl++)
			{
				Mtl* subMtl = pSrcMtl->GetSubMtl(iSubMtrl);

				JMtl AddSubMtl;
				AddSubMtl.iIndex = iSubMtrl;
				AddSubMtl.iNumSubMtl = subMtl->NumSubMtls();
				AddSubMtl.strName = FixupName(subMtl->GetName());

				TSTR className;
				subMtl->GetClassName(className);
				AddSubMtl.strClassName = FixupName(className);

				if (subMtl->NumSubMtls() > 0)
				{
					MessageBox(0, _T("다중 서브 매터리얼"), _T("Fatal error"), MB_OK);
				}
				if (subMtl)
				{
					GetTexture(&AddSubMtl, subMtl);
				}
				AddMtl.SubMaterial.push_back(AddSubMtl);
			}
		}
		else
		{

			GetTexture(&AddMtl, pSrcMtl);
		}
		m_Material.push_back(AddMtl);
	}


}
void ExpObject::GetTexture(JMtl* DestMtrl, Mtl* pSrcMtl)
{
	for (int iSubMap = 0; iSubMap < pSrcMtl->NumSubTexmaps(); iSubMap++)
	{
		Texmap* tex = pSrcMtl->GetSubTexmap(iSubMap);
		if (tex)
		{
			// If it is a standard material we can see if the map is enabled.
			if (pSrcMtl->ClassID() == Class_ID(DMTL_CLASS_ID, 0))
			{
				StdMat* std = (StdMat*)pSrcMtl;
				if (!std->MapEnabled(iSubMap))
					continue;
			}

			JTexMap TexMap;
			TexMap.iType = iSubMap;

			if (tex->ClassID() == Class_ID(BMTEX_CLASS_ID, 0x00))
			{
				TSTR mapName = ((BitmapTex *)tex)->GetMapName();
				TSTR strFullName;
				SplitPathFile(mapName, &strFullName, &mapName);
				TexMap.strTextureName = FixupName(mapName);
			}
			DestMtrl->TexMaps.push_back(TexMap);
			DestMtrl->iNumMap = DestMtrl->TexMaps.size();
		}
	}
}
void ExpObject::UpdateObject()
{
	for (int iObj = 0; iObj < m_MatrixMap.Count(); iObj++)
	{
		MatrixIndex *pPoint = (MatrixIndex *)m_MatrixMap.Map[iObj];
		GetObject(pPoint);
	}
}

void ExpObject::GetObject(MatrixIndex* pPoint)
{
	JMesh*	pMesh = &pPoint->m_Mesh;
	pMesh->m_ClassType = pPoint->m_ClassType;
	GetNodeHeader(pPoint->m_pINode, pMesh);	// 노드의 이름을 얻는다.
	GetNodeTM(pPoint->m_pINode, pMesh);	// 노드의 행렬을 얻는다.
	GetMesh(pPoint->m_pINode, pMesh);	// 기하 정보를 얻는다.		
	GetAnimKeys(pPoint->m_pINode, pMesh);	// 에니메이션 정보를 얻는다.
}

void ExpObject::GetNodeHeader(INode* node, JMesh*	tMesh)
{
	tMesh->m_strNodeName = FixupName(node->GetName());
	INode* parent = node->GetParentNode();
	if (parent && (!parent->IsRootNode()))
	{
		tMesh->m_strParentName = FixupName(parent->GetName());
	}
}
void ExpObject::GetNodeTM(INode* node, JMesh*	tMesh)
{
	Matrix3 g_matWorld = node->GetNodeTM(m_Interval.Start());
	DumpMatrix3(&g_matWorld, tMesh->m_matWorld);
}

void ExpObject::GetMesh(INode* node, JMesh*	tMesh)
{
	Matrix3 tm = node->GetObjTMAfterWSM(m_Interval.Start());
	// 작업중 및 작업완료된 파이프라인의 결과에 액세스함으로써 현재노드의 결과를 돌려준다.
	ObjectState os = node->EvalWorldState(m_Interval.Start());
	if (!os.obj || os.obj->SuperClassID() != GEOMOBJECT_CLASS_ID)
	{
		return;
	}

	BOOL needDel;
	TriObject* tri = GetTriObjectFromNode(node, m_Interval.Start(), needDel);
	if (!tri)
	{
		return;
	}

	Mesh* mesh = &tri->GetMesh();
	// 바운딩 박스
	mesh->buildBoundingBox();
	Box3 box = mesh->getBoundingBox(&tm);
	DumpPoint3(tMesh->m_Box.pmax, box.pmax);
	DumpPoint3(tMesh->m_Box.pmin, box.pmin);

	tMesh->m_iNumFace = mesh->getNumFaces();

	BOOL negScale = TMNegParity(tm);
	int v0, v1, v2;
	if (negScale) { v0 = 2;		v1 = 1;		v2 = 0; }
	else { v0 = 0;		v1 = 1;		v2 = 2; }

	tMesh->m_TriList.resize(tMesh->m_iNumFace);
	for (int iFace = 0; iFace < tMesh->m_iNumFace; iFace++)
	{
		Matrix3 pInverse = Inverse(node->GetNodeTM(m_Interval.Start()));

		Point3 v;
		//Point3 vv;

		if (mesh->getNumVerts() > 0)
		{
			/*			vv = tm * mesh->verts[   mesh->faces[iFace].v[v0]    ];
						v = mesh->verts[   mesh->faces[iFace].v[v0]    ] * tm;	*/


			v = mesh->verts[mesh->faces[iFace].v[v0]] * tm * pInverse;
			DumpPoint3(tMesh->m_TriList[iFace].v[0].p, v);

			v = mesh->verts[mesh->faces[iFace].v[v2]] * tm * pInverse;
			DumpPoint3(tMesh->m_TriList[iFace].v[1].p, v);

			v = mesh->verts[mesh->faces[iFace].v[v1]] * tm * pInverse;
			DumpPoint3(tMesh->m_TriList[iFace].v[2].p, v);
		}
		if (mesh->getNumTVerts() > 0)
		{
			tMesh->m_TriList[iFace].v[0].t.x = mesh->tVerts[mesh->tvFace[iFace].t[v0]].x;
			tMesh->m_TriList[iFace].v[0].t.y = 1.0f - mesh->tVerts[mesh->tvFace[iFace].t[v0]].y;
			tMesh->m_TriList[iFace].v[1].t.x = mesh->tVerts[mesh->tvFace[iFace].t[v2]].x;
			tMesh->m_TriList[iFace].v[1].t.y = 1.0f - mesh->tVerts[mesh->tvFace[iFace].t[v2]].y;
			tMesh->m_TriList[iFace].v[2].t.x = mesh->tVerts[mesh->tvFace[iFace].t[v1]].x;
			tMesh->m_TriList[iFace].v[2].t.y = 1.0f - mesh->tVerts[mesh->tvFace[iFace].t[v1]].y;
		}

		tMesh->m_TriList[iFace].v[0].c = Point4(1, 1, 1, 1);
		tMesh->m_TriList[iFace].v[1].c = Point4(1, 1, 1, 1);
		tMesh->m_TriList[iFace].v[2].c = Point4(1, 1, 1, 1);

		if (mesh->getNumVertCol() > 0)
		{
			tMesh->m_TriList[iFace].v[0].c.x = mesh->vertCol[mesh->vcFace[iFace].t[v0]].x;
			tMesh->m_TriList[iFace].v[0].c.y = mesh->vertCol[mesh->vcFace[iFace].t[v0]].y;
			tMesh->m_TriList[iFace].v[0].c.z = mesh->vertCol[mesh->vcFace[iFace].t[v0]].z;
			tMesh->m_TriList[iFace].v[0].c.w = 1.0f;
			tMesh->m_TriList[iFace].v[1].c.x = mesh->vertCol[mesh->vcFace[iFace].t[v2]].x;
			tMesh->m_TriList[iFace].v[1].c.y = mesh->vertCol[mesh->vcFace[iFace].t[v2]].y;
			tMesh->m_TriList[iFace].v[1].c.z = mesh->vertCol[mesh->vcFace[iFace].t[v2]].z;
			tMesh->m_TriList[iFace].v[1].c.w = 1.0f;
			tMesh->m_TriList[iFace].v[2].c.x = mesh->vertCol[mesh->vcFace[iFace].t[v1]].x;
			tMesh->m_TriList[iFace].v[2].c.y = mesh->vertCol[mesh->vcFace[iFace].t[v1]].y;
			tMesh->m_TriList[iFace].v[2].c.z = mesh->vertCol[mesh->vcFace[iFace].t[v1]].z;
			tMesh->m_TriList[iFace].v[2].c.w = 1.0f;
		}

		// 정점 노말 얻기
		mesh->buildNormals();

		int  vert = mesh->faces[iFace].getVert(v0);
		Point3 vn = GetVertexNormal(mesh, iFace, mesh->getRVertPtr(vert));
		DumpPoint3(tMesh->m_TriList[iFace].v[0].n, vn);

		vert = mesh->faces[iFace].getVert(v2);
		vn = GetVertexNormal(mesh, iFace, mesh->getRVertPtr(vert));
		DumpPoint3(tMesh->m_TriList[iFace].v[1].n, vn);

		vert = mesh->faces[iFace].getVert(v1);
		vn = GetVertexNormal(mesh, iFace, mesh->getRVertPtr(vert));
		DumpPoint3(tMesh->m_TriList[iFace].v[2].n, vn);

		// 서브 매터리얼 인덱스
		tMesh->m_TriList[iFace].iSubIndex = mesh->faces[iFace].getMatID();
	}
	if (needDel)
	{
		delete tri;
	}

	tMesh->m_iMtrlRef = GetMtlRef(node->GetMtl());
}

Point3 ExpObject::GetVertexNormal(Mesh* mesh, int faceNo, RVertex* rv)
{
	Face* f = &mesh->faces[faceNo];
	DWORD smGroup = f->smGroup;
	int numNormals = rv->rFlags & NORCT_MASK;
	Point3 vertexNormal;

	if (rv->rFlags & SPECIFIED_NORMAL)
	{
		vertexNormal = rv->rn.getNormal();
	}
	else if (numNormals && smGroup)
	{
		if (numNormals == 1)
		{
			vertexNormal = rv->rn.getNormal();
		}
		else
		{
			for (int i = 0; i < numNormals; i++)
			{
				if (rv->ern[i].getSmGroup() & smGroup)
				{
					vertexNormal = rv->ern[i].getNormal();
				}
			}
		}
	}
	else
	{
		vertexNormal = mesh->getFaceNormal(faceNo);
	}
	return vertexNormal;
}
TriObject* ExpObject::GetTriObjectFromNode(INode *node, TimeValue t, int &deleteIt)
{
	deleteIt = FALSE;
	Object *obj = node->EvalWorldState(t).obj;
	if (obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0)))
	{
		TriObject *tri = (TriObject *)obj->ConvertToType(t, Class_ID(TRIOBJ_CLASS_ID, 0));
		if (obj != tri) deleteIt = TRUE;
		return tri;
	}
	else
	{
		return NULL;
	}
}

void ExpObject::GetAnimKeys(INode* pNode, JMesh* pMesh)
{
	BOOL bPosAnim;
	BOOL bRotAnim;
	BOOL bScaleAnim;

	m_iDeltaTick = m_Scene.iTickPerFrame;

	if (CheckForAnimation(pNode, bPosAnim, bRotAnim, bScaleAnim))
	{
		if (bPosAnim)
		{
			DumpPosSample(pNode, pMesh);
		}
		if (bRotAnim)
		{
			DumpRotSample(pNode, pMesh);
		}
		if (bScaleAnim)
		{
			DumpScaleSample(pNode, pMesh);
		}
	}

	// Export the visibility track
	Control* visCont = pNode->GetVisController();
	if (visCont)
	{
		DumpFloatKeys(visCont, pMesh);
	}
}
bool ExpObject::GetDecompAffine(TimeValue t, INode* pNode, AffineParts* ap, Point3* rotAxis, float* rotAngle)
{
	Matrix3 tm = pNode->GetNodeTM(t) * Inverse(pNode->GetParentTM(t));
	decomp_affine(tm, ap);

	Point3 vRotAxis;
	float  fRotAngle;
	if (rotAngle != NULL && rotAngle != NULL)
	{
		AngAxisFromQ(ap->q, rotAngle, *rotAxis);
	}
	return true;
}
BOOL ExpObject::CheckForAnimation(INode* pNode, BOOL& bPos, BOOL& bRot, BOOL& bScale)
{
	AffineParts ap;
	Point3 firstPos, firstRotAxis, firstScaleFactor;
	float firstRotAngle;
	GetDecompAffine(m_Interval.Start(), pNode, &ap, &firstRotAxis, &firstRotAngle);
	firstPos = ap.t;
	firstScaleFactor = ap.k;

	TimeValue start = m_Interval.Start() + GetTicksPerFrame();
	TimeValue end = m_Interval.End();

	bPos = bRot = bScale = FALSE;
	float rotAngle;
	Point3 rotAxis;

	for (TimeValue t = start; t <= end; t += m_iDeltaTick)
	{
		GetDecompAffine(t, pNode, &ap, &rotAxis, &rotAngle);

		if (!bPos)
		{
			if (!EqualPoint3(ap.t, firstPos))
			{
				bPos = TRUE;
			}
		}
		if (!bRot)
		{
			if (fabs(rotAngle - firstRotAngle) > ALMOST_ZERO)
			{
				bRot = TRUE;
			}
			else if (!EqualPoint3(rotAxis, firstRotAxis))
			{
				bRot = TRUE;
			}
		}
		if (!bScale)
		{
			if (!EqualPoint3(ap.k, firstScaleFactor))
			{
				bScale = TRUE;
			}
		}

		if (bPos && bRot && bScale)		break;
	}
	return bPos || bRot || bScale;
}

void ExpObject::DumpPosSample(INode* pNode, JMesh* pMesh)
{
	TimeValue start = m_Interval.Start();
	TimeValue end = m_Interval.End();
	AffineParts ap;

	for (TimeValue t = start; t <= end; t += m_iDeltaTick)
	{
		GetDecompAffine(t, pNode, &ap);

		JAnimTrack pAnim;
		pAnim.iTick = t;
		pAnim.vValue.x = ap.t.x;
		pAnim.vValue.y = ap.t.z;
		pAnim.vValue.z = ap.t.y;
		pMesh->m_PosTrack.push_back(pAnim);
	}
}

void ExpObject::DumpRotSample(INode* pNode, JMesh* pMesh)
{
	TimeValue start = m_Interval.Start();
	TimeValue end = m_Interval.End();

	AffineParts ap;
	for (TimeValue t = start; t <= end; t += m_iDeltaTick)
	{
		GetDecompAffine(t, pNode, &ap);

		JAnimTrack pAnim;
		pAnim.iTick = t;
		pAnim.qValue.x = ap.q.x;
		pAnim.qValue.y = ap.q.z;
		pAnim.qValue.z = ap.q.y;
		pAnim.qValue.w = ap.q.w;
		pMesh->m_RotTrack.push_back(pAnim);
	}
}

void ExpObject::DumpScaleSample(INode* pNode, JMesh* pMesh)
{
	TimeValue start = m_Interval.Start();
	TimeValue end = m_Interval.End();

	AffineParts ap;
	for (TimeValue t = start; t <= end; t += m_iDeltaTick)
	{
		GetDecompAffine(t, pNode, &ap);

		JAnimTrack Anim;
		Anim.iTick = t;
		Anim.vValue.x = ap.k.x;
		Anim.vValue.y = ap.k.z;
		Anim.vValue.z = ap.k.y;
		Anim.qValue.x = ap.u.x;
		Anim.qValue.y = ap.u.z;
		Anim.qValue.z = ap.u.y;
		Anim.qValue.w = ap.u.w;
		pMesh->m_SclTrack.push_back(Anim);
	}
}
void ExpObject::DumpFloatKeys(Control* cont, JMesh* pMesh)
{
	if (!cont)		return;
	int i;
	IKeyControl *ikc = NULL;
	ikc = GetKeyControlInterface(cont);

	JAnimTrack Anim;

	// TCB float
	if (ikc && cont->ClassID() == Class_ID(TCBINTERP_FLOAT_CLASS_ID, 0))
	{
		for (i = 0; i < ikc->GetNumKeys(); i++)
		{
			ITCBFloatKey key;
			ikc->GetKey(i, &key);
			Anim.iTick = key.time;
			Anim.vValue.x = key.val;
			pMesh->m_VisTrack.push_back(Anim);
		}
	}
	// Bezier float
	else if (ikc && cont->ClassID() == Class_ID(HYBRIDINTERP_FLOAT_CLASS_ID, 0)) {
		for (i = 0; i < ikc->GetNumKeys(); i++) {
			IBezFloatKey key;
			ikc->GetKey(i, &key);
			Anim.iTick = key.time;
			Anim.vValue.x = key.val;
			pMesh->m_VisTrack.push_back(Anim);

		}
	}
	else if (ikc && cont->ClassID() == Class_ID(LININTERP_FLOAT_CLASS_ID, 0)) {
		for (i = 0; i < ikc->GetNumKeys(); i++)
		{
			ILinFloatKey key;
			ikc->GetKey(i, &key);
			Anim.iTick = key.time;
			Anim.vValue.x = key.val;
			pMesh->m_VisTrack.push_back(Anim);
		}
	}
	else
	{
		TSTR name;
		cont->GetClassName(name);

		// If it is animated at all...
		if (cont->IsAnimated()) {
			// Get the range of the controller animation 
			Interval range;
			// Get range of full animation
			Interval animRange = m_pMax->GetAnimRange();
			TimeValue t = cont->GetTimeRange(TIMERANGE_ALL).Start();
			float value;

			// While we are inside the animation... 
			while (animRange.InInterval(t))
			{
				// Sample the controller
				range = FOREVER;
				cont->GetValue(t, &value, range);

				// Set time to start of controller validity interval 
				t = range.Start();

				Anim.iTick = t;
				Anim.vValue.x = value;
				pMesh->m_VisTrack.push_back(Anim);

				if (range.End() > cont->GetTimeRange(TIMERANGE_ALL).End())
				{
					break;
				}
				else
				{
					//t = (range.End()/GetTicksPerFrame()+GetKeyFrameStep()) * GetTicksPerFrame();
					t = (range.End() / GetTicksPerFrame()) * GetTicksPerFrame();
				}
			}
		}
	}
}
