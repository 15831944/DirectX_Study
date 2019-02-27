#include "JCore.h"
#include "JMap.h"
class Sample : public JCore
{
public:
	
	std::map<int, int> map;
	std::pair<int, int> pair;
public:
	bool Init()
	{	
		return true;
	}
	bool Frame()
	{
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
	Sample() {}
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow)
{
	Sample core;
	if (core.SetWindow(hInstance, 800, 600, L"DirectX Sample"))
	{
		core.Run();
		return 0;
	}
	return 1;
}