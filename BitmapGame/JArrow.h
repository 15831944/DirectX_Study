#pragma once
#include "JObject.h"
class JArrow : public JObject
{
public:
	bool m_bAttack;
	int  m_iCount;
public:
	bool Frame();
public:
	JArrow();
	virtual ~JArrow();
};