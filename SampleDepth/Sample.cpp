#include "JCore.h"
#include "JDxObject.h"
////////////////////////
// wrl.h //스마트포인터(인터페이스)
// namespace Microsoft::WRL;
// ComPtr<devide> device
// device.Get() -> device*
// device.GetAddr() -> device**
// attach()
//////////////////////////
class Sample : public JCore
{
public:
	JDxObject Obj;
	JDxObject Obj2;
public:
	bool Init()
	{
		Obj.SetRect(0, 0, 200, 200 , 0.7f);
		Obj.Create(g_pd3dDevice, "VS", "PS1");
		Obj.CreateVertexBuffer(g_pd3dDevice);
		Obj.Load(g_pd3dDevice, L"../../Data/Bitmap/BackGround.bmp");
		Obj2.SetRect(150, 150, 250, 250,0.5f);
		Obj2.Create(g_pd3dDevice, "VS", "PS1");
		Obj2.CreateVertexBuffer(g_pd3dDevice);
		Obj2.Load(g_pd3dDevice, L"../../Data/Bitmap/BackGround.bmp");
		return true;
	}
	bool Frame()
	{
		Obj.Frame();
		Obj2.Frame();
		return true;
	}
	bool Render()
	{
		Obj2.Render(GetContext());
		Obj.Render(GetContext());
		return true;
	}
	bool Release()
	{
		Obj.Release();
		Obj2.Release();
		return true;
	}
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