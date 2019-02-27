#include "JPlane.h"
#include "JSelect.h"
#include "Input.h"

namespace UI
{
	bool JPlane::CheckPicking(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
	{
		I_Select.SetMatrix(pWorld, pView, pProj,
			Input::GetCursor(), (float)Window::getClientRect().right, (float)Window::getClientRect().bottom);
		for (int iFace = 0; iFace < 2; iFace++)
		{
			D3DXVECTOR3 v0, v1, v2;
			v0 = m_pVertices[m_pIndices[iFace * 3 + 0]].p;
			v1 = m_pVertices[m_pIndices[iFace * 3 + 1]].p;
			v2 = m_pVertices[m_pIndices[iFace * 3 + 2]].p;

			if (I_Select.ChkPick(v0, v1, v2))
			{
				m_bHovered = true;
				if (Input::GetMouseState(EMouseButton::Left) == EKeyState::DOWN)
					m_bClicked = true;
				else 
					m_bClicked = false;
				if (Input::GetMouseState(EMouseButton::Left) == EKeyState::HOLD)
					m_bPressed = true;
				else 
					m_bPressed = false;
				return true;
			}
		}
		m_bClicked = false;
		m_bPressed = false;
		m_bHovered = false;
		return false;
	}
	bool JPlane::Frame()
	{
		return true;
	}
	bool JPlane::PreRender(ID3D11DeviceContext* pContext)
	{
		JModel::PreRender(pContext);
		return true;
	}
	bool JPlane::Render(ID3D11DeviceContext* pContext, JTexture* pTexture)
	{
		this->PreRender(pContext);
		{
			if(pTexture != nullptr)
				pContext->PSSetShaderResources(0, 1, &pTexture->m_pSRV);
			pContext->UpdateSubresource(JPlane::m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
		}
		this->PostRender(pContext);
		return true;
	}
	bool JPlane::PostRender(ID3D11DeviceContext* pContext)
	{
		JModel::PostRender(pContext);
		return true;
	}
	bool JPlane::Create(ID3D11Device* pDevice, const char* PSName, const TCHAR* szShaderName)
	{
		m_pVertices.resize(4);
		m_pVertices[0] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
		m_pVertices[1] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
		m_pVertices[2] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
		m_pVertices[3] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
		m_iVertexNum = (UINT)m_pVertices.size();
		m_iVertexSize = sizeof(UI::PNCT_VERTEX);

		m_pIndices.resize(6);
		m_pIndices[0] = 0; m_pIndices[1] = 1; m_pIndices[2] = 2;
		m_pIndices[3] = 0; m_pIndices[4] = 2; m_pIndices[5] = 3;
		m_iIndexNum = (UINT)m_pIndices.size();
		m_iIndexSize = sizeof(DWORD);

		m_pVertexBuffer = UI::CreateVertexBuffer(pDevice, &m_pVertices.at(0), m_iVertexSize, m_iVertexNum);
		m_pIndexBuffer = UI::CreateIndexBuffer(pDevice, &m_pIndices.at(0), m_iIndexSize, m_iIndexNum);
		m_pConstantBuffer = UI::CreateConstantBuffer(pDevice, &m_cbData, sizeof(VSCB), 1);
		m_pVS = UI::LoadVertexShader(pDevice, szShaderName, &m_BlobVS, "VS");
		m_pPS = UI::LoadPixelShader(pDevice, szShaderName, &m_BlobPS, PSName);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		int ElementCnt = sizeof(ied) / sizeof(ied[0]);
		m_pIL = UI::CreateLayout(pDevice, ied, ElementCnt, m_BlobVS);

		m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
		return true;
	}
	JPlane::JPlane()
	{
	}


	JPlane::~JPlane()
	{
	}
}