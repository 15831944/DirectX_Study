#include "JPaser.h"
AnimTrack* JPaser::SetDoublyLinkedList(AnimTrack* pCurrentTrack, AnimTrack* pPrev)
{
	if (pPrev)
	{
		pPrev->NextTrack = pCurrentTrack;
		pCurrentTrack->PrevTrack = pPrev;
	}
	return pCurrentTrack;
}
int  JPaser::SearchArray(int iCnt, const char** pSection)
{
	while (m_dwTokenIndex < m_Tokenlist.size())
	{
		if (GetNextToken() == NULL)
		{
			return -1;
		}
		for (int itype = 0; itype < iCnt; itype++)
		{
			if (strstr(m_CurrentToken.c_str(),
				pSection[itype]))
			{
				return itype;
			}
		}
	}
	return -1;
}
bool JPaser::Load()
{
	INT iLine;
	if (!LoadScene()) return false;
	if (!LoadMaterial()) return false;
	while (m_dwTokenIndex + 1 < m_Tokenlist.size())
	{
		ASE_GEOMETRY* geom = new ASE_GEOMETRY;
		int iType = SearchArray(2, aseSection);
		switch (iType)
		{
		case GEOM:
		{
			iLine = LoadGeom(geom);
			m_Geom.push_back(geom);
		}break;
		case HELPER:
		{
			iLine = LoadHelperObj(geom);
			m_Geom.push_back(geom);
		}break;
		default:
		{
		}break;
		}

	}
	for (int iGeom = 0; iGeom < m_Geom.size(); iGeom++)
	{
		if (!GenTriangle(m_Geom[iGeom])) return false;
		SetAnimation(m_Geom[iGeom]);
	}
	if (!Convert())return false;
	return true;
}
vector<JMesh*> JPaser::GetData()
{
	return m_pMeshList;
}
bool JPaser::clear()
{
	m_pMeshList.clear();
	m_Tokenlist.clear();
	m_CurrentToken.clear();
	SAFE_DELETE(m_pData);
	for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
	{
		m_Mtrl[iMtrl].subMtrl.clear();
		m_Mtrl[iMtrl].tex.clear();
	}
	m_Mtrl.clear();
	//m_Geom.IndexColList.clear();
	//m_Geom.IndexPosList.clear();
	//m_Geom.IndexTexList.clear();
	//m_Geom.strNodeName.clear();
	//m_Geom.TriangleList.clear();
	//m_Geom.TriNormalList.clear();
	//m_Geom.VertexColList.clear();
	//m_Geom.VertexPosList.clear();
	//m_Geom.VertexTexList.clear();
	return true;
}
bool JPaser::LoadScene()
{
	INT iLine = 0;
	char szTemp[256] = { 0, };
	if (FindToken("SCENE"))
	{
		if ((iLine = FindToken("SCENE_FIRSTFRAME")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &m_Scene.iFirstFrame);
		}
		if ((iLine = FindToken("SCENE_LASTFRAME")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &m_Scene.iLastFrame);
		}
		if ((iLine = FindToken("SCENE_FRAMESPEED")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &m_Scene.iFrameSpeed);
		}
		if ((iLine = FindToken("SCENE_TICKSPERFRAME")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &m_Scene.iTickPerFrame);
		}
	}
	return true;
}
bool JPaser::LoadMaterial()
{
	INT iLine = 0;
	INT iPrevLine = 0;
	char szTemp[256] = { 0, };
	if ((iLine = FindToken("MATERIAL_LIST")) > 0)
	{
		int iMtrlCnt = 0;
		int iSubMtrlCnt = 0;
		if ((iLine = FindToken("MATERIAL_COUNT")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &iMtrlCnt);
		}
		m_Mtrl.resize(iMtrlCnt);

		for (int MtrlNum = 0; MtrlNum < iMtrlCnt; MtrlNum++)
		{
			if ((iLine = FindToken("MATERIAL ")) > 0)
			{
				if ((iLine = FindToken("MATERIAL_NAME")) > 0)
				{
					m_Mtrl[MtrlNum].strMtrlName = DestroyTokenName(m_Tokenlist[iLine].c_str(), "\"");
				}
				iPrevLine = iLine;
				if ((iLine = FindToken("NUMSUBMTLS ")) > 0)
				{
					sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &iSubMtrlCnt);
					m_Mtrl[MtrlNum].subMtrl.resize(iSubMtrlCnt);
				}

				if (iLine > 0)
				{
					ASE_MATERIAL tempMtrl;
					ASE_TEXTURE tmpTexture = { 0, };
					for (int iSubMtrl = 0; iSubMtrl < iSubMtrlCnt; iSubMtrl++)
					{
						if ((iLine = FindToken("SUBMATERIAL ")) > 0)
						{
							if ((iLine = FindToken("MATERIAL_NAME")) > 0)
							{
								m_Mtrl[MtrlNum].subMtrl[iSubMtrl].strMtrlName = DestroyTokenName(m_Tokenlist[iLine].c_str(), "\"");
							}

							if ((iLine = FindToken("MATERIAL_XP_TYPE")) > 0)
							{
								if ((iLine = GetLine("MAP_DIFFUSE")) > 0)
								{
									tmpTexture.iType = DIFFUSE;
									if ((iLine = FindToken("BITMAP")) > 0)
									{
										sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp, szTemp);
										tmpTexture.strTexName = DividePath(DestroyToken(szTemp, "\"").c_str());
									}
									m_Mtrl[MtrlNum].subMtrl[iSubMtrl].tex.push_back(tmpTexture);
								}
							}
						}
					}
				}
				else
				{
					m_dwTokenIndex = iPrevLine;
					ASE_TEXTURE tmpTexture = { 0, };
					if ((iLine = FindToken("MAP_DIFFUSE")) > 0)
					{
						tmpTexture.iType = DIFFUSE;
						if ((iLine = FindToken("BITMAP")) > 0)
						{
							sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp, szTemp);
							tmpTexture.strTexName = DividePath(DestroyToken(szTemp, "\"").c_str());
						}
					}
					m_Mtrl[MtrlNum].tex.push_back(tmpTexture);
				}
			}
		}
	}
	--m_dwTokenIndex;
	return true;
}
INT JPaser::LoadGeom(ASE_GEOMETRY* geom)
{
	INT			iLine = 0;
	char		szTemp[256] = { 0, };
	int			iTemp = 0;
	DWORD		dwVertexSize = 0;
	DWORD		dwFaceSize = 0;
	INT         iMaxLine = -1;
	geom->iGeomMtrlRef = -1;
	D3DXMatrixIdentity(&geom->m_matWorld);
	if ((iLine = FindToken("NODE_NAME")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp, szTemp);
		geom->strNodeName = DestroyToken(szTemp, "\"");
	}
	if ((iLine = GetLine("NODE_PARENT")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp, szTemp);
		geom->strParentName = DestroyToken(szTemp, "\"");
	}
	if ((iLine = FindToken("TM_ROW0")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f", szTemp, &geom->m_matWorld._11, &geom->m_matWorld._13, &geom->m_matWorld._12);
	}
	if ((iLine = FindToken("TM_ROW1")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f", szTemp, &geom->m_matWorld._31, &geom->m_matWorld._33, &geom->m_matWorld._32);
	}
	if ((iLine = FindToken("TM_ROW2")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f", szTemp, &geom->m_matWorld._21, &geom->m_matWorld._23, &geom->m_matWorld._22);
	}
	if ((iLine = FindToken("TM_ROW3")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f", szTemp, &geom->m_matWorld._41, &geom->m_matWorld._43, &geom->m_matWorld._42);
	}
	if ((iLine = FindToken("MESH")) > 0)
	{
		if ((iLine = FindToken("MESH_NUMVERTEX")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &dwVertexSize);
		}
		if ((iLine = FindToken("MESH_NUMFACES")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &dwFaceSize);
		}
		geom->m_dwFaceSize = dwFaceSize;
		// PosVertex
		if ((iLine = GetLine("MESH_VERTEX_LIST")) > 0)
		{
			geom->VertexPosList.resize(dwVertexSize);
			for (int iVer = 0; iVer < dwVertexSize; iVer++)
			{
				sscanf(m_Tokenlist[iLine + iVer + 1].c_str(), "%s%d%f%f%f", szTemp, &iTemp,
					&geom->VertexPosList[iVer].p[0],
					&geom->VertexPosList[iVer].p[2],
					&geom->VertexPosList[iVer].p[1]);
			}
		}
		// PosIndex
		if ((iLine = FindToken("MESH_FACE_LIST")) > 0)
		{
			geom->IndexPosList.resize(dwFaceSize);
			geom->TriangleList.resize(dwFaceSize);
			for (int iFace = 0; iFace < dwFaceSize; iFace++)
			{
				if ((iLine = GetLine("MESH_FACE")) > 0)
				{
					m_Tokenlist[m_dwTokenIndex];
					sscanf(m_Tokenlist[iLine].c_str(), "%s%s%s%d%s%d%s%d", szTemp, szTemp,
						szTemp, &geom->IndexPosList[iFace].i[0],
						szTemp, &geom->IndexPosList[iFace].i[2],
						szTemp, &geom->IndexPosList[iFace].i[1]);
				}
				if ((iLine = GetLine("MESH_SMOOTHING")) > 0)
				{

				}
				if ((iLine = GetLine("MESH_MTLID")) > 0)
				{
					sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &geom->IndexPosList[iFace].dwSubID);
				}
			}
		}
		// TexVertex
		if ((iLine = FindToken("MESH_NUMTVERTEX")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &dwVertexSize);
		}
		geom->VertexTexList.resize(dwVertexSize);

		if ((iLine = FindToken("MESH_TVERTLIST")) > 0)
		{
			for (int iTex = 0; iTex < dwVertexSize; iTex++)
			{
				sscanf(m_Tokenlist[iLine + iTex + 1].c_str(), "%s%d%f%f", szTemp, &iTemp,
					&geom->VertexTexList[iTex].t[0],
					&geom->VertexTexList[iTex].t[1]);
			}
		}
		// TexIndex
		if ((iLine = FindToken("MESH_NUMTVFACES")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &dwFaceSize);
		}
		geom->IndexTexList.resize(dwFaceSize);
		if ((iLine = FindToken("MESH_TFACELIST")) > 0)
		{
			for (int iFace = 0; iFace < dwFaceSize; iFace++)
			{
				sscanf(m_Tokenlist[iLine + iFace + 1].c_str(), "%s%d%d%d%d", szTemp, &iTemp,
					&geom->IndexTexList[iFace].i[0],
					&geom->IndexTexList[iFace].i[2],
					&geom->IndexTexList[iFace].i[1]);
			}
		}
		// ColVertex
		if ((iLine = FindToken("MESH_NUMCVERTEX")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &dwVertexSize);
		}
		if (dwVertexSize > 0)
		{
			geom->VertexColList.resize(dwVertexSize);
			if ((iLine = FindToken("MESH_CVERTLIST")) > 0 && dwVertexSize > 0)
			{
				for (int iVer = 0; iVer < dwVertexSize; iVer++)
				{
					sscanf(m_Tokenlist[iLine + iVer + 1].c_str(),
						"%s%d%f%f%f", szTemp, &iTemp,
						&geom->VertexColList[iVer].c[0],
						&geom->VertexColList[iVer].c[1],
						&geom->VertexColList[iVer].c[2]);
				}
			}
			// ColIndex
			if ((iLine = FindToken("MESH_NUMCVFACES")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &dwFaceSize);
			}
			geom->IndexColList.resize(dwFaceSize);
			for (int iFace = 0; iFace < dwFaceSize; iFace++)
			{
				sscanf(m_Tokenlist[iLine + iFace + 1].c_str(), "%s%d%d%d%d", szTemp, &iTemp,
					&geom->IndexColList[iFace].i[0],
					&geom->IndexColList[iFace].i[2],
					&geom->IndexColList[iFace].i[1]);
			}
		}
		// Normal
		geom->TriNormalList.resize(dwFaceSize);
		if ((iLine = FindToken("MESH_NORMALS")) > 0)
		{
			for (int iFace = 0; iFace < dwFaceSize; iFace++)
			{
				int iCnt = iLine + iFace * 4 + 1;
				sscanf(m_Tokenlist[iCnt].c_str(), "%s%d%f%f%f", szTemp, &iTemp,
					&geom->TriNormalList[iFace].fn[0],
					&geom->TriNormalList[iFace].fn[2],
					&geom->TriNormalList[iFace].fn[1]);
				for (int iNor = 0; iNor < 3; iNor++)
				{
					sscanf(m_Tokenlist[iCnt + iNor + 1].c_str(), "%s%d%f%f%f", szTemp, &iTemp,
						&geom->TriNormalList[iFace].vn[iNor][0],
						&geom->TriNormalList[iFace].vn[iNor][2],
						&geom->TriNormalList[iFace].vn[iNor][1]);
				}
			}
		}
	}

	int iPrevLine = 0;
	if ((iLine = FindToken("PROP_RECVSHADOW ")) > 0)
	{
	}
	if ((iLine = GetLine("TM_ANIMATION ")) > 0)
	{
		if ((iLine = GetLine("NODE_NAME ")) > 0) {}
		iPrevLine = m_dwTokenIndex;
		if ((iLine = GetLine("CONTROL_POS_TRACK ")) > 0)
		{
			iPrevLine = m_dwTokenIndex;
			while ((iLine = GetLine("CONTROL_POS_SAMPLE ")) > 0)
			{
				AnimTrack* pos = new AnimTrack();
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d%f%f%f", szTemp, &pos->iTick, &pos->vPos.x, &pos->vPos.z, &pos->vPos.y);
				geom->m_pTransTrack.push_back(pos);
				if ((iLine = GetLine("}")) > 0) break;
			}
		}
		if (iLine < 0)
		{
			m_dwTokenIndex = iPrevLine;
		}
		//Rotate
		if ((iLine = GetLine("CONTROL_ROT_TRACK ")) > 0)
		{
			iPrevLine = m_dwTokenIndex;
			while ((iLine = GetLine("CONTROL_ROT_SAMPLE ")) > 0)
			{
				AnimTrack* rot = new AnimTrack();
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d%f%f%f%f", szTemp,
					&rot->iTick,
					&rot->qRot.x,
					&rot->qRot.z,
					&rot->qRot.y,
					&rot->qRot.w);
				geom->m_pRotateTrack.push_back(rot);
				if ((iLine = GetLine("}")) > 0) break;
			}
		}
		if (iLine < 0)
		{
			m_dwTokenIndex = iPrevLine;
		}
		//Scale
		if ((iLine = GetLine("CONTROL_SCALE_TRACK ")) < 0)
		{
			iPrevLine = m_dwTokenIndex;
			while ((iLine = GetLine("CONTROL_SCALE_SAMPLE ")) > 0)
			{
				AnimTrack* scale = new AnimTrack();
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d%f%f%f%f%f%f%f", szTemp,
					&scale->iTick,
					&scale->vPos.x,
					&scale->vPos.z,
					&scale->vPos.y,
					&scale->qRot.x,
					&scale->qRot.z,
					&scale->qRot.y,
					&scale->qRot.w);
				geom->m_pScaleTrack.push_back(scale);
				if ((iLine = GetLine("}")) > 0) break;
			}
		}
		if (iLine < 0)
		{
			m_dwTokenIndex = iPrevLine;
		}
	}
	// MtrlRef
	m_dwTokenIndex--;
	if ((iLine = FindToken("MATERIAL_REF")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &geom->iGeomMtrlRef);
	}

	return m_dwTokenIndex - 1;
}
INT JPaser::LoadHelperObj(ASE_GEOMETRY* geom)
{
	INT iLine;
	char szTemp[256] = { 0, };
	char szParentTemp[256] = { 0, };
	geom->iGeomMtrlRef = -1;
	geom->m_dwFaceSize = 0;
	D3DXMatrixIdentity(&geom->m_matWorld);
	if ((iLine = FindToken("NODE_NAME")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp, szTemp);
		geom->strNodeName = DestroyToken(szTemp, "\"");
	}
	if ((iLine = GetLine("NODE_PARENT")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp, szTemp);
		geom->strParentName = DestroyToken(szTemp, "\"");
	}
	if ((iLine = FindToken("TM_ROW0")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f", szTemp, &geom->m_matWorld._11, &geom->m_matWorld._13, &geom->m_matWorld._12);

	}
	if ((iLine = FindToken("TM_ROW1")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f", szTemp, &geom->m_matWorld._31, &geom->m_matWorld._33, &geom->m_matWorld._32);
	}
	if ((iLine = FindToken("TM_ROW2")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f", szTemp, &geom->m_matWorld._21, &geom->m_matWorld._23, &geom->m_matWorld._22);
	}
	if ((iLine = FindToken("TM_ROW3")) > 0)
	{
		sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f", szTemp, &geom->m_matWorld._41, &geom->m_matWorld._43, &geom->m_matWorld._42);
	}
	if ((iLine = FindToken("BOUNDINGBOX_MIN")) > 0) {}
	if ((iLine = FindToken("BOUNDINGBOX_MAX")) > 0) {}
	int iPrevLine = 0;
	if ((iLine = GetLine("TM_ANIMATION ")) > 0)
	{
		if ((iLine = GetLine("NODE_NAME ")) > 0) {}
		iPrevLine = m_dwTokenIndex;
		if ((iLine = GetLine("CONTROL_POS_TRACK ")) > 0)
		{
			iPrevLine = m_dwTokenIndex;
			while ((iLine = GetLine("CONTROL_POS_SAMPLE ")) > 0)
			{
				AnimTrack* pos = new AnimTrack();
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d%f%f%f", szTemp, &pos->iTick, &pos->vPos.x, &pos->vPos.z, &pos->vPos.y);
				geom->m_pTransTrack.push_back(pos);
				if ((iLine = GetLine("}")) > 0) break;
			}
		}
		if (iLine < 0)
		{
			m_dwTokenIndex = iPrevLine;
		}
		//Rotate
		if ((iLine = GetLine("CONTROL_ROT_TRACK ")) > 0)
		{
			iPrevLine = m_dwTokenIndex;
			while ((iLine = GetLine("CONTROL_ROT_SAMPLE ")) > 0)
			{
				AnimTrack* rot = new AnimTrack();
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d%f%f%f%f", szTemp,
					&rot->iTick,
					&rot->qRot.x,
					&rot->qRot.z,
					&rot->qRot.y,
					&rot->qRot.w);
				geom->m_pRotateTrack.push_back(rot);
				if ((iLine = GetLine("}")) > 0) break;
			}
		}
		if (iLine < 0)
		{
			m_dwTokenIndex = iPrevLine;
		}
		//Scale
		if ((iLine = GetLine("CONTROL_SCALE_TRACK ")) < 0)
		{
			iPrevLine = m_dwTokenIndex;
			while ((iLine = GetLine("CONTROL_SCALE_SAMPLE ")) > 0)
			{
				AnimTrack* scale = new AnimTrack();
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d%f%f%f%f%f%f%f", szTemp,
					&scale->iTick,
					&scale->vPos.x,
					&scale->vPos.z,
					&scale->vPos.y,
					&scale->qRot.x,
					&scale->qRot.z,
					&scale->qRot.y,
					&scale->qRot.w);
				geom->m_pScaleTrack.push_back(scale);
				if ((iLine = GetLine("}")) > 0) break;
			}
		}
		if (iLine < 0)
		{
			m_dwTokenIndex = iPrevLine;
		}
	}
	return m_dwTokenIndex - 1;
}
bool JPaser::SetAnimation(ASE_GEOMETRY* geom)
{
	AnimTrack* pPrevTrack = NULL;
	for (int iTrack = 0; iTrack < geom->m_pTransTrack.size(); iTrack++)
	{
		AnimTrack* pTrack = new AnimTrack;
		pTrack->iTick = geom->m_pTransTrack[iTrack]->iTick;
		pTrack->vPos = geom->m_pTransTrack[iTrack]->vPos;

		pPrevTrack = SetDoublyLinkedList(pTrack, pPrevTrack);
		geom->m_pTransTrack[iTrack] = pTrack;
	}
	pPrevTrack = NULL;
	for (int iTrack = 0; iTrack < geom->m_pRotateTrack.size(); iTrack++)
	{
		AnimTrack* pTrack = new AnimTrack;

		pTrack->iTick = geom->m_pRotateTrack[iTrack]->iTick;

		D3DXQuaternionRotationAxis(&pTrack->qRot,
			&D3DXVECTOR3(geom->m_pRotateTrack[iTrack]->qRot.x,
				geom->m_pRotateTrack[iTrack]->qRot.y,
				geom->m_pRotateTrack[iTrack]->qRot.z),
			geom->m_pRotateTrack[iTrack]->qRot.w);
		if (pPrevTrack != NULL)
		{
			D3DXQuaternionMultiply(&pTrack->qRot, &pPrevTrack->qRot, &pTrack->qRot);
		}
		pPrevTrack = SetDoublyLinkedList(pTrack, pPrevTrack);
		geom->m_pRotateTrack[iTrack] = pTrack;
	}
	pPrevTrack = NULL;
	for (int iTrack = 0; iTrack < geom->m_pScaleTrack.size(); iTrack++)
	{
		AnimTrack* pTrack = new AnimTrack;
		pTrack->iTick = geom->m_pScaleTrack[iTrack]->iTick;
		pTrack->vPos = geom->m_pScaleTrack[iTrack]->vPos;

		D3DXQuaternionRotationAxis(&pTrack->qRot,
			&D3DXVECTOR3(geom->m_pScaleTrack[iTrack]->qRot.x,
				geom->m_pScaleTrack[iTrack]->qRot.y,
				geom->m_pScaleTrack[iTrack]->qRot.z),
			geom->m_pScaleTrack[iTrack]->qRot.w);
		pPrevTrack = SetDoublyLinkedList(pTrack, pPrevTrack);
		geom->m_pScaleTrack[iTrack] = pTrack;
	}
	return true;
}
bool JPaser::GenTriangle(ASE_GEOMETRY* geom)
{
	for (int iTri = 0; iTri < geom->m_dwFaceSize; iTri++)
	{
		for (int iVer = 0; iVer < 3; iVer++)
		{
			if (geom->VertexPosList.size() > 0)
			{
				geom->TriangleList[iTri].v[iVer].p[0] = geom->VertexPosList[geom->IndexPosList[iTri].i[iVer]].p[0];
				geom->TriangleList[iTri].v[iVer].p[1] = geom->VertexPosList[geom->IndexPosList[iTri].i[iVer]].p[1];
				geom->TriangleList[iTri].v[iVer].p[2] = geom->VertexPosList[geom->IndexPosList[iTri].i[iVer]].p[2];
				geom->TriangleList[iTri].dwSubID = geom->IndexPosList[iTri].dwSubID;
			}

			if (geom->TriNormalList.size() > 0)
			{
				geom->TriangleList[iTri].v[iVer].n[0] = geom->TriNormalList[iTri].vn[iVer][0];
				geom->TriangleList[iTri].v[iVer].n[1] = geom->TriNormalList[iTri].vn[iVer][1];
				geom->TriangleList[iTri].v[iVer].n[2] = geom->TriNormalList[iTri].vn[iVer][2];
			}

			geom->TriangleList[iTri].v[iVer].c[0] = 1.0f;
			geom->TriangleList[iTri].v[iVer].c[1] = 1.0f;
			geom->TriangleList[iTri].v[iVer].c[2] = 1.0f;
			geom->TriangleList[iTri].v[iVer].c[3] = 1.0f;

			if (geom->VertexColList.size() > 0)
			{
				geom->TriangleList[iTri].v[iVer].c[0] = geom->VertexPosList[geom->IndexColList[iTri].i[iVer]].c[0];
				geom->TriangleList[iTri].v[iVer].c[1] = geom->VertexPosList[geom->IndexColList[iTri].i[iVer]].c[1];
				geom->TriangleList[iTri].v[iVer].c[2] = geom->VertexPosList[geom->IndexColList[iTri].i[iVer]].c[2];
				geom->TriangleList[iTri].v[iVer].c[3] = 1.0f;
			}

			if (geom->VertexTexList.size() > 0)
			{
				geom->TriangleList[iTri].v[iVer].t[0] = geom->VertexTexList[geom->IndexTexList[iTri].i[iVer]].t[0];
				geom->TriangleList[iTri].v[iVer].t[1] = 1.0f - geom->VertexTexList[geom->IndexTexList[iTri].i[iVer]].t[1];
			}
		}
	}
	return true;
}
bool JPaser::Convert()
{
	for (int iGeom = 0; iGeom < m_Geom.size(); iGeom++)
	{
		JMesh* pMesh = new JMesh();
		pMesh->m_strNodeName = m_Geom[iGeom]->strNodeName;
		pMesh->m_strParentName = m_Geom[iGeom]->strParentName;
		pMesh->m_matAseWorld = m_Geom[iGeom]->m_matWorld;
		pMesh->m_pTransTrack = m_Geom[iGeom]->m_pTransTrack;
		pMesh->m_pRotateTrack = m_Geom[iGeom]->m_pRotateTrack;
		pMesh->m_pScaleTrack = m_Geom[iGeom]->m_pScaleTrack;
		D3DXMatrixIdentity(&pMesh->m_matCalc);
		for (int iTri = 0; iTri < m_Geom[iGeom]->TriangleList.size(); iTri++)
		{
			int iRef = m_Geom[iGeom]->iGeomMtrlRef;
			int iSubMtrlID = m_Geom[iGeom]->TriangleList[iTri].dwSubID;
			if (iRef >= 0 && iSubMtrlID < m_Mtrl[iRef].subMtrl.size())
			{
				ASE_TRIANGLE sTri = m_Geom[iGeom]->TriangleList[iTri];
				pMesh->m_pSubMeshList.resize(m_Mtrl[iRef].subMtrl.size());
				pMesh->m_pSubMeshList[iSubMtrlID].m_pTriangleList.push_back(sTri);
				pMesh->m_pSubMeshList[iSubMtrlID].m_pTexName = m_Mtrl[iRef].subMtrl[iSubMtrlID].tex[0].strTexName;
			}
		}
		for (int iSubMesh = 0; iSubMesh < pMesh->m_pSubMeshList.size(); iSubMesh++)
		{
			for (int iTri = 0; iTri < pMesh->m_pSubMeshList[iSubMesh].m_pTriangleList.size(); iTri++)
			{
				pMesh->m_pSubMeshList[iSubMesh].m_pVertexList.push_back(pMesh->m_pSubMeshList[iSubMesh].m_pTriangleList[iTri].v[0]);
				pMesh->m_pSubMeshList[iSubMesh].m_pVertexList.push_back(pMesh->m_pSubMeshList[iSubMesh].m_pTriangleList[iTri].v[1]);
				pMesh->m_pSubMeshList[iSubMesh].m_pVertexList.push_back(pMesh->m_pSubMeshList[iSubMesh].m_pTriangleList[iTri].v[2]);

				pMesh->m_pSubMeshList[iSubMesh].m_pIndexList.push_back(iTri * 3 + 0);
				pMesh->m_pSubMeshList[iSubMesh].m_pIndexList.push_back(iTri * 3 + 2);
				pMesh->m_pSubMeshList[iSubMesh].m_pIndexList.push_back(iTri * 3 + 1);
			}
		}
		m_pMeshList.push_back(pMesh);
	}
	for (int iMesh = 0; iMesh < m_pMeshList.size(); iMesh++)
	{
		JMesh* pParent = GetParent(m_pMeshList[iMesh]);
		m_pMeshList[iMesh]->m_pParent = pParent;
		D3DXMATRIX matInvParent;
		D3DXMatrixIdentity(&matInvParent);

		if (m_pMeshList[iMesh]->m_pParent)
		{
			D3DXMatrixInverse(&matInvParent, NULL, &m_pMeshList[iMesh]->m_pParent->m_matAseWorld);
		}
		// 분해된 월드행렬 -> 부모가 빠진 LocalWorld
		m_pMeshList[iMesh]->m_matLocalWorld = m_pMeshList[iMesh]->m_matAseWorld * matInvParent;

		D3DXVECTOR3 v3Pos, v3Scale;
		D3DXQUATERNION q;
		D3DXMatrixDecompose(&v3Scale, &q, &v3Pos, &m_pMeshList[iMesh]->m_matLocalWorld);
		D3DXMatrixScaling(&m_pMeshList[iMesh]->m_matLocalScale, v3Scale.x, v3Scale.y, v3Scale.z);
		D3DXMatrixTranslation(&m_pMeshList[iMesh]->m_matLocalTrans, v3Pos.x, v3Pos.y, v3Pos.z);
		D3DXMatrixRotationQuaternion(&m_pMeshList[iMesh]->m_matLocalRotate, &q);

		//D3DXMATRIX matInvLocalWorld;
		//D3DXMatrixIdentity(&matInvLocalWorld);
		//D3DXMatrixInverse(&matInvLocalWorld, NULL, &m_pMeshList[iMesh]->m_matLocalWorld);
		//matInvLocalWorld = matInvParent * matInvLocalWorld;

		/* (InvParent * InvLocalWorld(Not Parent) * AllVertex) */
		D3DXMatrixInverse(&m_pMeshList[iMesh]->m_matLocalWorld, NULL, &m_pMeshList[iMesh]->m_matAseWorld);
		for (int iSubMesh = 0; iSubMesh < m_pMeshList[iMesh]->m_pSubMeshList.size(); iSubMesh++)
		{
			for (int iver = 0; iver < m_pMeshList[iMesh]->m_pSubMeshList[iSubMesh].m_pVertexList.size(); iver++)
			{
				D3DXVECTOR3 v = m_pMeshList[iMesh]->m_pSubMeshList[iSubMesh].m_pVertexList[iver].p;
				D3DXVec3TransformCoord(&m_pMeshList[iMesh]->m_pSubMeshList[iSubMesh].m_pVertexList[iver].p, &v, &m_pMeshList[iMesh]->m_matLocalWorld);
			}
		}
	}
	return true;
}
JMesh* JPaser::GetParent(JMesh* pMesh)
{
	for (int iMesh = 0; iMesh < m_pMeshList.size(); iMesh++)
	{
		if (m_pMeshList[iMesh]->m_strNodeName == pMesh->m_strParentName)
		{
			return m_pMeshList[iMesh];
		}
	}
	return NULL;
}
JPaser::JPaser()
{

}


JPaser::~JPaser()
{
}
