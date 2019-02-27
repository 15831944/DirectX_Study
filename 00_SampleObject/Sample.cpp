#include "JCore.h"
//#include "JCamera.h"
#include "PlaneShape.h"
#include "JSelect.h"
class Sample : public JCore
{
public:
	PlaneShape* pPlane;
	D3DXMATRIX matWorld;
	JSelect Clicked;
public:
	bool Init()
	{
		pPlane = new PlaneShape();
		pPlane->Create(GetDevice());
		pPlane->SetTexture(GetDevice(), L"../../Data/popup_normal.png");

		return true;
	}
	bool Frame()
	{
		float fTime = g_fSecPerFrame * 3.141592f * 10.0f;
		if (I_Input.KeyCheck('W') == KEY_PUSH || I_Input.KeyCheck('W') == KEY_HOLD)
		{
			pPlane->PlayMove(0, fTime, 0);
		}
		if (I_Input.KeyCheck('S') == KEY_PUSH || I_Input.KeyCheck('S') == KEY_HOLD)
		{
			pPlane->PlayMove(0, fTime, 0, false);
		}
		if (I_Input.KeyCheck('D') == KEY_PUSH || I_Input.KeyCheck('D') == KEY_HOLD)
		{
			pPlane->PlayMove(fTime, 0, 0);
		}
		if (I_Input.KeyCheck('A') == KEY_PUSH || I_Input.KeyCheck('A') == KEY_HOLD)
		{
			pPlane->PlayMove(fTime, 0, 0, false);
		}
		pPlane->Frame();

		if (Clicked.ClickCheck(*pPlane))
		{
			return true;
		}
		return true;
	}
	bool Render()
	{
		JState::SetAlphaBlendState(GetContext(), JState::g_pAlphaBlend);
		JState::SetDSState(GetContext(), JState::g_pEnableDSS);
		JState::SetRSState(GetContext(), JState::g_pRSNoneCullSolid);


		pPlane->Render(GetContext());
		return true;
	}
	bool Release()
	{
		pPlane->Release();
		return true;
	}
};
RUN;