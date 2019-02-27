#include "JCore.h"
#include "AseObject.h"
class Sample : public JCore
{
public:
	AseObject pr;
public:
	bool Init()
	{
		pr.Load(g_pd3dDevice, L"../../data/box.ase");
		return true;
	}
	bool Frame()
	{
		pr.Frame();
		return true;
	}
	bool Render()
	{
		pr.Render(GetContext());
		return true;
	}
	bool Release()
	{
		pr.Release();
		return true;
	}
};
RUN;