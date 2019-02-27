#pragma once
#include "UserInterface.h"
#include "JState.h"
class SpriteCtrl : public UserInterface
{
public:
	bool Create();
	bool Frame();
	bool PreRender(ID3D11DeviceContext* context, UINT iVertexSize);
	bool Render(ID3D11DeviceContext* context, UINT iVertexSize = 0, UINT iCount = 0);
	bool PostRender(ID3D11DeviceContext* context, UINT iCount);
public:
	SpriteCtrl();
	virtual ~SpriteCtrl();
};

