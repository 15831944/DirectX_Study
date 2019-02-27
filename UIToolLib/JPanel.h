#pragma once
#include "JTransform.h"
#include "GameObject.h"
namespace UI
{
	class JEvent;
	enum UIType
	{
		txNORMAL = 0, // Normal
		txHOVER,      // 올린상태
		txPRESS,      // 누른상태
	};
	/* JPanel 개념 */
	/* 하나의 이벤트에 실행되는 UI 또는 한번에 보여주는 UI 단위 */
	class JPanel : public JTransform, public GameObject
	{
	public:
		/* ======= Event ==========*/
		int					m_iCtrlType;
		JEvent*				m_pEvent;					// EventBind
	public:
		bool				m_bRender = true; // Render 여부 확인
		JPanel*				m_pParent = nullptr;
		wstring				m_ParentName;
		wstring				m_NodeName;
		vector<JPanel*>		m_pChildList;
	public:
		D3DXMATRIX			m_matWorld;
		D3DXMATRIX			m_matView;
		D3DXMATRIX			m_matProj;
	public:
		bool BindEvent(JEvent* pEvent);
		bool SetParent(JPanel* pParent);
		void push_child(JPanel* pChild);
		void Update(); // worldmatrix update
	public:
		bool Init() noexcept override;
		bool Frame(const float& spf, const float& accTime) noexcept override;
		bool Render(ID3D11DeviceContext* pContext) noexcept override;
		bool Release() noexcept override;
	public:
		JPanel(wstring NodeName);
		virtual ~JPanel();
	};
}