#include "JServer.h"
void main()
{
	JServer svr;
	svr.Set(10000);
	svr.Finish();
	svr.Release();
}