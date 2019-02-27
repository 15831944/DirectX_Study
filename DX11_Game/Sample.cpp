#include "JCore.h"
#include "JDxSprite.h"
#include "JDxPlayer.h"
#include "JWrite.h"
class Sample : public JCore
{
public:
	//vector<JDxSprite> m_Sample;
	//JDxPlayer m_Sample2;
//	JDxSprite m_Sample;
	JDxObject m_Sample;
	JDxSprite m_Samplee;
	JDxSprite m_Samplee2;
	JDxSprite m_Samplee3;
	ID3D11BlendState* g_pAlphaBlend;
public:
	void CreateBlendState()
	{
		HRESULT hr;
		D3D11_BLEND_DESC BlendState;
		ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
		BlendState.AlphaToCoverageEnable = TRUE;
		BlendState.RenderTarget->BlendEnable = TRUE;
		BlendState.RenderTarget->BlendOp = D3D11_BLEND_OP_ADD;
		BlendState.RenderTarget->SrcBlend = D3D11_BLEND_SRC_ALPHA;
		BlendState.RenderTarget->DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		BlendState.RenderTarget->BlendOpAlpha = D3D11_BLEND_OP_ADD;
		BlendState.RenderTarget->SrcBlendAlpha = D3D11_BLEND_ZERO;
		BlendState.RenderTarget->DestBlendAlpha = D3D11_BLEND_ZERO;
		BlendState.RenderTarget->RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		FAILED(hr = g_pd3dDevice->CreateBlendState(&BlendState, &g_pAlphaBlend));
	}
	//bool DataLoad(const TCHAR* pszLoadFile)
	//{
	//	FILE* fp;
	//	_wfopen_s(&fp, pszLoadFile, L"rt");
	//	if (fp == NULL)
	//	{
	//		return false;
	//	}

