// SpriteForm.cpp: 구현 파일
//

#include "stdafx.h"
#include "SampleUI.h"
#include "SpriteForm.h"
#include "afxdialogex.h"


// SpriteForm 대화 상자

IMPLEMENT_DYNAMIC(SpriteForm, CFormView)
SpriteForm* SpriteForm::CreateOne(CWnd* pParent)
{
	SpriteForm* pForm = new SpriteForm();
	pForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 500, 500), pParent, 0, NULL);
	return pForm;
}
SpriteForm::SpriteForm(CWnd* pParent /*=nullptr*/)
	: CFormView(IDD_SpriteForm)
	, m_NodeName(_T(""))
	, m_strParentName(_T(""))
	, m_ScaleX(_T("100"))
	, m_ScaleY(_T("100"))
	, m_ScaleZ(_T("1"))
	, m_RotateAngle(_T("0"))
	, m_TransX(_T("0"))
	, m_TransY(_T("0"))
	, m_TransZ(_T("0"))
	, m_SpriteSec(_T(""))
{

}

SpriteForm::~SpriteForm()
{
}

void SpriteForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDD_TextList, m_CtrlTextureList);
	DDX_Text(pDX, IDC_SpriteNodeName, m_NodeName);
	DDX_Text(pDX, IDC_SpriteParentName, m_strParentName);
	DDX_Text(pDX, IDC_SpriteScaleX, m_ScaleX);
	DDX_Text(pDX, IDC_SpriteScaleY, m_ScaleY);
	DDX_Text(pDX, IDC_SpriteScaleZ, m_ScaleZ);
	DDX_Text(pDX, IDC_SpriteAngle, m_RotateAngle);
	DDX_Text(pDX, IDC_SpriteTransX, m_TransX);
	DDX_Text(pDX, IDC_SpriteTransY, m_TransY);
	DDX_Text(pDX, IDC_SpriteTransZ, m_TransZ);
	DDX_Text(pDX, IDC_SpriteSecond, m_SpriteSec);
}


BEGIN_MESSAGE_MAP(SpriteForm, CFormView)
	ON_LBN_SELCHANGE(IDD_TextList, &SpriteForm::OnLbnSelchangeTextlist)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &SpriteForm::OnEnChangeMfceditbrowse1)
	ON_LBN_DBLCLK(IDD_TextList, &SpriteForm::OnLbnDblclkTextlist)
	ON_BN_CLICKED(IDC_CreateSprite, &SpriteForm::OnBnClickedCreatesprite)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE2, &SpriteForm::OnEnChangeMfceditbrowse2)
END_MESSAGE_MAP()


// SpriteForm 메시지 처리기


void SpriteForm::OnLbnSelchangeTextlist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void SpriteForm::OnEnChangeMfceditbrowse1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void SpriteForm::OnLbnDblclkTextlist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString DelTexName;
	CSampleUIApp* pApp = (CSampleUIApp*)AfxGetApp();
	int iIndex = m_CtrlTextureList.GetCurSel();
	m_CtrlTextureList.GetText(iIndex, DelTexName);
	pApp->m_Sample.DeleteTexture(DelTexName);
	m_CtrlTextureList.DeleteString(iIndex);
}


void SpriteForm::OnBnClickedCreatesprite()
{
	 //TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	float SclX = 0, SclY = 0, SclZ = 0;
	float fAngle = 0, fSec = 0;
	float TransX = 0, TransY = 0, TransZ = 0;
	CString NodeName, ParentName;
	D3DXMATRIX Scl, Rot, Trans;
	D3DXMatrixIdentity(&Scl);
	D3DXMatrixIdentity(&Rot);
	D3DXMatrixIdentity(&Trans);
	GetDlgItemText(IDC_SpriteScaleX, m_ScaleX);
	if (m_ScaleX != L"")
		SclX = _wtoi(m_ScaleX);
	GetDlgItemText(IDC_SpriteScaleY, m_ScaleY);
	if (m_ScaleY != L"")
		SclY = _wtoi(m_ScaleY);
	GetDlgItemText(IDC_SpriteScaleZ, m_ScaleZ);
	if (m_ScaleZ != L"")
		SclZ = _wtoi(m_ScaleZ);
	GetDlgItemText(IDC_SpriteAngle, m_RotateAngle);
	if (m_RotateAngle != L"")
		fAngle = _wtoi(m_RotateAngle);
	GetDlgItemText(IDC_SpriteTransX, m_TransX);
	if (m_TransX != L"")
		TransX = _wtoi(m_TransX);
	GetDlgItemText(IDC_SpriteTransY, m_TransY);
	if (m_TransY != L"")
		TransY = _wtoi(m_TransY);
	GetDlgItemText(IDC_SpriteTransZ, m_TransZ);
	if (m_TransZ != L"")
		TransZ = _wtoi(m_TransZ);
	GetDlgItemText(IDC_SpriteSecond, m_SpriteSec);
	if (m_TransZ != L"")
		fSec = _wtoi(m_SpriteSec);
	GetDlgItemText(IDC_SpriteParentName, m_strParentName);
	if (m_strParentName != L"")
		ParentName = m_strParentName;
	GetDlgItemText(IDC_SpriteNodeName, m_NodeName);
	if (m_NodeName == L"")
	{
		AfxMessageBox(L"Node Name Error!");
	}
	else
	{
		NodeName = m_NodeName;
		D3DXMatrixScaling(&Scl, SclX, SclY, SclZ);
		float fRadian = fAngle * (3.141592f / 180.0f);
		D3DXMatrixRotationZ(&Rot, fRadian);
		Trans._41 = TransX;
		Trans._42 = TransY;
		Trans._43 = TransZ;
		CSampleUIApp* pApp = (CSampleUIApp*)AfxGetApp();
		pApp->m_Sample.CreateSprite(Scl, Rot, Trans, NodeName, ParentName);
		pApp->m_Sample.m_pCurrentPlane->m_fSec = fSec;
		pApp->m_Sample.m_pCurrentPlane->m_iStart = 0;
		if (pApp->m_Sample.m_pCurrentPlane)
		{
			for (int iSprite = 0; iSprite < m_SpriteList.size(); iSprite++)
			{
				CString strTexName = m_SpriteList[iSprite];
				pApp->m_Sample.LoadMultyTexture(strTexName);
				strTexName = pApp->m_Sample.PathDivide(strTexName);
				pApp->m_Sample.m_pCurrentPlane->m_strTexName = strTexName;
			}
		}
		else
		{
			AfxMessageBox(L"생성된 플랜이 없거나 어떠한 플랜도 클릭하지 않았습니다.");
		}
		m_SpriteList.clear();
		m_CtrlTextureList.ResetContent();
	}
}


void SpriteForm::OnEnChangeMfceditbrowse2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTexName;
	CSampleUIApp* pApp = (CSampleUIApp*)AfxGetApp();
	GetDlgItemText(IDC_MFCEDITBROWSE2, strTexName);
	m_SpriteList.push_back(strTexName);
	strTexName = pApp->m_Sample.PathDivide(strTexName);
	m_CtrlTextureList.AddString(strTexName);
}
