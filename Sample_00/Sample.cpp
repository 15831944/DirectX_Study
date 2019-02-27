#include "JCore.h"
#include "ime.h"
#pragma comment( lib, "IMM32.lib" )
class Sample : public JCore
{
public:
	void MsgEvent(MSG msg)
	{
	}
	bool Init()
	{
		return true;
	}
	bool Frame()
	{
		vector<int> sam;
		list<int> sam2;
		sam2.push_back(1);
		sam2.push_back(2);
		sam2.push_back(3);
		sam2.push_back(4);
		sam2.push_back(5);
		for(auto i : sam2)
		{
			int a = i;

			int b = a;
		}
		return true;
	}
	bool Render()
	{
		return true;
	}
	bool Release()
	{
		return true;
	}
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow) 
{
	Sample core; 
	if (core.SetWindow(hInstance, 800, 600, L"Windows Sample"))
	{
		core.Run();
		return 0;
	}
	return 1; 
}