#pragma once
#include "JImageCtrl.h"
namespace UI
{
	class JSliderCtrl : public JPanel
	{
	public:
		/* 0 ~ 1°ª °íÁ¤ */
		float m_fValue;
		JImageCtrl* m_pSliderBar;
		JImageCtrl* m_pSliderHandle;
	public:
		bool Create(ID3D11Device* pDevice, const char* PSName = "PS", const TCHAR* szShaderName = L"../../Data/Shader/DefaultUI.hlsl");
		bool SetTexture(ID3D11Device* pDevice, const TCHAR* szBar, const TCHAR* szHandle);
		const float* GetValue();
	public:
		void Update();
		bool Frame(const float& spf, const float& accTime) noexcept override;
		bool Render(ID3D11DeviceContext* pContext)noexcept override;
	public:
		JSliderCtrl(wstring NodeName);
		virtual ~JSliderCtrl();
	};
}