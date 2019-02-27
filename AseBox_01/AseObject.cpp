#include "AseObject.h"
vector<DWORD> AseObject::SetIndex(vector<ASE_TRIANGLE> pData)
{
	AseObject::m_Geom.TriangleList;
	vector<DWORD> index;
	for (int i = 0; i < pData.size(); i++)
	{
		index.push_back(i * 3 + 0);
		index.push_back(i * 3 + 2);
		index.push_back(i * 3 + 1);
	}
	return index;
}
bool AseObject::Init()
{
	for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
	{
		if (m_Mtrl[iMtrl].subMtrl.size() > 0)
		{
			for (int iSubMtrl = 0; iSubMtrl < m_Mtrl[iMtrl].subMtrl.size(); iSubMtrl++)
			{
				//Vertex
				m_SubAseObj[iSubMtrl].m_pVertexList = CutTriangle(m_SubAseObj[iSubMtrl].m_Geom.TriangleList);
				//vector<ASE_VERTEX> vertices = m_Geom.VertexPosList;
				m_SubAseObj[iSubMtrl].m_dxObj.m_iVertexNum = m_SubAseObj[iSubMtrl].m_pVertexList.size();
				m_SubAseObj[iSubMtrl].m_dxObj.m_iVertexSize = sizeof(ASE_VERTEX);


				//vector<DWORD> indices = CutIndex(m_Geom.IndexPosList);
				m_SubAseObj[iSubMtrl].m_pIndexList = SetIndex(m_SubAseObj[iSubMtrl].m_Geom.TriangleList);
				m_SubAseObj[iSubMtrl].m_dxObj.m_iIndexNum = m_SubAseObj[iSubMtrl].m_pIndexList.size();
				m_SubAseObj[iSubMtrl].m_dxObj.m_iIndexSize = sizeof(DWORD);

				m_SubAseObj[iSubMtrl].m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, 
					&m_SubAseObj[iSubMtrl].m_pVertexList.at(0), 
					m_SubAseObj[iSubMtrl].m_dxObj.m_iVertexSize, 
					m_SubAseObj[iSubMtrl].m_dxObj.m_iVertexNum);
				m_SubAseObj[iSubMtrl].m_dxObj.m_pIndexBuffer = CreateIndexBuffer(g_pd3dDevice, 
					&m_SubAseObj[iSubMtrl].m_pIndexList.at(0), 
					m_SubAseObj[iSubMtrl].m_dxObj.m_iIndexSize, 
					m_SubAseObj[iSubMtrl].m_dxObj.m_iIndexNum);

				m_SubAseObj[iSubMtrl].m_dxObj.m_pConstantBuffer = CreateConstantBuffer(g_pd3dDevice, &m_SubAseObj[iSubMtrl].m_cbData, sizeof(VSCB), 1);
				m_SubAseObj[iSubMtrl].m_dxObj.m_pVS = DX::LoadVertexShader(g_pd3dDevice, L"../../data/shader/shape.vsh", &m_SubAseObj[iSubMtrl].m_dxObj.m_BlobVS);
				m_SubAseObj[iSubMtrl].m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", &m_SubAseObj[iSubMtrl].m_dxObj.m_BlobPS);

				D3D11_INPUT_ELEMENT_DESC ied[] =
				{
					{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};
				int ElementCnt = sizeof(ied) / sizeof(ied[0]);
				m_SubAseObj[iSubMtrl].m_dxObj.m_pIL = DX::CreateLayout(g_pd3dDevice, ied, ElementCnt, m_SubAseObj[iSubMtrl].m_dxObj.m_BlobVS);
				D3DXMatrixIdentity(&m_SubAseObj[iSubMtrl].m_matWorld);
			}
		}
		else
		{
			// Vertex
			m_pVertexList = CutTriangle(m_Geom.TriangleList);
			m_dxObj.m_iVertexNum = m_pVertexList.size();
			m_dxObj.m_iVertexSize = sizeof(ASE_VERTEX);

			// Index
			m_pIndexList = SetIndex(m_Geom.TriangleList);
			m_dxObj.m_iIndexNum = m_pIndexList.size();
			m_dxObj.m_iIndexSize = sizeof(DWORD);

			m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, &m_pVertexList.at(0), m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
			m_dxObj.m_pIndexBuffer = CreateIndexBuffer(g_pd3dDevice, &m_pIndexList.at(0), m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum);
			m_dxObj.m_pConstantBuffer = CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1);
			m_dxObj.m_pVS = DX::LoadVertexShader(g_pd3dDevice, L"../../data/shader/shape.vsh", &m_dxObj.m_BlobVS);
			m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", &m_dxObj.m_BlobPS);

			D3D11_INPUT_ELEMENT_DESC ied[] =
			{
				{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			int ElementCnt = sizeof(ied) / sizeof(ied[0]);
			m_dxObj.m_pIL = DX::CreateLayout(g_pd3dDevice, ied, ElementCnt, m_dxObj.m_BlobVS);
			D3DXMatrixIdentity(&m_matWorld);
		}
	}
	return true;
}
bool AseObject::Frame()
{
	return true;
}
bool AseObject::Render(ID3D11DeviceContext* context)
{	
	for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
	{
		if (m_Mtrl[iMtrl].subMtrl.size() > 0)
		{
			for (int iSubMtrl = 0; iSubMtrl < m_Mtrl[iMtrl].subMtrl.size(); iSubMtrl++)
			{
				context->UpdateSubresource(m_SubAseObj[iSubMtrl].m_dxObj.m_pConstantBuffer, 0, NULL, &m_SubAseObj[iSubMtrl].m_cbData, 0, 0);
				m_SubAseObj[iSubMtrl].m_dxObj.Render(context);
			}
		}
		else
		{
			context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
			m_dxObj.Render(context);
		}
	}

	return true;
}
bool AseObject::Release()
{
	for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
	{
		for (int iSubMtrl = 0; iSubMtrl < m_Mtrl[iMtrl].subMtrl.size(); iSubMtrl++)
		{
			m_SubAseObj[iSubMtrl].m_dxObj.Release();
		}
	}
	m_dxObj.Release();
	return true;
}
bool AseObject::Load(const TCHAR* AseFileName)
{
	if (LoadAseFile(AseFileName))
	{
		LoadScene();
		LoadMaterial();
		LoadGeom();
		return true;
	}
	return false;
}
bool AseObject::LoadScene()
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
bool AseObject::LoadMaterial()
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
									string abcd = DestroyToken(szTemp, "\"");
									tmpTexture.strTexName = DividePath(abcd.c_str());
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
							string abcd = DestroyToken(szTemp, "\"");
							tmpTexture.strTexName = DividePath(abcd.c_str());
						}
					}
					m_Mtrl[MtrlNum].tex.push_back(tmpTexture);
				}
			}
		}
	}
	return true;
}
bool AseObject::LoadGeom()
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
				if ((iLine = FindToken("ESH_CVERTLIST")) > 0 && dwVertexSize > 0)
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
			// MtrlRef
			if ((iLine = FindToken("MATERIAL_REF")) > 0)
			{
				sscanf(m_Tokenlist[iLine].c_str(), "%s%d", szTemp, &m_Geom.iGeomMtrlRef);
			}
			// Gen Triangle
			GenTriangle();
		}
	}
	return true;
}
//const char* GetPrevToken()

