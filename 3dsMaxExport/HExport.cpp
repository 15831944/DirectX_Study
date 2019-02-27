#include "dllStd.h"
#include "ExpObject.h"
#include "ExpWrite.h"
#define HExport_CLASS_ID Class_ID(0x2dc541c, 0x499763e5)
/*
	1. 관리자 권한으로 실행 :: 빌드 후 명령 -> plugins 폴더로 복사됨
	2. 속성 -> C/C++ -> 언어 -> 준수모드 아니요
	3. 디버깅 -> 명령 -> 3dsMax.exe 경로 설정
	4. ID 생성 :: 3dsMax SDK Folder -> help -> gencid.exe
*/
class HExport : public SceneExport
{
public:
	int				ExtCount();					
	const TCHAR *	Ext(int n);					
	const TCHAR *	LongDesc();					
	const TCHAR *	ShortDesc();				
	const TCHAR *	AuthorName();				
	const TCHAR *	CopyrightMessage();			
	const TCHAR *	OtherMessage1();			
	const TCHAR *	OtherMessage2();			
	unsigned int	Version();					
	void			ShowAbout(HWND hWnd);		
	BOOL SupportsOptions(int ext, DWORD options);
	int  DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0);
public:
	HExport();
	virtual ~HExport();
};
class HExportDesc : public ClassDesc2
{
public:
	virtual int IsPublic() { return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) { return new HExport(); }
	virtual const TCHAR *	ClassName() { return _T("HExporter100"); }
	virtual SClass_ID SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() { return HExport_CLASS_ID; }
	virtual const TCHAR* Category() { return _T("HExporter"); }

	virtual const TCHAR* InternalName() { return _T("HClassDesc"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() { return hInstance; }					// returns owning module handle
};

ClassDesc2* GetExportDesc()
{
	static HExportDesc HExpDesc;
	return &HExpDesc;
}

HExport::HExport()
{

}

HExport::~HExport()
{

}

int HExport::ExtCount()
{
	return 1;
}

const TCHAR *HExport::Ext(int /*i*/)
{
	return _T("ash");
}

const TCHAR *HExport::LongDesc()
{
	return _T("HExpoter 1.0");
}

const TCHAR *HExport::ShortDesc()
{
	return _T("KGCA_HExport_V100");
}

const TCHAR *HExport::AuthorName()
{
	return _T("Ashi");
}

const TCHAR *HExport::CopyrightMessage()
{
	return _T("");
}

const TCHAR *HExport::OtherMessage1()
{
	return _T("");
}

const TCHAR *HExport::OtherMessage2()
{
	return _T("");
}

unsigned int HExport::Version()
{
	return 100;
}

void HExport::ShowAbout(HWND /*hWnd*/)
{

}

BOOL HExport::SupportsOptions(int /*ext*/, DWORD /*options*/)
{
	return TRUE;
}


int	HExport::DoExport(const TCHAR *name, ExpInterface *ei, Interface *i,
	BOOL suppressPrompts, DWORD options)
{
	//FILE* pFile = NULL;
	I_Writer.Initialize(i);
	I_Writer.RunExport(name);
	/*_tfopen_s(&pFile, name, L"wt");
	_ftprintf_s(pFile, L"HExport v100");*/
	//fclose(pFile);
	return TRUE;
}