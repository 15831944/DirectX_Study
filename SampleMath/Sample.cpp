#include "JCore.h"
#include "JDxHelper.h"
using namespace DX;

class Sample : public JCore
{
public:
	bool Init()
	{
		return true;
	}
	bool Frame()
	{
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
	if (core.SetWindow(hInstance, 800, 600, L"DirectX Sample Box3D"))
	{
		core.Run();
		return 0;
	}
	return 1;
}