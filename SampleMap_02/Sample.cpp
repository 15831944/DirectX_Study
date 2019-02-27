#include "JCore.h"

struct JLookUp
{
	vector<DWORD> m_pNormal;
};

class SampleMap_02 : public JShape
{
public:
	vector<PNCT_VERTEX> m_pVertices;
	vector<DWORD> m_pIndices;
	int m_iCellCols;
	int m_iCellRows;
	int m_iNumCols;
	int m_iNumRows;
	int m_iVertexSize;
	int m_iFaceSize;
	int m_iCellSize;
	float* m_pHeightMap;
	int m_iWidth;
	int m_iHeight;
	vector<D3DXVECTOR3> m_pFaceNormal;
	vector<JLookUp> m_pLookUpTable;
public:
	float GetHeightVertex(int iIndex)
	{
		float fRet = 0.0f;
		if (m_pHeightMap != NULL)
		{
			fRet = m_pHeightMap[iIndex];
		}
		return fRet;
	}
	float GetHeight(float fX, float fZ)
	{
		float fCellX = (m_iNumCols * m_iCellSize / 2.0f + fX) / m_iCellSize;
		float fCellZ = (m_iNumRows * m_iCellSize / 2.0f - fZ) / m_iCellSize;

		int iCellX = (m_iNumCols * m_iCellSize / 2.0f + fX) / m_iCellSize;
		int iCellZ = (m_iNumRows * m_iCellSize / 2.0f - fZ) / m_iCellSize;

		if (iCellX < 0) iCellX = 0;
		if (iCellZ < 0) iCellZ = 0;

		if (iCellX >= m_iNumRows) iCellX = m_iNumRows;
		if (iCellZ >= m_iNumCols) iCellZ = m_iNumCols;

		float fa, fb, fc, fd;
		fa = GetHeightVertex(iCellZ * m_iNumRows + iCellX);
		fb = GetHeightVertex(iCellZ * m_iNumRows + iCellX+1);
		fc = GetHeightVertex((iCellZ+1) * m_iNumRows + iCellX);
		fd = GetHeightVertex((iCellZ+1) * m_iNumRows + iCellX+1);

		float fDeltaX = fCellX - iCellX;
		float fDeltaZ = fCellZ - iCellZ;

		float fRetHeight = 0.0f;
		float u = fb - fa;
		float v = fc - fa;
		if (u * v >1.0f)
		{
			u = fc - fd;
			v = fb - fd;
			fRetHeight = fd + (u * (1.0f - fDeltaX)) + (v * (1.0f - fDeltaZ));
		}
		else
		{
			fRetHeight = fa + (u * fDeltaX) + (v * fDeltaZ);
		}
		return fRetHeight;
	}
	bool CalcPerVertexFastLookUp()
	{
		for (int iVer = 0; iVer < m_iVertexSize; iVer++)
		{
			D3DXVECTOR3 vAver(0,0,0);
			int iFaceSize = m_pLookUpTable[iVer].m_pNormal.size();
			for (int iFace = 0; iFace < iFaceSize; iFace++)
			{
				DWORD dw = m_pLookUpTable[iVer].m_pNormal[iFace];
				vAver += m_pFaceNormal[dw];
			}
			D3DXVec3Normalize(&m_pVertices[iVer].n, &vAver);
		}
		return true;
	}
	bool GenNormalLookUpTable()
	{
		m_pLookUpTable.resize(m_iFaceSize);
		for (int iFace = 0; iFace < m_iFaceSize; iFace++)
		{
			for (int iVer = 0; iVer < 3; iVer++)
			{
				DWORD ID = m_pIndices[iFace * 3 + iVer];
				m_pLookUpTable[ID].m_pNormal.push_back(iFace);
			}
		}
		return true;
	}
	D3DXVECTOR3 ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2)
	{
		D3DXVECTOR3 vRet;
		D3DXVECTOR3 v0 = m_pVertices[i1].p - m_pVertices[i0].p;
		D3DXVECTOR3 v1 = m_pVertices[i2].p - m_pVertices[i0].p;

		D3DXVec3Cross(&vRet, &v0, &v1);
		D3DXVec3Normalize(&vRet, &vRet);
		return vRet;
	}
	bool InitFaceNormal()
	{
		m_pFaceNormal.resize(m_iFaceSize);
		for (int iFace = 0; iFace < m_iFaceSize; iFace++)
		{
			DWORD i0 = m_pIndices[iFace * 3 + 0];
			DWORD i1 = m_pIndices[iFace * 3 + 1];
			DWORD i2 = m_pIndices[iFace * 3 + 2];

			m_pFaceNormal[iFace] = ComputeFaceNormal(i0, i1, i2);
		}
		return true;
	}
	bool CreateVertexNormal()
	{
		InitFaceNormal();
		GenNormalLookUpTable();
		CalcPerVertexFastLookUp();
		return true;
	}
	bool SetHeightMap(ID3D11DeviceContext* context, const TCHAR* szFileName)
	{
		D3DX11_IMAGE_INFO Info;
		D3DX11_IMAGE_LOAD_INFO LoadInfo;
		ZeroMemory(&LoadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
		LoadInfo.CpuAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		LoadInfo.Format = DXGI_FORMAT_FROM_FILE;
		LoadInfo.pSrcInfo = &Info;
		LoadInfo.Usage = D3D11_USAGE_STAGING;

		ID3D11Resource* pResource;
		D3DX11CreateTextureFromFile(g_pd3dDevice, szFileName, &LoadInfo, NULL, &pResource, NULL);

		ID3D11Texture2D* pTex;
		pResource->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTex);
		SAFE_RELEASE(pResource);

		D3D11_TEXTURE2D_DESC desc;
		pTex->GetDesc(&desc);
		
		m_iWidth = desc.Width;
		m_iHeight = desc.Height;
		m_pHeightMap = new float[m_iWidth * m_iHeight];
		
		D3D11_MAPPED_SUBRESOURCE Mapped;
		if (SUCCEEDED(context->Map(pTex, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, NULL, &Mapped)))
		{
			UCHAR* pTexel = (UCHAR*)Mapped.pData;
			for (UINT iCols = 0; iCols < desc.Height; iCols++)
			{
				UINT iColStart = iCols * Mapped.RowPitch;
				for (UINT iRows = 0; iRows < desc.Width; iRows++)
				{
					UINT iRowStart = iRows * 4;
					UINT iRed = pTexel[iColStart+iRowStart];
					m_pHeightMap[iCols * desc.Width + iRows] = iRed * 0.1f;
				}
			}
			context->Unmap(pTex, D3D11CalcSubresource(0, 0, 1));
		}
		SAFE_RELEASE(pTex);
		return true;
	}
	bool Create(UINT iWidth, UINT iHeight, UINT iCellSz, const TCHAR* szFileName)
	{
		m_iVertexSize = iWidth * iHeight;
		m_iCellSize = iCellSz;
		m_iCellRows = iWidth - 1;
		m_iCellCols = iHeight - 1;
		m_iNumRows = iWidth;
		m_iNumCols = iHeight;
		m_iFaceSize = (iWidth - 1) * (iHeight - 1) * 2;

		float fOffsetX = 1.0f / m_iNumRows;
		float fOffsetZ = 1.0f / m_iNumCols;
		float fHalfX = (m_iNumRows * m_iCellSize) / 2.0f;
		float fHalfZ = (m_iNumCols * m_iCellSize) / 2.0f;

		m_pVertices.resize(m_iVertexSize);
		for (int iCols = 0; iCols < iHeight; iCols++)
		{
			for (int iRows = 0; iRows < iWidth; iRows ++)
			{
				float fHeight = 0.0f;
				if (m_pHeightMap != NULL)
				{
					fHeight = m_pHeightMap[iCols * iWidth + iRows];
				}
				int iIndex = iCols * iWidth + iRows;
				m_pVertices[iIndex].p = D3DXVECTOR3((iRows * m_iCellSize) - fHalfX, fHeight, (-iCols * m_iCellSize) + fHalfZ);
				m_pVertices[iIndex].n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				m_pVertices[iIndex].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				m_pVertices[iIndex].t = D3DXVECTOR2(fHalfX * iRows, fHalfZ * iCols);
			}
		}


		m_dxObj.m_iVertexNum = m_pVertices.size();
		m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);

		m_pIndices.resize(m_iFaceSize * 3);
		int iIndex = 0;
		for (int iCols = 0; iCols < iHeight - 1; iCols++)
		{
			for (int iRows = 0; iRows < iWidth - 1; iRows++)
			{
				m_pIndices[iIndex++] = (iCols * iWidth) + iRows;
				m_pIndices[iIndex++] = (iCols * iWidth) + iRows + 1;
				m_pIndices[iIndex++] = ((iCols + 1) * iWidth) + iRows;
				m_pIndices[iIndex++] = ((iCols + 1) * iWidth) + iRows;
				m_pIndices[iIndex++] = (iCols * iWidth) + iRows + 1;
				m_pIndices[iIndex++] = ((iCols + 1) * iWidth) + iRows + 1;
			}
		}
		m_dxObj.m_iIndexNum = m_pIndices.size();
		m_dxObj.m_iIndexSize = sizeof(DWORD);

		CreateVertexNormal();

		m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, &m_pVertices.at(0), m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
		m_dxObj.m_pIndexBuffer = CreateIndexBuffer(g_pd3dDevice, &m_pIndices.at(0), m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum);
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
		return true;
	}
	bool Render(ID3D11DeviceContext* context)
	{
		context->UpdateSubresource(m_dxObj.m_pConstantBuffer, NULL, NULL, &m_cbData, NULL, NULL);
		m_dxObj.Render(context);
		return true;
	}
};

class Sample : public JCore
{
public:
	SampleMap_02 map;
	JShape*		m_pBox;
	D3DXMATRIX  m_matWorld;
public:
	bool Init()
	{
		map.Init();
		map.SetHeightMap(GetContext(), L"../../data/Map512.png");
		map.Create(map.m_iWidth, map.m_iHeight, 1, L"../../data/Castle.jpg");
		int iTexture = I_TexMgr.Add(g_pd3dDevice, L"../../data/Castle.jpg");
		map.m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTexture);
		
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
RUN;