const char* AseObject::GetNextToken()
{
	m_CurrentToken = m_Tokenlist[m_dwTokenIndex++];
	return m_CurrentToken.c_str();
}
INT AseObject::FindToken(string szToken)
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
bool AseObject::LoadAseFile(const TCHAR* AseFileName)
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

	if (!CuttingFile()) return false;
	return true;
}
bool AseObject::CuttingFile()
{
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
string AseObject::DestroyToken(const char* szName, const char* szToken)
{
	string pData = szName;
	string strToken = szToken;
	size_t start = pData.find_first_not_of(strToken);
	size_t end = pData.find_first_of(strToken, start);
	string retData = pData.substr(start, end - 1);
	return retData;
}
string AseObject::DestroyTokenName(const char* szName, const char* szToken)
{
	string pData = szName;
	string strToken = szToken;
	size_t start = pData.find_first_of(strToken);
	size_t end = pData.find_last_of(strToken);
	string retData = pData.substr(start, end - 1);
	return DestroyToken(retData.c_str(), szToken);
}
string AseObject::DividePath(const char* pszFileName)
{
	char RetData[MAX_PATH] = { 0, };
	char Drive[MAX_PATH] = { 0, };
	char Dir[MAX_PATH] = { 0, };
	char FileName[MAX_PATH] = { 0, };
	char Ext[MAX_PATH] = { 0, };
	string Ret;
	if (pszFileName != NULL)
	{
		//_tsplitpath_s((TCHAR*)pszFileName, Drive, Dir, FileName, Ext);
		//wsprintf(RetData, _T("%s%s"), FileName, Ext);
		_splitpath_s(pszFileName, Drive, Dir, FileName, Ext);
		sprintf_s(RetData, "%s%s", FileName, Ext);
		Ret = RetData;
		return Ret;
	}
}
vector<ASE_VERTEX> AseObject::CutTriangle(vector<ASE_TRIANGLE> triangle)
{
	vector<ASE_VERTEX> retTri;
	for (int iTri = 0; iTri < triangle.size(); iTri++)
	{
		retTri.push_back(triangle[iTri].v[0]);
		retTri.push_back(triangle[iTri].v[1]);
		retTri.push_back(triangle[iTri].v[2]);
	}
	return retTri;
}
void AseObject::GenTriangle()
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
	for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
	{
		if (m_Mtrl[iMtrl].subMtrl.size() > 0)
		{
			SetSubObj();
		}
	}
}
bool AseObject::SetSubObj()
{
	for (int iMtrl = 0; iMtrl < m_Mtrl.size(); iMtrl++)
	{
		m_SubAseObj.resize(m_Mtrl[iMtrl].subMtrl.size());
		for (int iSubMtrl = 0; iSubMtrl < m_Mtrl[iMtrl].subMtrl.size(); iSubMtrl++)
		{
			for (int iVer = 0; iVer < m_dwFaceSize; iVer++)
			{
				if (m_Geom.TriangleList[iVer].dwSubID == iSubMtrl)
				{
					m_SubAseObj[iSubMtrl].m_Geom.TriangleList.push_back(m_Geom.TriangleList[iVer]);
				}
			}
		}
	}
	return true;
}
AseObject::AseObject()
{

}
AseObject::~AseObject()
{

}
