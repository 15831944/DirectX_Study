#pragma once
class JSampler
{
public:
	ID3D11SamplerState * m_pSS[3];
public:
	JSampler();
	virtual ~JSampler();
};

