#include "JCore.h"
#include "JMap.h"
class Sample : public JCore
{
public:
	JMap* pMap;
public:
	bool Init()
	{
		pMap = new JMap();
		pMap->SetHeightTexture(GetContext(), L"../../data/256px-Concrete_wall_height.jpg");
		pMap->Create(GetDevice(), 256, 256, 1);
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		pMap->SetMatrix(NULL, GetView(), GetProj());
		pMap->Render(GetContext());
		return true;
	}
	bool Release()
	{
		pMap->Release();
		return true;
	}
};
RUN;