#pragma once
#include "JServerObject.h"
class JSynchronize
{
public:
	JServerObject * m_pObject;
public:
	JSynchronize(JServerObject* pObj);
	virtual ~JSynchronize();
};

