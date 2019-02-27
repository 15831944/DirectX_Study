#pragma once
#include "JPlaneShape.h"
struct RECTUV
{
	D3DXVECTOR4 vUV;
	RECT rt;
};
class Sprite : public JPlaneShape
{
public:
	vector<int> m_pIndexList; // TextureMgr 반환 Index 저장
	int m_iCurrentIndex; // 현제 인덱스
	int m_iNumTexture; // 전체 텍스쳐 개수
	float m_fSecPerRender; //
	float m_fTime;
	float m_fAnimTime;
	float m_fElapseTime;
	RECT m_rtSet;
	vector<RECTUV> m_rtList;
	ID3D11ShaderResourceView* m_pSRV;
public:
	void SetRectAnimation(float fAnimTime, int iWidth = 1, int iWidthSize = 0, int iHeight = 1, int iHeightSize = 0);
	D3DXVECTOR4 SetUV(RECT& rt);
	void SetTextureArray(vector<T_STR> FileList);
	void Update(ID3D11DeviceContext* context, float& pfCurrentTimer, int& iApplyIndex, float fGlobalTime, float fElapsedTime);
	bool Create(bool bInstance = false, const char* szPSFunName = "PS", const char* szVSFunName = "VS", const TCHAR* szShaderName = L"../../Data/Shader/Default.hlsl");
	bool Frame(ID3D11DeviceContext* context, float fGlobalTime, float fElapsedTime);
	bool PreRender(ID3D11DeviceContext* context);
	bool Render(ID3D11DeviceContext* context);
	bool PostRender(ID3D11DeviceContext* context);
	bool RenderInstancing(ID3D11DeviceContext* context);
public:
	Sprite();
	virtual ~Sprite();
};

