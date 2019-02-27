#include "JCore.h"

class BackViewCamera : public JCamera
{
public:
	BackViewCamera() {}
	virtual ~BackViewCamera() {}
};

struct JVertexLookUp
{
	vector<DWORD> m_pLookUp;
};

class SampleMap_01 : public JShape
{
public:
	vector<PNCT_VERTEX> m_pVertices;
	vector<DWORD> m_pIndices;
	int m_iCellSize;
	int m_iNumCols;
	int m_iNumRows;
	int m_iCellCols;
	int m_iCellRows;
	int m_iVertexSize;
	float m_fFaceSize;
	int m_iWidth;
	int m_iHeight;
	float* m_pHeightMap;
	vector<D3DXVECTOR3> m_pFaceNormal;
	vector<JVertexLookUp> m_pLookUpTable;
public:
	float GetHeightOfVertex(int iIndex)
	{
		float fReturn = 0.0f;
		
		if (m_pHeightMap == NULL) return -1.0f;
		fReturn = m_pHeightMap[iIndex];

		return fReturn;
	}
	float GetHeight(float fX, float fZ)
	{
		float fCellX = ((m_iCellCols * m_iCellSize / 2.0f) + fX) * m_iCellSize;
		float fCellZ = ((m_iCellCols * m_iCellSize / 2.0f) - fZ) * m_iCellSize;

		int iCellX = ((m_iCellCols * m_iCellSize / 2.0f) + fX) * m_iCellSize;
		int iCellZ = ((m_iCellCols * m_iCellSize / 2.0f) - fZ) * m_iCellSize;

		if (iCellX < 0) iCellX = 0;
		if (iCellZ < 0) iCellZ = 0;

		if (iCellX > m_iNumCols) iCellX = m_iNumCols;
		if (iCellZ > m_iNumRows) iCellX = m_iNumRows;

		float fa, fb, fc, fd;
		fa = GetHeightOfVertex(iCellZ * m_iNumCols + iCellX);
		fb = GetHeightOfVertex(iCellZ * m_iNumCols + iCellX + 1);
		fc = GetHeightOfVertex((iCellZ+1) * m_iNumCols + iCellX);
		fd = GetHeightOfVertex((iCellZ+1) * m_iNumCols + iCellX+1);

		float fDeltaX = fCellX - iCellX;
		float fDeltaZ = fCellZ - iCellZ;

		float fHeight = fa;
		float fU = fb - fa;
		float fV = fc - fa;
		if (fU * fV > 1.0f)
		{
			fU = fc - fd;
			fV = fb - fd;
			fHeight = fd + (fU * (1.0f - fDeltaX)) + (fV * (1.0f - fDeltaZ));
		}
		else
		{
			fHeight = fa + (fU * fDeltaX) + (fV * fDeltaZ);
		}
		return fHeight;
	}
	bool CalcPerNormalVertexFastLookUp()
	{
		for (int iVer = 0; iVer < m_iVertexSize; iVer++)
		{
			D3DXVECTOR3 vAverage(0.0f, 0.0f, 0.0f);
			int iFaceSize = m_pLookUpTable[iVer].m_pLookUp.size();
			for (int iFace = 0; iFace < iFaceSize; iFace++)
			{
				DWORD dwNor = m_pLookUpTable[iVer].m_pLookUp[iFace];
				vAverage += m_pFaceNormal[dwNor];
			}
			D3DXVec3Normalize(&m_pVertices[iVer].n, &vAverage);
		}
		return true;
	}
	bool GenNormalLookUpTable()
	{
		m_pLookUpTable.resize(m_fFaceSize);
		for (int iFace = 0; iFace < m_fFaceSize; iFace++)
		{
			for (int iVer = 0; iVer < 3; iVer++)
			{
				DWORD ID = m_pIndices[iFace * 3 + iVer];
				m_pLookUpTable[ID].m_pLookUp.push_back(iFace);
			}
		}
		return true;
	}
	D3DXVECTOR3 ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2)
	{
		D3DXVECTOR3 vRet;
		D3DXVECTOR3 vNol1 = m_pVertices[i1].p - m_pVertices[i0].p;
		D3DXVECTOR3 vNol2 = m_pVertices[i2].p - m_pVertices[i0].p;

		D3DXVec3Cross(&vRet, &vNol1, &vNol2);
		D3DXVec3Normalize(&vRet, &vRet);
		return vRet;
	}
	bool InitFaceNormal()
	{
		m_pFaceNormal.resize(m_fFaceSize);
		for (int iFace = 0; iFace < m_fFaceSize; iFace++)
		{
			DWORD i0 = m_pIndices[iFace * 3 + 0];
			DWORD i1 = m_pIndices[iFace * 3 + 1];
			DWORD i2 = m_pIndices[iFace * 3 + 2];

			m_pFaceNormal[iFace] = ComputeFaceNormal(i0,i1,i2);
		}
		return true;
	}
	void CreateVertexNormal()
	{
		InitFaceNormal();
		GenNormalLookUpTable();
		CalcPerNormalVertexFastLookUp();
	}
	bool CreateHeightMap(ID3D11DeviceContext* context, const TCHAR* szFileName)
	{
		D3DX11_IMAGE_INFO ImageInfo;
		D3DX11_IMAGE_LOAD_INFO ImageLoadInfo;
		ZeroMemory(&ImageLoadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
		ImageLoadInfo.CpuAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		ImageLoadInfo.Format = DXGI_FORMAT_FROM_FILE;
		ImageLoadInfo.pSrcInfo = &ImageInfo;
		ImageLoadInfo.Usage = D3D11_USAGE_STAGING;

		ID3D11Resource* pResource;
		D3DX11CreateTextureFromFile(g_pd3dDevice, szFileName, &ImageLoadInfo, NULL, &pResource, NULL);

		ID3D11Texture2D* Texture2D;
		pResource->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&Texture2D);
		SAFE_RELEASE(pResource);
		D3D11_TEXTURE2D_DESC desc2D;
		Texture2D->GetDesc(&desc2D);

		m_iWidth = desc2D.Width;
		m_iHeight = desc2D.Height;

		m_pHeightMap = new float[m_iWidth * m_iHeight];

		D3D11_MAPPED_SUBRESOURCE Mapped;
		if (SUCCEEDED(context->Map(Texture2D, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &Mapped)))
		{
			UCHAR* pTexel = (UCHAR*)Mapped.pData;
			for (UINT iCols = 0; iCols < desc2D.Height; iCols++)
			{
				UINT ColStart = iCols * Mapped.RowPitch;
				for (UINT iRows = 0; iRows < desc2D.Width; iRows++)
				{
					UINT RowStart = iRows * 4;
					UINT iRed = pTexel[RowStart + ColStart];
					m_pHeightMap[iCols*desc2D.Width + iRows] = iRed * 0.1f;
				}
			}
			context->Unmap(Texture2D, D3D11CalcSubresource(0, 0, 1));
		}
		SAFE_RELEASE(Texture2D);
		return true;
	}
	bool Create( ID3D11DeviceContext* context, int iWidth, int iHeight, int iCellSize, const TCHAR* szFileName = 0)
	{
		m_iVertexSize = iWidth * iHeight;
		m_iNumCols = iWidth;
		m_iNumRows = iHeight;
		m_iCellSize = iCellSize;
		m_iCellCols = iWidth - 1;
		m_iCellRows = iHeight - 1;
		m_fFaceSize = (iWidth - 1) * (iHeight - 1) * 2;

		float fHalfCols = (iWidth - 1) * iCellSize / 2.0f;
		float fHalfRows = (iHeight - 1) * iCellSize / 2.0f;
		float fOffSetX = 1.0f / (iWidth - 1);
		float fOffSetZ = 1.0f / (iHeight - 1);

		m_pVertices.resize(m_iVertexSize);		
		float fHeight = 0.0f;
		for (int iCols = 0; iCols < iHeight; iCols++)
		{
			for (int iRows = 0; iRows < iWidth; iRows++)
			{
				int iIndex = iCols * iWidth + iRows;

				if (m_pHeightMap == NULL) return false;
				fHeight = m_pHeightMap[iCols * iWidth + iRows];

				m_pVertices[iIndex].p = D3DXVECTOR3((iRows * m_iCellSize) - fHalfRows, fHeight, (-iCols * m_iCellSize) + fHalfCols);
				m_pVertices[iIndex].n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				m_pVertices[iIndex].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				m_pVertices[iIndex].t = D3DXVECTOR2(fOffSetX * iRows, fOffSetZ * iCols);
			}
		}
		m_pIndices.resize(m_fFaceSize * 3);
		int iIndex = 0;
		for (int iCols = 0; iCols < m_iCellCols; iCols++)
		{
			for (int iRows = 0; iRows < m_iCellRows; iRows++)
			{
				//0,1,2,   2,1,3
				m_pIndices[iIndex++] = (iCols * iWidth) + iRows;      
				m_pIndices[iIndex++] = (iCols * iWidth) + iRows + 1;
				m_pIndices[iIndex++] = ((iCols + 1) * iWidth) + iRows;

				m_pIndices[iIndex++] = ((iCols + 1) * iWidth) + iRows;
				m_pIndices[iIndex++] = (iCols * iWidth) + iRows + 1;
				m_pIndices[iIndex++] = ((iCols + 1) * iWidth) + iRows + 1;
			}
		}
		m_dxObj.m_iVertexNum = m_pVertices.size();
		m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);

		m_dxObj.m_iIndexNum = m_pIndices.size();
		m_dxObj.m_iIndexSize = sizeof(DWORD);

		CreateVertexNormal();

		m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, &m_pVertices.at(0), m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
		m_dxObj.m_pIndexBuffer = CreateIndexBuffer(g_pd3dDevice, &m_pIndices.at(0), m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum);
		m_dxObj.m_pConstantBuffer = CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1);
		m_dxObj.m_pVS = DX::LoadVertexShader(g_pd3dDevice, L"../../data/shader/shape.vsh", &m_dxObj.m_BlobVS);
		m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", &m_dxObj.m_BlobPS);

		if (szFileName != NULL)
		{
			int iTexture = I_TexMgr.Add(g_pd3dDevice, szFileName);
			m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTexture);
		}

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
};

