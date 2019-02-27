#include "JPaser.h"
TRACK* JPaser::SetDoublyLinkedList(TRACK* pCurrentTrack, TRACK* pPrev)
{
	if (pPrev)
	{
		pPrev->NextTrack = pCurrentTrack;
		pCurrentTrack->PrevTrack = pPrev;
	}
	return pCurrentTrack;
}
bool JPaser::Load()
{
	if (!LoadScene()) return false;
	if (!LoadMaterial()) return false;
	if (!LoadGeom()) return false;
	if (!Convert())return false;
	return true;
}
vector<TRACK*> JPaser::GetPos()
{
	return m_pTrasTrack;
}
vector<TRACK*> JPaser::GetRot()
{
	return m_pRotateTrack;
}
vector<TRACK*> JPaser::GetScl()
{
	return m_pScaleTrack;
}
vector<MeshData> JPaser::GetData()
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
	m_Geom.IndexColList.clear();
	m_Geom.IndexPosList.clear();
	m_Geom.IndexTexList.clear();
	m_Geom.strNodeName.clear();
	m_Geom.TriangleList.clear();
	m_Geom.TriNormalList.clear();
	m_Geom.VertexColList.clear();
	m_Geom.VertexPosList.clear();
	m_Geom.VertexTexList.clear();
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
				//=====SubMtrl=====
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
							if ((iLine = FindToken("MAP_DIFFUSE")) > 0)
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
	return true;
}
bool JPaser::LoadGeom()
{
	INT			iLine = 0;
	char		szTemp[256] = { 0, };
	int			iTemp = 0;
	DWORD		dwVertexSize = 0;
	DWORD		dwFaceSize = 0;

	if ((iLine = FindToken("GEOMOBJECT")) > 0)
	{
		if ((iLine = FindToken("NODE_NAME")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%s", szTemp, szTemp);
			m_Geom.strNodeName = DestroyToken(szTemp, "\"");
		}
		if ((iLine = FindToken("TM_ROW0")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f", szTemp, &matWorld._11, &matWorld._13, &matWorld._12);
		}
		if ((iLine = FindToken("TM_ROW1")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f", szTemp, &matWorld._31, &matWorld._33, &matWorld._32);
		}
		if ((iLine = FindToken("TM_ROW2")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f", szTemp, &matWorld._21, &matWorld._23, &matWorld._22);
		}
		if ((iLine = FindToken("TM_ROW3")) > 0)
		{
			sscanf(m_Tokenlist[iLine].c_str(), "%s%f%f%f", szTemp, &matWorld._41, &matWorld._43, &matWorld._42);
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
				m_dwFaceSize = dwFaceSize;
				// PosVertex
				if ((iLine = FindToken("MESH_VERTEX_LIST")) > 0)
				{
					m_Geom.VertexPosList.resize(dwVertexSize);
					for (int iVer = 0; iVer < dwVertexSize; iVer++)
					{
						sscanf(m_Tokenlist[iLine + iVer + 1].c_str(), "%s%d%f%f%f", szTemp, &iTemp,
							&m_Geom.VertexPosList[iVer].p[0],
							&m_Geom.VertexPosList[iVer].p[2],
							&m_Geom.VertexPosList[iVer].p[1]);
					}
				}
				// PosIndex
				if ((iLine = FindToken("MESH_FACE_LIST")) > 0)
				{
					m_Geom.IndexPosList.resize(dwFaceSize);
					m_Geom.TriangleList.resize(dwFaceSize);
					for (int iFace = 0; iFace < dwFaceSize; iFace++)
					{
						sscanf(m_Tokenlist[iLine + 1].c_str(), "%s%s%s%d%s%d%s%d", szTemp, szTemp,
							szTemp, &m_Geom.IndexPosList[iFace].i[0],
							szTemp, &m_Geom.IndexPosList[iFace].i[2],
							szTemp, &m_Geom.IndexPosList[iFace].i[1]);
						if ((iLine = FindToken("MESH_MTLID")) > 0)
						{
							sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &m_Geom.IndexPosList[iFace].dwSubID);
						}
					}
				}
				// TexVertex
				if ((iLine = FindToken("MESH_NUMTVERTEX")) > 0)
				{
					sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &dwVertexSize);
				}
				m_Geom.VertexTexList.resize(dwVertexSize);

				if ((iLine = FindToken("MESH_TVERTLIST")) > 0)
				{
					for (int iTex = 0; iTex < dwVertexSize; iTex++)
					{
						sscanf(m_Tokenlist[iLine + iTex + 1].c_str(), "%s%d%f%f", szTemp, &iTemp,
							&m_Geom.VertexTexList[iTex].t[0],
							&m_Geom.VertexTexList[iTex].t[1]);
					}
				}
				// TexIndex
				if ((iLine = FindToken("MESH_NUMTVFACES")) > 0)
				{
					sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &dwFaceSize);
				}
				m_Geom.IndexTexList.resize(dwFaceSize);
				if ((iLine = FindToken("MESH_TFACELIST")) > 0)
				{
					for (int iFace = 0; iFace < dwFaceSize; iFace++)
					{
						sscanf(m_Tokenlist[iLine + iFace + 1].c_str(), "%s%d%d%d%d", szTemp, &iTemp,
							&m_Geom.IndexTexList[iFace].i[0],
							&m_Geom.IndexTexList[iFace].i[2],
							&m_Geom.IndexTexList[iFace].i[1]);
					}
				}
				// ColVertex
				if ((iLine = FindToken("MESH_NUMCVERTEX")) > 0)
				{
					sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &dwVertexSize);
				}
				if (dwVertexSize > 0)
				{
					m_Geom.VertexColList.resize(dwVertexSize);
					if ((iLine = FindToken("MESH_CVERTLIST")) > 0 && dwVertexSize > 0)
					{
						for (int iVer = 0; iVer < dwVertexSize; iVer++)
						{
							sscanf(m_Tokenlist[iLine + iVer + 1].c_str(),
								"%s%d%f%f%f", szTemp, &iTemp,
								&m_Geom.VertexColList[iVer].c[0],
								&m_Geom.VertexColList[iVer].c[1],
								&m_Geom.VertexColList[iVer].c[2]);
						}
					}
					// ColIndex
					if ((iLine = FindToken("MESH_NUMCVFACES")) > 0)
					{
						sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &dwFaceSize);
					}
					m_Geom.IndexColList.resize(dwFaceSize);
					for (int iFace = 0; iFace < dwFaceSize; iFace++)
					{
						sscanf(m_Tokenlist[iLine + iFace + 1].c_str(), "%s%d%d%d%d", szTemp, &iTemp,
							&m_Geom.IndexColList[iFace].i[0],
							&m_Geom.IndexColList[iFace].i[2],
							&m_Geom.IndexColList[iFace].i[1]);
					}
				}
				// Normal
				m_Geom.TriNormalList.resize(dwFaceSize);
				if ((iLine = FindToken("MESH_NORMALS")) > 0)
				{
					for (int iFace = 0; iFace < dwFaceSize; iFace++)
					{
						int iCnt = iLine + iFace * 4 + 1;
						sscanf(m_Tokenlist[iCnt].c_str(), "%s%d%f%f%f", szTemp, &iTemp,
							&m_Geom.TriNormalList[iFace].fn[0],
							&m_Geom.TriNormalList[iFace].fn[2],
							&m_Geom.TriNormalList[iFace].fn[1]);
						for (int iNor = 0; iNor < 3; iNor++)
						{
							sscanf(m_Tokenlist[iCnt + iNor + 1].c_str(), "%s%d%f%f%f", szTemp, &iTemp,
								&m_Geom.TriNormalList[iFace].vn[iNor][0],
								&m_Geom.TriNormalList[iFace].vn[iNor][2],
								&m_Geom.TriNormalList[iFace].vn[iNor][1]);
						}
					}
				}
				// anim
				int iPrevLine = 0;
				if ((iLine = FindToken("TM_ANIMATION ")) > 0)
				{

					if ((iLine = FindToken("CONTROL_POS_TRACK ")) > 0)
					{
						iPrevLine = iLine;
					}
					while ((iLine = FindToken("CONTROL_POS_SAMPLE ")) > 0)
					{
						TRACK* pos = new TRACK();
						sscanf(m_Tokenlist[iLine].c_str(), "%s%d%f%f%f", szTemp, &pos->iTick, &pos->vPos.x, &pos->vPos.z, &pos->vPos.y);
						m_pPos.push_back(pos);
					}
					if (iLine < 0)
					{
						m_dwTokenIndex = iPrevLine;
					}

					//Rotate

					if ((iLine = FindToken("CONTROL_ROT_TRACK ")) > 0)
					{
						iPrevLine = iLine;
					}
					while ((iLine = FindToken("CONTROL_ROT_SAMPLE ")) > 0)
					{
						TRACK* rot = new TRACK();
						sscanf(m_Tokenlist[iLine].c_str(), "%s%d%f%f%f%f", szTemp, 
							&rot->iTick, 
							&rot->qRot.x, 
							&rot->qRot.z, 
							&rot->qRot.y, 
							&rot->qRot.w);
						m_pRot.push_back(rot);
					}
					if (iLine < 0)
					{
						m_dwTokenIndex = iPrevLine;
					}

					//Scale

					if ((iLine = FindToken("CONTROL_SCALE_TRACK ")) > 0)
					{
						iPrevLine = iLine;
					}
					while ((iLine = FindToken("CONTROL_SCALE_SAMPLE ")) > 0)
					{
						TRACK* scale = new TRACK();
						sscanf(m_Tokenlist[iLine].c_str(), "%s%d%f%f%f%f%f%f%f", szTemp, 
							&scale->iTick, 
							&scale->vPos.x, 
							&scale->vPos.z, 
							&scale->vPos.y, 
							&scale->qRot.x, 
							&scale->qRot.z, 
							&scale->qRot.y, 
							&scale->qRot.w);
						m_pScale.push_back(scale);
					}
					if (iLine < 0)
					{
						m_dwTokenIndex = iPrevLine;
					}
				}

				// MtrlRef
				if ((iLine = FindToken("MATERIAL_REF")) > 0)
				{
					sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &m_Geom.iGeomMtrlRef);
				}
				// Gen Triangle
				GenTriangle();
			}
		}
	}

	return true;
}
const char* JPaser::GetNextToken()
{
	m_CurrentToken = m_Tokenlist[m_dwTokenIndex++];
	return m_CurrentToken.c_str();
}
INT JPaser::FindToken(string szToken)
{
	int EndLine = m_dwMaxTokenLine;
	INT retIndex = -1;
	while (EndLine > m_dwTokenIndex)
	{
		GetNextToken();
		if (NULL != strstr(m_CurrentToken.c_str(), szToken.c_str()))
		{
			retIndex = m_dwTokenIndex - 1;
			break;
		}
	}
	if (EndLine < m_dwTokenIndex) return -1;
	return retIndex;
}
bool JPaser::LoadAseFile(const TCHAR* AseFileName)
{
	HANDLE hRead = CreateFile(AseFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hRead == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hRead);
		return false;
	}

	GetFileSizeEx(hRead, &m_lFileSize);
	m_pData = new char[m_lFileSize.QuadPart];

	if (m_pData == NULL)
	{
		SAFE_DELETE(m_pData);
		CloseHandle(hRead);
		return false;
	}

	if (FALSE == ReadFile(hRead, m_pData, m_lFileSize.QuadPart, 0, 0))
	{
		SAFE_DELETE(m_pData);
		CloseHandle(hRead);
		return false;
	}
	CloseHandle(hRead);

	if (m_pData == NULL) return false;
	string pData = m_pData;
	string strToken = "*";
	size_t start = pData.find_first_not_of(strToken);
	size_t end = pData.find_first_of(strToken, start);
	for (; start < pData.size(); start = pData.find_first_not_of(strToken, end))
	{
		end = pData.find_first_of(strToken, start);

		string Token = pData.substr(start, end - start);
		m_Tokenlist.push_back(Token);
	}
	m_dwMaxTokenLine = m_Tokenlist.size();
	return true;
}
string JPaser::DestroyToken(const char* szName, const char* szToken)
{
	string pData = szName;
	string strToken = szToken;
	size_t start = pData.find_first_not_of(strToken);
	size_t end = pData.find_first_of(strToken, start);
	string retData = pData.substr(start, end - 1);
	return retData;
}
string JPaser::DestroyTokenName(const char* szName, const char* szToken)
{
	string pData = szName;
	string strToken = szToken;
	size_t start = pData.find_first_of(strToken);
	size_t end = pData.find_last_of(strToken);
	string retData = pData.substr(start, end - 1);
	return DestroyToken(retData.c_str(), szToken);
}
string JPaser::DividePath(const char* pszFileName)
{
	char RetData[MAX_PATH] = { 0, };
	char Drive[MAX_PATH] = { 0, };
	char Dir[MAX_PATH] = { 0, };
	char FileName[MAX_PATH] = { 0, };
	char Ext[MAX_PATH] = { 0, };
	string Ret;
	if (pszFileName != NULL)
	{
		_splitpath_s(pszFileName, Drive, Dir, FileName, Ext);
		sprintf_s(RetData, "%s%s", FileName, Ext);
		Ret = RetData;
		return Ret;
	}
	return NULL;
}
void JPaser::GenTriangle()
{
	for (int iTri = 0; iTri < m_dwFaceSize; iTri++)
	{
		for (int iVer = 0; iVer < 3; iVer++)
		{
			if (m_Geom.VertexPosList.size() > 0)
			{
				m_Geom.TriangleList[iTri].v[iVer].p[0] = m_Geom.VertexPosList[m_Geom.IndexPosList[iTri].i[iVer]].p[0];
				m_Geom.TriangleList[iTri].v[iVer].p[1] = m_Geom.VertexPosList[m_Geom.IndexPosList[iTri].i[iVer]].p[1];
				m_Geom.TriangleList[iTri].v[iVer].p[2] = m_Geom.VertexPosList[m_Geom.IndexPosList[iTri].i[iVer]].p[2];
				m_Geom.TriangleList[iTri].dwSubID = m_Geom.IndexPosList[iTri].dwSubID;
			}

			if (m_Geom.TriNormalList.size() > 0)
			{
				m_Geom.TriangleList[iTri].v[iVer].n[0] = m_Geom.TriNormalList[iTri].vn[iVer][0];
				m_Geom.TriangleList[iTri].v[iVer].n[1] = m_Geom.TriNormalList[iTri].vn[iVer][1];
				m_Geom.TriangleList[iTri].v[iVer].n[2] = m_Geom.TriNormalList[iTri].vn[iVer][2];
			}

			m_Geom.TriangleList[iTri].v[iVer].c[0] = 1.0f;
			m_Geom.TriangleList[iTri].v[iVer].c[1] = 1.0f;
			m_Geom.TriangleList[iTri].v[iVer].c[2] = 1.0f;
			m_Geom.TriangleList[iTri].v[iVer].c[3] = 1.0f;

			if (m_Geom.VertexColList.size() > 0)
			{
				m_Geom.TriangleList[iTri].v[iVer].c[0] = m_Geom.VertexPosList[m_Geom.IndexColList[iTri].i[iVer]].c[0];
				m_Geom.TriangleList[iTri].v[iVer].c[1] = m_Geom.VertexPosList[m_Geom.IndexColList[iTri].i[iVer]].c[1];
				m_Geom.TriangleList[iTri].v[iVer].c[2] = m_Geom.VertexPosList[m_Geom.IndexColList[iTri].i[iVer]].c[2];
				m_Geom.TriangleList[iTri].v[iVer].c[3] = 1.0f;
			}

			if (m_Geom.VertexTexList.size() > 0)
			{
				m_Geom.TriangleList[iTri].v[iVer].t[0] = m_Geom.VertexTexList[m_Geom.IndexTexList[iTri].i[iVer]].t[0];
				m_Geom.TriangleList[iTri].v[iVer].t[1] = 1.0f - m_Geom.VertexTexList[m_Geom.IndexTexList[iTri].i[iVer]].t[1];
			}
		}
	}
	m_pMeshList.resize(m_Mtrl.size());
	for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
	{
		if (m_Mtrl[iMtrl].subMtrl.size() > 0)
		{
			TriangleSubID();
		}
		else
		{
			for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
			{
				m_pMeshList[iMtrl].m_pSubMeshList.resize(1);
				for (int iVer = 0; iVer < m_dwFaceSize; iVer++)
				{
					m_pMeshList[iMtrl].m_pSubMeshList[iMtrl].m_pTriangleList.push_back(m_Geom.TriangleList[iVer]);
					m_pMeshList[iMtrl].m_pSubMeshList[iMtrl].m_pTexName = m_Mtrl[iMtrl].tex[0].strTexName;
				}
			}
		}
	}
}
bool JPaser::TriangleSubID()
{
	for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
	{
		m_pMeshList[iMtrl].m_pSubMeshList.resize(m_Mtrl[iMtrl].subMtrl.size());
		for (int iSubMtrl = 0; iSubMtrl < m_Mtrl[iMtrl].subMtrl.size(); iSubMtrl++)
		{
			for (int iVer = 0; iVer < m_dwFaceSize; iVer++)
			{
				if (m_Geom.TriangleList[iVer].dwSubID == iSubMtrl)
				{
					m_pMeshList[iMtrl].m_pSubMeshList[iSubMtrl].m_pTriangleList.push_back(m_Geom.TriangleList[iVer]);
				}
			}
			m_pMeshList[iMtrl].m_pSubMeshList[iSubMtrl].m_pTexName = m_Mtrl[iMtrl].subMtrl[iSubMtrl].tex[0].strTexName;
		}
	}
	return true;
}
bool JPaser::Convert()
{
	for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
	{
		for (int iSubMtrl = 0; iSubMtrl < m_Mtrl[iMtrl].subMtrl.size(); iSubMtrl++)
		{
			for (int iTri = 0; iTri < m_pMeshList[iMtrl].m_pSubMeshList[iSubMtrl].m_pTriangleList.size(); iTri++)
			{
				m_pMeshList[iMtrl].m_pSubMeshList[iSubMtrl].m_pVertexList.push_back(m_pMeshList[iMtrl].m_pSubMeshList[iSubMtrl].m_pTriangleList[iTri].v[0]);
				m_pMeshList[iMtrl].m_pSubMeshList[iSubMtrl].m_pVertexList.push_back(m_pMeshList[iMtrl].m_pSubMeshList[iSubMtrl].m_pTriangleList[iTri].v[1]);
				m_pMeshList[iMtrl].m_pSubMeshList[iSubMtrl].m_pVertexList.push_back(m_pMeshList[iMtrl].m_pSubMeshList[iSubMtrl].m_pTriangleList[iTri].v[2]);

				m_pMeshList[iMtrl].m_pSubMeshList[iSubMtrl].m_pIndexList.push_back(iTri * 3 + 0);
				m_pMeshList[iMtrl].m_pSubMeshList[iSubMtrl].m_pIndexList.push_back(iTri * 3 + 2);
				m_pMeshList[iMtrl].m_pSubMeshList[iSubMtrl].m_pIndexList.push_back(iTri * 3 + 1);
			}
		}
		if (m_Mtrl[iMtrl].subMtrl.size() <= 0)
		{
			for (int iTri = 0; iTri < m_pMeshList[iMtrl].m_pSubMeshList[iMtrl].m_pTriangleList.size(); iTri++)
			{
				m_pMeshList[iMtrl].m_pSubMeshList[0].m_pVertexList.push_back(m_pMeshList[iMtrl].m_pSubMeshList[0].m_pTriangleList[iTri].v[0]);
				m_pMeshList[iMtrl].m_pSubMeshList[0].m_pVertexList.push_back(m_pMeshList[iMtrl].m_pSubMeshList[0].m_pTriangleList[iTri].v[1]);
				m_pMeshList[iMtrl].m_pSubMeshList[0].m_pVertexList.push_back(m_pMeshList[iMtrl].m_pSubMeshList[0].m_pTriangleList[iTri].v[2]);

				m_pMeshList[iMtrl].m_pSubMeshList[0].m_pIndexList.push_back(iTri * 3 + 0);
				m_pMeshList[iMtrl].m_pSubMeshList[0].m_pIndexList.push_back(iTri * 3 + 2);
				m_pMeshList[iMtrl].m_pSubMeshList[0].m_pIndexList.push_back(iTri * 3 + 1);
			}
		}
	}


	// 에니메이션 트랙 복사		
	TRACK* pPrevTrack = NULL;
	for (int iTrack = 0; iTrack < m_pPos.size(); iTrack++)
	{
		TRACK* pTrack = new TRACK;
		pTrack->iTick = m_pPos[iTrack]->iTick;
		pTrack->vPos = m_pPos[iTrack]->vPos;

		pPrevTrack = SetDoublyLinkedList(pTrack, pPrevTrack);
		m_pTrasTrack.push_back(pTrack);
	}

	pPrevTrack = NULL;
	for (int iTrack = 0; iTrack < m_pRot.size(); iTrack++)
	{
		TRACK* pTrack = new TRACK;

		pTrack->iTick = m_pRot[iTrack]->iTick;

		// 임의의 축과 각을 쿼터니언으로 변환			
		D3DXQuaternionRotationAxis(&pTrack->qRot, &D3DXVECTOR3(
			m_pRot[iTrack]->qRot.x,
			m_pRot[iTrack]->qRot.y,
			m_pRot[iTrack]->qRot.z),
			m_pRot[iTrack]->qRot.w);
		// 이전트랙의 쿼터니온과 누적시킴.			
		if (pPrevTrack != NULL)
		{
			D3DXQuaternionMultiply(&pTrack->qRot, &pPrevTrack->qRot, &pTrack->qRot);
		}

		pPrevTrack = SetDoublyLinkedList(pTrack, pPrevTrack);

		m_pRotateTrack.push_back(pTrack);
	}

	pPrevTrack = NULL;
	for (int iTrack = 0; iTrack < m_pScale.size(); iTrack++)
	{
		TRACK* pTrack = new TRACK;

		pTrack->iTick = m_pScale[iTrack]->iTick;
		pTrack->vPos = m_pScale[iTrack]->vPos;

		// 임의의 축과 각을 쿼터니언으로 변환			
		D3DXQuaternionRotationAxis(&pTrack->qRot,
			&D3DXVECTOR3(m_pScale[iTrack]->qRot.x,
						 m_pScale[iTrack]->qRot.y,
				         m_pScale[iTrack]->qRot.z),
						 m_pScale[iTrack]->qRot.w);

		pPrevTrack = SetDoublyLinkedList(pTrack, pPrevTrack);

		m_pScaleTrack.push_back(pTrack);
	}
	return true;
}
JPaser::JPaser()
{
	//D3DXMatrixIdentity(&m_Geom.matWorld);
}


JPaser::~JPaser()
{
}
