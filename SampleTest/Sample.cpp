#include "JCore.h"
#include "JMap.h"
#include "JBoxShape.h"
/*
	텍스처좌표 없이 텍스쳐를 붙이기 (텍스쳐 자동생성)
	텍스쳐변환행렬 -> 텍스처에도 SRT, 타일링
	* 카메라 움직이는것도 고려 -> 
	월드 좌표, 뷰좌표, 뷰좌표의 반사벡터
	// TCI_0 쉐이더
*/
/*
	스플래팅 ::  그림판, 포토샵  
*/
/*
	동적링크, 테셀레이션, 컴퓨터 쉐이더, 멀티스레드렌더, max sdk를 이용한 plugin제작(오브젝트모델)
*/
class Sample : public JCore
{
public:
	shared_ptr<JMap> map;
	JBoxShape* box;
	JBoxShape* Shadow;
	D3DXMATRIX boxWorld;
public:
	bool Init()
	{
		map = make_shared<JMap>();
		map->Create(GetDevice(), 32, 32, 1);
		map->m_dxObj.m_pTexture = I_TexMgr.GetPtr(I_TexMgr.Add(GetDevice(), L"../../Data/Castle.jpg"));
		map->ChangedPixelShader("PSMeshColor");
		map->m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);

		box = new JBoxShape();
		box->Init();
		box->ChangedPixelShader("PSTexture");

		Shadow = new JBoxShape();
		Shadow->Init();
		Shadow->ChangedPixelShader("PSMeshColor");
		Shadow->m_cbData.vColor = D3DXVECTOR4(0, 0, 0, 1.0f);

		D3DXMatrixTranslation(&boxWorld, 0.0f, 5.0f, 0.0f);
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		GetContext()->OMSetBlendState(JState::g_pNoAlphaBlend, 0, -1);
		/* map */
		map->SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		map->Render(GetContext());

		/* box */
		box->SetMatrix(&boxWorld, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		box->Render(GetContext());

		/* shadow */
		D3DXVECTOR3 vLight(5,10,5);
		D3DXVECTOR4 pLight(vLight.x, vLight.y, vLight.z, 1.0f);
		D3DXPLANE pPlane(0, 1, 0, -0.01f);

		D3DXMATRIX matShadow, ShadowWorld;
		D3DXMatrixShadow(&matShadow, &pLight, &pPlane);

		ShadowWorld = boxWorld * matShadow;
		Shadow->SetMatrix(&ShadowWorld, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		Shadow->Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;

/*
	1) dll -> 동적라이브러리, 빈프로젝트, 내보내기 기호체크 (프로젝트 생성)
	2) BOOL WINAPI DllMain() -> dll의 시작
	extern "C"
		typedef void (CALLBACK *FNCALL)();
		FNCALL fp;
		fp =(FNCALL)GetProcAddress();

		HMODULE = LoadLibrary()

		FreeLibrary();
*/
/*
	맥스폴더 plugins -> dll넣어

	__declspec(dllexport)
	const TCHAR* LibDescription()
	help -> CreateID
	속성 -> 디버그 -> 명령 -> 맥스실행파일경로
	출력파일 -> max plugin
	interface i => max모든기능사용가능
	*/