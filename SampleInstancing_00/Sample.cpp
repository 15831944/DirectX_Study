#include "JCore.h"
/*
	������ 9���
*/
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