#include "JCore.h"
#include "JShape.h"
#define MAP_HEIGHT 0.1f
struct JVertexLookUp
{
	vector<DWORD> NormalList;
};
class JSampleMap : public JPlaneShape
{
public:
	vector<PNCT_VERTEX> m_pVertices;
	vector<DWORD>       m_pIndices;
	int m_iNumCols;
	int m_iNumRows;
	float* m_fHeightMap;
	int m_iFaceCnt;
	float m_fCellSize;
	int VerticeSize;
	int m_iCellCols; // - 1
	int m_iCellRows; // - 1
	int m_iWidth;
	int m_iHeight;
	float m_fHeightScale;
	vector<D3DXVECTOR3> m_pFaceNormalList;
	vector<JVertexLookUp> m_pNormalLookUpTable;
public:
	float GetHeight(float fX, float fZ)
	{
		float fCellX = (m_iCellCols * m_fCellSize / 2.0f + fX) / m_fCellSize;
		float fCellZ = (m_iCellRows * m_fCellSize / 2.0f - fZ) / m_fCellSize;

		int iCellX = (m_iCellCols * m_fCellSize / 2.0f + fX) / m_fCellSize;
		int iCellZ = (m_iCellRows * m_fCellSize / 2.0f - fZ) / m_fCellSize;

		if (iCellX < 0) iCellX = 0;
		if (iCellZ < 0) iCellZ = 0;

		if (iCellX >= m_iNumCols) iCellX = m_iNumCols;
		if (iCellZ >= m_iNumRows) iCellZ = m_iNumRows;

		float fa, fb, fc, fd;

		fa = GetHeightOfVertex(iCellZ * m_iNumCols + iCellX);
		fb = GetHeightOfVertex(iCellZ * m_iNumCols + iCellX + 1);
		fc = GetHeightOfVertex((iCellZ + 1) * m_iNumCols + iCellX);
		fd = GetHeightOfVertex((iCellZ + 1) * m_iNumCols + iCellX + 1);

		float fDeltaX = fCellX - iCellX;
		float fDeltaZ = fCellZ - fCellZ;

		float fHeight = fa;
		float u, v;
		u = fb - fa;
		v = fc - fa;
		if (u*v > 1.0f)
		{
			u = fc - fd;
			v = fb - fd;
			fHeight = fd + (u * (1.0f - fDeltaX)) + (v * ( 1.0f - fDeltaZ));
		}
		else
		{
			// 선형보간..
			fHeight = fa + (u * fDeltaX) + (v * fDeltaZ);
		}
		return fHeight;
	}
	float GetHeightOfVertex(UINT iIndex)
	{
		float fHeight = 0.0f;
		if (m_fHeightMap != NULL)
		{
			fHeight = m_fHeightMap[iIndex] * m_fHeightScale;
		}
		return fHeight;
	}
	void CalcPerVertexNormalsFastLookup()
	{
		for (int iVer = 0; iVer < VerticeSize; iVer++)
		{
			D3DXVECTOR3 vAverage(0.0f, 0.0f, 0.0f);
			int iFaceCnt = m_pNormalLookUpTable[iVer].NormalList.size();
			for (int iNor = 0; iNor < iFaceCnt; iNor++)
			{
				DWORD dwNormal = m_pNormalLookUpTable[iVer].NormalList[iNor];
				vAverage += m_pFaceNormalList[dwNormal];
			}
			D3DXVec3Normalize(&m_pVertices[iVer].n, &vAverage);
		}
	}
	void GenNormalLookUpTable()
	{
		m_pNormalLookUpTable.resize(m_iFaceCnt);
		for (int iFace = 0; iFace < m_iFaceCnt; iFace++)
		{
			for (int iVer = 0; iVer < 3; iVer++)
			{
				DWORD id = m_pIndices[iFace * 3 + iVer];
				m_pNormalLookUpTable[id].NormalList.push_back(iFace);
			}
		}
	}
	void InitFaceNormal()
	{
		m_pFaceNormalList.resize(m_iFaceCnt);
		// 
		for (int iFace = 0; iFace < m_iFaceCnt; iFace++)
		{
			DWORD i0 = m_pIndices[iFace * 3 + 0];
			DWORD i1 = m_pIndices[iFace * 3 + 1];
			DWORD i2 = m_pIndices[iFace * 3 + 2];
			m_pFaceNormalList[iFace] = ComputeFaceNormal(i0, i1, i2);
		}
	}
	D3DXVECTOR3 ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2)
	{
		D3DXVECTOR3 FaceNomal;
		D3DXVECTOR3 vEdge0 = m_pVertices[i1].p - m_pVertices[i0].p;
		D3DXVECTOR3 vEdge1 = m_pVertices[i2].p - m_pVertices[i0].p;

		D3DXVec3Cross(&FaceNomal, &vEdge0, &vEdge1);
		D3DXVec3Normalize(&FaceNomal, &FaceNomal);
		return FaceNomal;
	}
	void CreateNormalVertex()
	{
		InitFaceNormal();
		GenNormalLookUpTable();
		CalcPerVertexNormalsFastLookup();
	}
	D3DXVECTOR3 GetNormalOfVertex(int iIndex)
	{
		D3DXVECTOR3 retV3(0.0f, 1.0f, 0.0f);
		return retV3;
	}
	bool SetHeightTexture(ID3D11DeviceContext* context, const TCHAR* szTexName)
	{
		D3DX11_IMAGE_INFO imageinfo;
		D3DX11_IMAGE_LOAD_INFO loadinfo;
		ZeroMemory(&loadinfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
		/* cpu 접근 허가 */
		loadinfo.Usage = D3D11_USAGE_STAGING;
		loadinfo.Format = DXGI_FORMAT_FROM_FILE;
		loadinfo.CpuAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		loadinfo.pSrcInfo = &imageinfo;

		ID3D11Resource* pResource;
		D3DX11CreateTextureFromFile(g_pd3dDevice, szTexName ,&loadinfo, NULL, &pResource, NULL);

		ID3D11Texture2D* pTex2D;
		pResource->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTex2D);

		SAFE_RELEASE(pResource);

		D3D11_TEXTURE2D_DESC desc;
		pTex2D->GetDesc(&desc);

		m_iWidth = desc.Width;
		m_iHeight = desc.Height;

		m_fHeightMap = new float[m_iWidth * m_iHeight];

		D3D11_MAPPED_SUBRESOURCE Mapped;
		/* Map -> CriticalSection */
		if (SUCCEEDED(context->Map(pTex2D, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &Mapped)))
		{
			UCHAR* pTexels = (UCHAR*)Mapped.pData;
			for (UINT row = 0; row < desc.Height; row++)
			{
				UINT rowStart = row * Mapped.RowPitch;
				for (UINT col = 0; col < desc.Width; col++)
				{
					UINT colStart = col * 4;
					UINT uRed = pTexels[rowStart + colStart + 0];
					m_fHeightMap[row*desc.Width + col] = uRed * MAP_HEIGHT;
				}
			}
			context->Unmap(pTex2D, D3D11CalcSubresource(0, 0, 1));
		}
		SAFE_RELEASE(pTex2D);
		return true;
	}
	bool Init()
	{
		return true;
	}
	bool Create(ID3D11Device* device, int iWidth, int iHeight, int iCellSize)
	{
		m_iNumCols = iWidth;
		m_iNumRows = iHeight;
		VerticeSize = iWidth*iHeight;
		m_fCellSize = iCellSize;
		m_iFaceCnt = (iWidth - 1) * (iHeight - 1) * 2;
		m_iCellCols = iWidth - 1;
		m_iCellRows = iHeight - 1;


		float fHalfRow = ((iWidth - 1) * m_fCellSize) / 2.0f;
		float fHalfCol = ((iHeight - 1) * m_fCellSize) /2.0f;
		float fOffsetX = 1.0f / (iWidth - 1);
		float fOffsetZ = 1.0f / (iHeight - 1);

		m_pVertices.resize(VerticeSize);

		for (int iCol = 0; iCol < iHeight; iCol++)
		{
			for (int iRow = 0; iRow < iWidth; iRow++)
			{
				int iIndex = (iCol * iWidth) + iRow;

				float fHeight = 0.0f;
				if (m_fHeightMap != NULL)
				{
					fHeight = m_fHeightMap[iCol * iWidth + iRow];// *0.1f;
				}
				m_pVertices[iIndex].p = D3DXVECTOR3((iRow * iCellSize) - fHalfRow, fHeight, -iCol * iCellSize + fHalfCol);
				m_pVertices[iIndex].n = GetNormalOfVertex(iIndex); // 0,1,0
				m_pVertices[iIndex].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				m_pVertices[iIndex].t = D3DXVECTOR2(fOffsetX*iRow, fOffsetZ*iCol);
			}
		}

		m_dxObj.m_iVertexNum = m_pVertices.size();
		m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);
		
		int iIndexCnt = m_iFaceCnt * 3;
		m_pIndices.resize(iIndexCnt);

		int iCount = 0;
		for (int iCol = 0; iCol < iHeight - 1; iCol++)
		{
			for (int iRow = 0; iRow < iWidth - 1; iRow++)
			{
				m_pIndices[iCount++] = (iCol*iWidth) + iRow;
				m_pIndices[iCount++] = (iCol*iWidth) + iRow + 1;
				m_pIndices[iCount++] = ((iCol + 1) * iWidth) + iRow;

				m_pIndices[iCount++] = ((iCol + 1) * iWidth) + iRow;
				m_pIndices[iCount++] = (iCol*iWidth) + iRow + 1;
				m_pIndices[iCount++] = ((iCol + 1) * iWidth) + iRow + 1;
			}
		}
		m_dxObj.m_iIndexNum = m_pIndices.size();
		m_dxObj.m_iIndexSize = sizeof(DWORD);

		/* Normal Create */
		CreateNormalVertex();

		m_dxObj.m_pVertexBuffer		= DX::CreateVertexBuffer(g_pd3dDevice, &m_pVertices.at(0), m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
		m_dxObj.m_pIndexBuffer		= CreateIndexBuffer(g_pd3dDevice, &m_pIndices.at(0), m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum);
		m_dxObj.m_pConstantBuffer	= CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1);
		m_dxObj.m_pVS				= DX::LoadVertexShader(g_pd3dDevice, L"../../data/shader/shape.vsh", &m_dxObj.m_BlobVS);
		m_dxObj.m_pPS				= DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", &m_dxObj.m_BlobPS);

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
		return true;
	}
	bool Render(ID3D11DeviceContext* context)
	{
		context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
		m_dxObj.Render(context);
		return true;
	}
	bool Release()
	{
		SAFE_DELETE(m_fHeightMap);
		return true;
	}
