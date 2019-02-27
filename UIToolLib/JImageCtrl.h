#pragma once
#include "JPanel.h"
#include "JPlane.h"
#include "JTextureMgr.h"
namespace UI
{
	class JImageCtrl : public JPanel
	{
	public:
		JPlane*				m_pShape;
		JTexture*			m_pTexture;
		vector<int>			m_pIndexList; // TextureMgr 반환 Index 저장
	public:
		virtual bool Create(ID3D11Device* pDevice, const char* PSName = "PS", const TCHAR* szShaderName = L"../../Data/Shader/DefaultUI.hlsl");
		void SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
		bool SetTexture(ID3D11Device* pDevice, const TCHAR* txName = NULL);
	public:
		void Update();
	public:
		bool Frame(const float& spf, const float& accTime)noexcept override;
		bool Render(ID3D11DeviceContext* pContext)noexcept override;
	public:
		JImageCtrl(wstring NodeName) : JPanel(NodeName) 
		{
			m_pShape = new JPlane();
		};
		~JImageCtrl() {};
	};
}