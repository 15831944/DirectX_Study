#include "JCore.h"
/*
	TransparentBit == �����÷�Ű���� 
*/
class JObject
{
public:
	bool Init()
	{
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		return true;
	}
	bool Release()

	{
		return true;
	}
	JObject();
	virtual ~JObject();
};
class Sample : public JCore
{
public:
	bool Init()
	{
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;