class Sample : public JCore
{
public:
	SampleMap_01 m_Map;
	JShape*    m_pBox;
	D3DXMATRIX m_matWorldBox;
	BackViewCamera m_BVCamera;
public:
	bool Init()
	{
		m_Map.CreateHeightMap(GetContext(), L"../../data/Map512.png");
		m_Map.Create(GetContext(), m_Map.m_iWidth, m_Map.m_iHeight, 1);// , L"../../data/Castle.jpg");

		m_pBox = new JBoxShape(CENTER);
		m_pBox->Init();
		//int iTexture = I_TexMgr.Add(GetDevice(), L"../../data/UserInterface/ui_pet_btn_1_off.png");
		//m_pBox->m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTexture);

		D3DXMatrixIdentity(&m_matWorldBox);

		D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 100.0f, -10.0f);
		D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_BVCamera.SetViewMatrix(vPos, vTarget, vUp);
		m_BVCamera.SetProjMatrix(D3DX_PI* 0.25f,
			(float)g_rtClient.right / (float)g_rtClient.bottom,
			1.0f, 1000.0f);
		return true;
	}
	bool Frame()
	{
		if (I_Input.KeyCheck(VK_UP) == KEY_PUSH || I_Input.KeyCheck(VK_UP) == KEY_HOLD)
		{
			m_pBox->m_vPos -= m_pBox->m_vLook * g_fSecPerFrame * 10.0f;
		}
		if (I_Input.KeyCheck(VK_DOWN) == KEY_PUSH || I_Input.KeyCheck(VK_DOWN) == KEY_HOLD)
		{
			m_pBox->m_vPos += m_pBox->m_vLook * g_fSecPerFrame * 10.0f;
		}
		if (I_Input.KeyCheck(VK_RIGHT) == KEY_PUSH || I_Input.KeyCheck(VK_RIGHT) == KEY_HOLD)
		{
			m_pBox->m_vPos += m_pBox->m_vRight * g_fSecPerFrame * 10.0f;
		}
		if (I_Input.KeyCheck(VK_LEFT) == KEY_PUSH || I_Input.KeyCheck(VK_LEFT) == KEY_HOLD)
		{
			m_pBox->m_vPos -= m_pBox->m_vRight * g_fSecPerFrame * 10.0f;
		}
		m_matWorldBox._41 = m_pBox->m_vPos.x;
		m_matWorldBox._43 = m_pBox->m_vPos.z;
		m_matWorldBox._42 = m_Map.GetHeight(m_pBox->m_vPos.x, m_pBox->m_vPos.z);

		D3DXVECTOR3 vPos = m_pBox->m_vPos + D3DXVECTOR3(0, 0, 1);
		D3DXVECTOR3 vAt = m_pBox->m_vPos;
		D3DXVECTOR3 vUp = D3DXVECTOR3(0, 1, 0);
		vPos.y = m_Map.GetHeight(vPos.x, vPos.z);
		m_BVCamera.SetViewMatrix(vPos, vAt, vUp);
		return true;
	}
	bool Render()
	{
		m_Map.SetMatrix(NULL, &m_BVCamera.m_matView, &m_BVCamera.m_matProj);
		m_Map.Render(GetContext());

		m_pBox->SetMatrix(&m_matWorldBox, &m_BVCamera.m_matView, &m_BVCamera.m_matProj);
		m_pBox->Render(GetContext());
		return true;
	}
	bool Release()
	{
		m_Map.Release();
		m_pBox->Release();
		return true;
	}
};
RUN;