	//	TCHAR Buffer[256] = { 0, };
	//	TCHAR Temp[256] = { 0, };
	//	TCHAR Bitmap[256] = { 0, };
	//	TCHAR BitmapMask[256] = { 0, };
	//	int iSpriteCnt = 0;
	//	int iEffectFrame = 0;
	//	fRECT rt_Tex = { 0,0,0,0 };
	//	fPOINT rt_UISize = { 0, };
	//	JDxObject Images;
	//	_fgetts(Buffer, _countof(Buffer), fp);
	//	_stscanf_s(Buffer, L"%f %f", &rt_UISize.x, &rt_UISize.y);
	//	_fgetts(Buffer, _countof(Buffer), fp);
	//	_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iEffectFrame);
	//	for (int frame = 0; frame < iEffectFrame; frame++)
	//	{
	//		_fgetts(Buffer, _countof(Buffer), fp);
	//		_stscanf_s(Buffer, L"%s", Bitmap, _countof(Bitmap));
	//		JDxObject sample;
	//		//sample.SetRect((g_rtWindow.right/2) - (rt_UISize.x / 2), 
	//		//				(g_rtWindow.bottom / 2) - (rt_UISize.y /2), 
	//		//				((g_rtWindow.right / 2) - (rt_UISize.x / 2)) + rt_UISize.x,
	//		//				((g_rtWindow.bottom / 2) - (rt_UISize.y / 2)) + rt_UISize.y);
	//		sample.SetRect(0,
	//			0,
	//			g_rtWindow.right,
	//			((g_rtWindow.bottom / 2) - (rt_UISize.y / 2)) + rt_UISize.y);
	//		sample.Create(g_pd3dDevice, "VS", "PS1");
	//		sample.CreateVertexBuffer(g_pd3dDevice);
	//		sample.Load(g_pd3dDevice, Bitmap);
	//		m_Sample.m_ImageSize = rt_UISize;
	//		m_Sample.m_iMax = iEffectFrame;
	//		m_Sample.m_ImageList.push_back(sample);
	//	}
	//	fclose(fp);
	//	return true;
	//}
	bool DataLoadOpening(const TCHAR* pszLoadFile)
	{
		FILE* fp;
		_wfopen_s(&fp, pszLoadFile, L"rt");
		if (fp == NULL)
		{
			return false;
		}

		TCHAR Buffer[256] = { 0, };
		TCHAR Temp[256] = { 0, };
		TCHAR Bitmap[256] = { 0, };
		TCHAR BitmapMask[256] = { 0, };
		int iSpriteCnt = 0;
		int iEffectFrame = 0;
		fRECT rt_Tex = { 0,0,0,0 };
		fPOINT rt_UISize = { 0, };
		JDxObject Images;
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%f %f", &rt_UISize.x, &rt_UISize.y);
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iEffectFrame);
		for (int frame = 0; frame < iEffectFrame; frame++)
		{
			_fgetts(Buffer, _countof(Buffer), fp);
			_stscanf_s(Buffer, L"%s", Bitmap, _countof(Bitmap));
			JDxObject sample;
			//sample.SetRect((g_rtWindow.right / 2) - (rt_UISize.x / 2),
			//	(g_rtWindow.bottom / 2) - (rt_UISize.y / 2),
			//	((g_rtWindow.right / 2) - (rt_UISize.x / 2)) + rt_UISize.x,
			//	((g_rtWindow.bottom / 2) - (rt_UISize.y / 2)) + rt_UISize.y);
			sample.SetRect(0, 0, g_rtWindow.right / 2, g_rtWindow.bottom);
			sample.Create(g_pd3dDevice, "VS", "PS1");
			sample.CreateVertexBuffer(g_pd3dDevice);
			sample.Load(g_pd3dDevice, Bitmap);
			m_Samplee.m_ImageSize = rt_UISize;
			m_Samplee.m_iMax = iEffectFrame;
			m_Samplee.m_ImageList.push_back(sample);
		}
		fclose(fp);
		return true;
	}
	bool DataLoadOpening2(const TCHAR* pszLoadFile)
	{
		FILE* fp;
		_wfopen_s(&fp, pszLoadFile, L"rt");
		if (fp == NULL)
		{
			return false;
		}

		TCHAR Buffer[256] = { 0, };
		TCHAR Temp[256] = { 0, };
		TCHAR Bitmap[256] = { 0, };
		TCHAR BitmapMask[256] = { 0, };
		int iSpriteCnt = 0;
		int iEffectFrame = 0;
		fRECT rt_Tex = { 0,0,0,0 };
		fPOINT rt_UISize = { 0, };
		JDxObject Images;
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%f %f", &rt_UISize.x, &rt_UISize.y);
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iEffectFrame);
		for (int frame = 0; frame < iEffectFrame; frame++)
		{
			_fgetts(Buffer, _countof(Buffer), fp);
			_stscanf_s(Buffer, L"%s", Bitmap, _countof(Bitmap));
			JDxObject sample;
			//sample.SetRect((g_rtWindow.right / 2) - (rt_UISize.x / 2),
			//	(g_rtWindow.bottom / 2) - (rt_UISize.y / 2),
			//	((g_rtWindow.right / 2) - (rt_UISize.x / 2)) + rt_UISize.x,
			//	((g_rtWindow.bottom / 2) - (rt_UISize.y / 2)) + rt_UISize.y);
			sample.SetRect(g_rtWindow.right, g_rtWindow.bottom, g_rtWindow.right / 2, 0);
			sample.Create(g_pd3dDevice, "VS", "PS1");
			sample.CreateVertexBuffer(g_pd3dDevice);
			sample.Load(g_pd3dDevice, Bitmap);
			m_Samplee2.m_ImageSize = rt_UISize;
			m_Samplee2.m_iMax = iEffectFrame;
			m_Samplee2.m_ImageList.push_back(sample);
		}
		fclose(fp);
		return true;
	}
	bool EffectData(const TCHAR* pszLoadFile)
	{
		FILE* fp;
		_wfopen_s(&fp, pszLoadFile, L"rt");
		if (fp == NULL)
		{
			return false;
		}

		TCHAR Buffer[256] = { 0, };
		TCHAR Temp[256] = { 0, };
		TCHAR Bitmap[256] = { 0, };
		TCHAR BitmapMask[256] = { 0, };
		int iSpriteCnt = 0;
		int iEffectFrame = 0;
		fRECT rt_Tex = { 0,0,0,0 };
		fPOINT rt_UISize = { 0, };
		JDxObject Images;
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%f %f", &rt_UISize.x, &rt_UISize.y);
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iEffectFrame);
		for (int frame = 0; frame < iEffectFrame; frame++)
		{
			_fgetts(Buffer, _countof(Buffer), fp);
			_stscanf_s(Buffer, L"%s%s", Bitmap, _countof(Bitmap), BitmapMask, _countof(BitmapMask));
			JDxObject sample;
			//sample.SetRect((g_rtWindow.right / 2) - (rt_UISize.x / 2),
			//	(g_rtWindow.bottom / 2) - (rt_UISize.y / 2),
			//	((g_rtWindow.right / 2) - (rt_UISize.x / 2)) + rt_UISize.x,
			//	((g_rtWindow.bottom / 2) - (rt_UISize.y / 2)) + rt_UISize.y);
			sample.SetRect(0,0,480,240);
			sample.Create(g_pd3dDevice, "VS", "PS1");
			sample.CreateVertexBuffer(g_pd3dDevice);
			sample.Load(g_pd3dDevice, Bitmap, BitmapMask);
			m_Samplee3.m_ImageSize = rt_UISize;
			m_Samplee3.m_iMax = iEffectFrame;
			m_Samplee3.m_ImageList.push_back(sample);
		}
		fclose(fp);
		return true;
	}
	bool Init()
	{
		//m_Sample2.Init();
		I_Sound.Load("../../sound/Apollo.mp3");
		//DataLoad(L"OpeningData.txt");
		DataLoadOpening(L"OpeningData2.txt");
		DataLoadOpening2(L"OpeningData2.txt");
		EffectData(L"EffectData.txt");
		CreateBlendState();
		//m_Samplee.m_bPlay = true;
		//m_Samplee2.m_bPlay = true;
		m_Sample.SetRect(0, 0, 960, 480);
		m_Sample.Create(g_pd3dDevice);
		m_Sample.CreateVertexBuffer(g_pd3dDevice);
		m_Sample.Load(g_pd3dDevice, L"../../Data/bitmap/BackGround1.bmp");
		return true;
	}
	bool Frame()
	{
		I_Sound.Play(0);
		//if (!m_Sample.m_bPlay)
		{
			m_Samplee.m_bPlay = true;
			m_Samplee.SetUp(7.0f); 
			m_Samplee.Frame(GetContext());

			m_Samplee2.m_bPlay = true;
			m_Samplee2.SetUp(7.0f);
			m_Samplee2.Frame(GetContext());

			m_Samplee3.m_bPlay = true;
			m_Samplee3.SetUp(1.0f);
			m_Samplee3.Frame(GetContext());
		}
		/*if (!m_Samplee.m_bPlay)
		{
			m_Sample.m_bPlay = true;
			m_Sample.SetUp(2.5f);
			m_Sample.Frame(GetContext());
		}*/
		//m_Sample2.Frame(GetContext());
		return true;
	}
	bool Render()
	{
		//m_Sample2.Render(GetContext()); 
		if (I_Input.KeyCheck(VK_F3) == KEY_PUSH || I_Input.KeyCheck(VK_F3) == KEY_HOLD)
			GetContext()->OMSetBlendState(0, 0, -1);
		else
			//GetContext()->OMSetBlendState(g_pAlphaBlend, 0, -1);

		//m_Sample.Render(GetContext());
		m_Samplee.Render(GetContext());
		m_Samplee2.Render(GetContext());
		//m_Samplee3.Render(GetContext());
		//m_Sample.Render(GetContext());
		//I_Write.RedDraw(L"G a m e  S t a r t", 30, {377,377,960,480});
		return true;
	}
	bool Release()
	{
	//	m_Sample2.Release();
		//m_Sample.Release();
		m_Samplee.Release();
		m_Samplee2.Release();
		m_Samplee3.Release();
		m_Sample.Release();
		return true;
	}
	Sample() {}
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow)
{
	Sample core;
	if (core.SetWindow(hInstance, 960, 480, L"DirectX Sample"))
	{
		core.Run();
		return 0;
	}
	return 1;
}