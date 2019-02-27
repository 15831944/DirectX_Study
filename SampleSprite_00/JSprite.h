#pragma once
#include "JPlaneShape.h"
struct JRectUV
{
	D3DXVECTOR4 vUV;
	RECT rt;
};
class JSprite : public JPlaneShape
{
public:

public:
	JSprite();
	virtual ~JSprite();
};

