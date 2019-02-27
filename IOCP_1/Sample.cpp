#include "JIocp.h"

void main()
{
	JIocp iocp;
	iocp.Init();
	iocp.Frame();
	iocp.Release();
}