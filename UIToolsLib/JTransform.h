#pragma once
#include "JUIStd.h"
class JTransform
{
public:
	D3DXVECTOR3 m_vLocation;
	D3DXVECTOR3 m_vRotation;
	D3DXVECTOR3 m_vScale;
public:
	JTransform();
	virtual ~JTransform();
};