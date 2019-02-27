#include "HPlane.h"
bool HPlane::CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	float fA, fB, fC, fD;
	D3DXVECTOR3 edge0 = v1 - v0;
	D3DXVECTOR3 edge1 = v2 - v0;
	D3DXVECTOR3 vNormal;
	D3DXVec3Cross(&vNormal, &edge0, &edge1);
	D3DXVec3Normalize(&vNormal, &vNormal);
	fA = vNormal.x;
	fB = vNormal.y;
	fC = vNormal.z;
	fD = -(fA * v0.x + fB * v0.y + fC * v0.z);
	return true;
}

HPlane::HPlane()
{
}


HPlane::~HPlane()
{
}
