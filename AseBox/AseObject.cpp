#include "AseObject.h"
// MESH_MTLID
// MESH_FACE_LIST :: Index	
// MATERIAL_REF 0
// t : 1.0f -
bool AseObject::Init()
{
	PNCT_VERTEX vertices[] =
	{
	// 아래
	{ m_GeoMetry.m_vPosList[2], m_GeoMetry.m_vNorList[0], D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[2] },
	{ m_GeoMetry.m_vPosList[0], m_GeoMetry.m_vNorList[0], D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[0] },
	{ m_GeoMetry.m_vPosList[1], m_GeoMetry.m_vNorList[0], D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[1] },
	{ m_GeoMetry.m_vPosList[2], m_GeoMetry.m_vNorList[1], D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[2] },
	{ m_GeoMetry.m_vPosList[1], m_GeoMetry.m_vNorList[1], D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[1] },
	{ m_GeoMetry.m_vPosList[3], m_GeoMetry.m_vNorList[1], D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[3] },
	// 위
	{ m_GeoMetry.m_vPosList[6], m_GeoMetry.m_vNorList[2], D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[6] },
	{ m_GeoMetry.m_vPosList[5], m_GeoMetry.m_vNorList[2], D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[5] },
	{ m_GeoMetry.m_vPosList[4], m_GeoMetry.m_vNorList[2], D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[4] },
	{ m_GeoMetry.m_vPosList[6], m_GeoMetry.m_vNorList[3], D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[6] },
	{ m_GeoMetry.m_vPosList[7], m_GeoMetry.m_vNorList[3], D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[7] },
	{ m_GeoMetry.m_vPosList[5], m_GeoMetry.m_vNorList[3], D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[5] },
	// 정면
	{ m_GeoMetry.m_vPosList[4], m_GeoMetry.m_vNorList[4], D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), m_GeoMetry.m_vTexList[6] },
	{ m_GeoMetry.m_vPosList[1], m_GeoMetry.m_vNorList[4], D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), m_GeoMetry.m_vTexList[5] },
	{ m_GeoMetry.m_vPosList[0], m_GeoMetry.m_vNorList[4], D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), m_GeoMetry.m_vTexList[4] },
	{ m_GeoMetry.m_vPosList[4], m_GeoMetry.m_vNorList[5], D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), m_GeoMetry.m_vTexList[6] },
	{ m_GeoMetry.m_vPosList[5], m_GeoMetry.m_vNorList[5], D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), m_GeoMetry.m_vTexList[7] },
	{ m_GeoMetry.m_vPosList[1], m_GeoMetry.m_vNorList[5], D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), m_GeoMetry.m_vTexList[5] },
	// 뒤
	{ m_GeoMetry.m_vPosList[2], m_GeoMetry.m_vNorList[8], D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[0] },
	{ m_GeoMetry.m_vPosList[3], m_GeoMetry.m_vNorList[8], D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[1] },
	{ m_GeoMetry.m_vPosList[6], m_GeoMetry.m_vNorList[8], D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[2] },
	{ m_GeoMetry.m_vPosList[6], m_GeoMetry.m_vNorList[9], D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[2] },
	{ m_GeoMetry.m_vPosList[3], m_GeoMetry.m_vNorList[9], D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[1] },
	{ m_GeoMetry.m_vPosList[7], m_GeoMetry.m_vNorList[9], D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[3] },
	// 오른
	{ m_GeoMetry.m_vPosList[5], m_GeoMetry.m_vNorList[6], D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[0] },
	{ m_GeoMetry.m_vPosList[7], m_GeoMetry.m_vNorList[6], D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[1] },
	{ m_GeoMetry.m_vPosList[1], m_GeoMetry.m_vNorList[6], D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[2] },
	{ m_GeoMetry.m_vPosList[1], m_GeoMetry.m_vNorList[7], D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[2] },
	{ m_GeoMetry.m_vPosList[7], m_GeoMetry.m_vNorList[7], D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[1] },
	{ m_GeoMetry.m_vPosList[3], m_GeoMetry.m_vNorList[7], D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), m_GeoMetry.m_vTexList[3] },
	// 왼
	{ m_GeoMetry.m_vPosList[0], m_GeoMetry.m_vNorList[10], D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), m_GeoMetry.m_vTexList[6] },
	{ m_GeoMetry.m_vPosList[6], m_GeoMetry.m_vNorList[10], D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), m_GeoMetry.m_vTexList[5] },
	{ m_GeoMetry.m_vPosList[4], m_GeoMetry.m_vNorList[10], D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), m_GeoMetry.m_vTexList[4] },
	{ m_GeoMetry.m_vPosList[6], m_GeoMetry.m_vNorList[11], D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), m_GeoMetry.m_vTexList[5] },
	{ m_GeoMetry.m_vPosList[0], m_GeoMetry.m_vNorList[11], D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), m_GeoMetry.m_vTexList[6] },
	{ m_GeoMetry.m_vPosList[2], m_GeoMetry.m_vNorList[11], D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), m_GeoMetry.m_vTexList[7] },
	};
	m_dxObj.m_iVertexNum = sizeof(vertices) / sizeof(vertices[0]);
	m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);

	//	DWORD indices[] =
	//	{
	//		0,2,3,	3,1,0,
	//		4,5,7,	7,6,4,
	//		0,1,5,	5,4,0,
	//		1,3,7,	7,5,1,
	//		3,2,6,	6,7,3,
	//		2,0,4,	4,6,2,
	//	};
	//m_dxObj.m_iIndexNum = sizeof(indices) / sizeof(indices[0]);
	//m_dxObj.m_iIndexSize = sizeof(DWORD);

	m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, vertices, m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
