#pragma once
#include "JStd.h"
class HPlane
{
public:
	float fA, fB, fC, fD;
public:
	bool CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2);
public:
	HPlane();
	~HPlane();
};

