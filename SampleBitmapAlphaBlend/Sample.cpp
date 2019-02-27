#include "JCore.h"
/*
	TransparentBit == 지정컬러키제거 
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