#include "HWrite.h"
#define HExport_CLASS_ID Class_ID(0x53a65fb4, 0x70170af3)

class HExport : public UtilityObj
{
public:
	HWND			hPanel;
	IUtil			*iu;
	Interface		*ip;

	virtual void DeleteThis() { }
	virtual void BeginEditParams(Interface *ip, IUtil *iu);
	virtual void EndEditParams(Interface *ip, IUtil *iu);
	virtual void Init(HWND hWnd);
	virtual void Destroy(HWND hWnd);
	void SelectionSetChanged(Interface *ip, IUtil *iu);
public:
	static HExport* GetInstance() 
	{
		static HExport HExporter;
		return &HExporter;
	}
private:
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	HExport();
	virtual ~HExport();
};
#define I_Exp HExport::GetInstance()
class HExpUtilityClassDesc : public ClassDesc2
{
public:
	virtual int IsPublic() { return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) { return HExport::GetInstance(); }
	virtual const TCHAR *	ClassName() { return _T("3dsMaxJUtility"); }
	virtual SClass_ID SuperClassID() { return UTILITY_CLASS_ID; }
	virtual Class_ID ClassID() { return HExport_CLASS_ID; }
	virtual const TCHAR* Category() { return _T("HUtility"); }
	virtual const TCHAR* InternalName() { return _T("HUtility"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() { return hInstance; }					// returns owning module handle
};

ClassDesc2* GetExportDesc() {
	static HExpUtilityClassDesc HExpUtilityDesc;
	return &HExpUtilityDesc;
}

HExport::HExport()
	: hPanel(nullptr)
	, iu(nullptr)
{

}

HExport::~HExport()
{

}

void HExport::BeginEditParams(Interface* ip, IUtil* iu)
{
	this->iu = iu;
	this->ip = ip;
	hPanel = ip->AddRollupPage(hInstance, MAKEINTRESOURCE(IDD_HUtilityDlg),DlgProc,_T("Parameters"),0);
}

void HExport::EndEditParams(Interface* ip, IUtil*)
{
	this->iu = NULL;
	this->ip = NULL;
	this->iu = nullptr;
	ip->DeleteRollupPage(hPanel);
	hPanel = nullptr;
}
void HExport::Init(HWND hWnd)
{

}

void HExport::Destroy(HWND hWnd)
{
}

void HExport::SelectionSetChanged(Interface *ip, IUtil *iu)
{
}

INT_PTR CALLBACK HExport::DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		//HExport::GetInstance()->Init(hWnd);
		break;
	case WM_DESTROY:
		//HExport::GetInstance()->Destroy(hWnd);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_Export:
		{
			TSTR fileName =  HExport::GetInstance()->ip->GetCurFileName();
			I_HWrite.Init(fileName, I_Exp->ip);
		}
		}break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MOUSEMOVE:
		GetCOREInterface()->RollupMouseMessage(hWnd, msg, wParam, lParam);
		break;

	default:
		return 0;
	}
	return 1;
}
