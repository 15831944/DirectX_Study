#pragma once
#include "UserInterface.h"
class ImageCtrl : public UserInterface
{
public:
	bool Create();
	bool Render(ID3D11DeviceContext* context, UINT iVertexSize = 0, UINT iCount = 0);
public:
	ImageCtrl();
	virtual ~ImageCtrl();
};