public:
	JSampleMap()
	{
		m_iNumCols = 0;
		m_iNumRows = 0;
		 m_fHeightMap = NULL;
		 m_iFaceCnt = 0;
		 m_fCellSize = 0;
		 VerticeSize = 0;
		 m_fHeightScale = 1.0f;
		 m_iCellCols = 0;
		 m_iCellRows = 0;
	}
	virtual ~JSampleMap()
	{

	}
};
class Sample : public JCore
{
public:
	JSampleMap map;
	JShape*		m_pBox;
	D3DXMATRIX  m_matWorld;
	//D3DXMATRIX m_matWorld;
public:
	bool Init()
	{
		map.Init();
		map.SetHeightTexture(GetContext(), L"../../data/Height_Castle.bmp");
		map.Create(GetDevice(),map.m_iWidth, map.m_iHeight, 1);
		int m_iTexture = I_TexMgr.Add(GetDevice(), L"../../data/Castle.jpg");
		//int m_iTexture = I_TexMgr.Add(GetDevice(), L"../../data/Bitmap/BackGround.bmp");
		map.m_dxObj.m_pTexture = I_TexMgr.GetPtr(m_iTexture);
		m_pBox = new JBoxShape();
		m_pBox->Init();
		D3DXMatrixIdentity(&m_matWorld);
		return true;
	}
	bool Frame()
	{
		if (I_Input.KeyCheck(VK_UP) == KEY_PUSH || I_Input.KeyCheck(VK_UP) == KEY_HOLD)
		{
			m_pBox->m_vPos += m_pBox->m_vLook * g_fSecPerFrame * 10.0f;
		}
		if (I_Input.KeyCheck(VK_DOWN) == KEY_PUSH || I_Input.KeyCheck(VK_DOWN) == KEY_HOLD)
		{
			m_pBox->m_vPos -= m_pBox->m_vLook * g_fSecPerFrame * 10.0f;
		}
		if (I_Input.KeyCheck(VK_RIGHT) == KEY_PUSH || I_Input.KeyCheck(VK_RIGHT) == KEY_HOLD)
		{
			m_pBox->m_vPos += m_pBox->m_vRight * g_fSecPerFrame * 10.0f;
		}
		if (I_Input.KeyCheck(VK_LEFT) == KEY_PUSH || I_Input.KeyCheck(VK_LEFT) == KEY_HOLD)
		{
			m_pBox->m_vPos -= m_pBox->m_vRight * g_fSecPerFrame * 10.0f;
		}
		m_matWorld._41 = m_pBox->m_vPos.x;
		m_matWorld._43 = m_pBox->m_vPos.z;
		m_matWorld._42 = map.GetHeight(m_pBox->m_vPos.x, m_pBox->m_vPos.z);
		return true;
	}
	bool Render()
	{
		map.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		map.Render(GetContext());

		m_pBox->SetMatrix(&m_matWorld, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_pBox->Render(GetContext());
		return true;
	}
	bool Release()
	{
		map.Release();
		m_pBox->Release();
		return true;
	}
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow)
{
	Sample core;
	if (core.SetWindow(hInstance, 800, 600, L"DirectX Sample Box3D"))
	{
		core.Run();
		return 0;
	}
	return 1;
}