//	m_dxObj.m_pIndexBuffer = CreateIndexBuffer(g_pd3dDevice, indices, m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum);
	m_dxObj.m_pConstantBuffer = DX::CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1);
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
	return true;
}
bool AseObject::Frame()
{
	return true;
}
bool AseObject::Render(ID3D11DeviceContext* context)
{
	context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	m_dxObj.Render(context);
	return true;
}
bool AseObject::Release()
{
	return true;
}
void AseObject::SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	if (matWorld != NULL)
		m_matWorld = *matWorld;
	if (matView != NULL)
		m_matView = *matView;
	if (matProj != NULL)
		m_matProj = *matProj;

	m_vRight.x = m_matWorld._11;
	m_vRight.y = m_matWorld._12;
	m_vRight.z = m_matWorld._13;

	m_vUp.x = m_matWorld._21;
	m_vUp.y = m_matWorld._22;
	m_vUp.z = m_matWorld._23;

	m_vLook.x = m_matWorld._31;
	m_vLook.y = m_matWorld._32;
	m_vLook.z = m_matWorld._33;

	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;

	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
}
bool AseObject::AseLoad(const TCHAR* szFileName)
{
	if (!LoadAseFile(szFileName)) return false;
	if (!CuttingFile()) return false;
	CutScene();
	CutMaterial();
	CutGeoMetryObject();
	return true;
}
bool AseObject::CutScene()
{
	char temp[256] = { 0, };
	for (m_iStartToken; m_iStartToken < m_TokenList.size(); m_iStartToken++)
	{
		if (strstr(m_TokenList[m_iStartToken].c_str(), "SCENE_FILENAME"))
		{
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%s", temp, m_Scene.m_FileName.c_str());
		}
		
		if (strstr(m_TokenList[m_iStartToken].c_str(), "SCENE_FIRSTFRAME"))
		{
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%d", temp, &m_Scene.m_dwFirstFrame);
		}

		if (strstr(m_TokenList[m_iStartToken].c_str(), "SCENE_LASTFRAME"))
		{
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%d", temp, &m_Scene.m_dwLastFrame);
		}

		if (strstr(m_TokenList[m_iStartToken].c_str(), "SCENE_TICKSPERFRAME"))
		{
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%d", temp, &m_Scene.m_dwTickPerFrame);
			break;
		}
	}
	return true;
}
bool AseObject::CutMaterial()
{
	char temp[256] = { 0, };
	int	 iMaterialCnt = -1;
	for (m_iStartToken; m_iStartToken < m_TokenList.size(); m_iStartToken++)
	{
		if (strstr(m_TokenList[m_iStartToken].c_str(), "MATERIAL_COUNT"))
		{
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%d", temp, &m_dwMaterialCount);
			m_MaterialList.resize(m_dwMaterialCount);
		}
		if (strstr(m_TokenList[m_iStartToken].c_str(), "MATERIAL "))
		{
			iMaterialCnt++;
		}
		if (strstr(m_TokenList[m_iStartToken].c_str(), "MATERIAL_NAME"))
		{
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%s", temp, m_MaterialList[iMaterialCnt].m_MaterialName.c_str());
		}
		if (strstr(m_TokenList[m_iStartToken].c_str(), "MAP_DIFFUSE"))
		{
			m_MaterialList[iMaterialCnt].m_Texture.m_iType = 1;
		}
		if (strstr(m_TokenList[m_iStartToken].c_str(), "BITMAP"))
		{
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%s", temp, temp);
			m_MaterialList[iMaterialCnt].m_Texture.m_TextureName = Divide(DestroyQuotationMark(temp).c_str());
			break;
		}
	}
	return true;
}
bool AseObject::CutGeoMetryObject()
{
	char temp[256] = { 0, };
	int itemp = 0;
	for (m_iStartToken; m_iStartToken < m_TokenList.size(); m_iStartToken++)
	{
		if (strstr(m_TokenList[m_iStartToken].c_str(), "NODE_NAME"))
		{
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%s", temp, temp);
			m_GeoMetry.m_NodeName = DestroyQuotationMark(temp);
		}
		if (strstr(m_TokenList[m_iStartToken].c_str(), "TM_ROW0"))
		{
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%f%f%f", temp, &m_GeoMetry.m_matWorld._11,
				&m_GeoMetry.m_matWorld._12,
				&m_GeoMetry.m_matWorld._13);
		}
		if (strstr(m_TokenList[m_iStartToken].c_str(), "TM_ROW1"))
		{
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%f%f%f", temp, &m_GeoMetry.m_matWorld._31,
				&m_GeoMetry.m_matWorld._32,
				&m_GeoMetry.m_matWorld._33);
		}
		if (strstr(m_TokenList[m_iStartToken].c_str(), "TM_ROW2"))
		{
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%f%f%f", temp, &m_GeoMetry.m_matWorld._21,
				&m_GeoMetry.m_matWorld._22,
				&m_GeoMetry.m_matWorld._23);
		}
		if (strstr(m_TokenList[m_iStartToken].c_str(), "TM_ROW3"))
		{
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%f%f%f", temp, &m_GeoMetry.m_matWorld._41,
				&m_GeoMetry.m_matWorld._42,
				&m_GeoMetry.m_matWorld._43);
		}
		if (strstr(m_TokenList[m_iStartToken].c_str(), "MESH_VERTEX    "))
		{
			float x, y, z;
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%d%f%f%f", temp, &itemp, &x, &z, &y);
			m_GeoMetry.m_vPosList.push_back(D3DXVECTOR3(x,y,z));
		}
		if (strstr(m_TokenList[m_iStartToken].c_str(), "MESH_TVERT "))
		{
			D3DXVECTOR2 vTemp;
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%d%f%f", temp, &itemp, &vTemp.x, &vTemp.y);
			m_GeoMetry.m_vTexList.push_back(vTemp);
		}
		if (strstr(m_TokenList[m_iStartToken].c_str(), "MESH_FACENORMAL"))
		{
			D3DXVECTOR3 vTemp;
			sscanf(m_TokenList[m_iStartToken].c_str(), "%s%d %f%f%f", temp, &itemp, &vTemp.x, &vTemp.z, &vTemp.y);
			m_GeoMetry.m_vNorList.push_back(vTemp);
		}
		//if (strstr(m_TokenList[m_iStartToken].c_str(), "MATERIAL_REF"))
		//{
		//	D3DXVECTOR3 vTemp;
		//	sscanf(m_TokenList[m_iStartToken].c_str(), "%s%d", temp, m_dwMtrlRef);
		//}
	}
	return true;
}
// 따옴표 제거
string AseObject::DestroyQuotationMark(const char* szName)
{
	string pData = szName;
	string cToken = "\"";
	size_t start = pData.find_first_not_of(cToken);
	size_t end = pData.find_first_of(cToken, start);
	string texData = pData.substr(start, end - 1);

	return texData;
}
char* AseObject::Divide(const char* pszFileName)
{
	char szFileName[MAX_PATH] = { 0, };
	char Dirve[MAX_PATH] = { 0, };
	char Dir[MAX_PATH] = { 0, };
	char FileName[MAX_PATH] = { 0, };
	char FileExt[MAX_PATH] = { 0, };
	if (pszFileName != NULL)
	{
		_splitpath_s(pszFileName, Dirve, Dir, FileName, FileExt);
		sprintf_s(szFileName, "%s%s", FileName, FileExt);
	}
	return szFileName;
}
AseObject::AseObject()
{
	D3DXMatrixIdentity(&m_GeoMetry.m_matWorld);
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vUp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
}
AseObject::~AseObject()
{
}
