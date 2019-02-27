#include "dllStd.h"

extern ClassDesc2* GetExportDesc();

HINSTANCE hInstance;

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG fReason, LPVOID)
{
	if (fReason == DLL_PROCESS_ATTACH)
	{
		hInstance = hInst;
		DisableThreadLibraryCalls(hInst);
	}
	return TRUE;
}


__declspec(dllexport) const TCHAR* LibDescription()
{
	return _T("HExport v100");
}
__declspec(dllexport) int LibNumberClasses()
{
	return 1;
}

__declspec(dllexport) ClassDesc* LibClassDesc(int i)
{
	switch (i) {
	case 0: return GetExportDesc();
	default: return 0;
	}
}

__declspec(dllexport) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}

__declspec(dllexport) int LibInitialize(void)
{
	return TRUE;
}

__declspec(dllexport) int LibShutdown(void)
{
	return TRUE;
}

TCHAR *GetString(int id)
{
	static TCHAR buf[256];

	if (hInstance)
		return LoadString(hInstance, id, buf, _countof(buf)) ? buf : NULL;
	return NULL;
}
