#pragma once
#include <windows.h>
#include <windowsx.h>
#include <time.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
//#include <wrl.h>
#include <dinput.h>
using namespace std;
//using namespace Microsoft::WRL;

typedef basic_string<TCHAR> T_STR;
typedef basic_string<wchar_t> W_STG;
typedef basic_string<char>  C_STR;
typedef vector<T_STR>		T_STR_VECTOR;

template<class T>
class JSingleton
{
public:
	static T& GetInstance()
	{
		static T SingleInstance;
		return SingleInstance;
	}
};