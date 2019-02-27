#pragma once
#include "JTransform.h"
class JUserInterface
{
public:
	JTransform m_Transform;
public:
	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
public:
	virtual bool Init();
public:
	JUserInterface();
	virtual ~JUserInterface();
};