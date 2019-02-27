#include "JCore.h"
#include "JMap.h"
#include "JBoxShape.h"
/*
	�ؽ�ó��ǥ ���� �ؽ��ĸ� ���̱� (�ؽ��� �ڵ�����)
	�ؽ��ĺ�ȯ��� -> �ؽ�ó���� SRT, Ÿ�ϸ�
	* ī�޶� �����̴°͵� ��� -> 
	���� ��ǥ, ����ǥ, ����ǥ�� �ݻ纤��
	// TCI_0 ���̴�
*/
/*
	���÷��� ::  �׸���, ���伥  
*/
/*
	������ũ, �׼����̼�, ��ǻ�� ���̴�, ��Ƽ�����巻��, max sdk�� �̿��� plugin����(������Ʈ��)
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
	1) dll -> �������̺귯��, ��������Ʈ, �������� ��ȣüũ (������Ʈ ����)
	2) BOOL WINAPI DllMain() -> dll�� ����
	extern "C"
		typedef void (CALLBACK *FNCALL)();
		FNCALL fp;
		fp =(FNCALL)GetProcAddress();

		HMODULE = LoadLibrary()

		FreeLibrary();
*/
/*
	�ƽ����� plugins -> dll�־�

	__declspec(dllexport)
	const TCHAR* LibDescription()
	help -> CreateID
	�Ӽ� -> ����� -> ��� -> �ƽ��������ϰ��
	������� -> max plugin
	interface i => max����ɻ�밡��
	*/