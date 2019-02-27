#include "JIOCP.h"
#include <conio.h>
void main()
{
	JIOCP iocp;
	iocp.Init();
	iocp.Frame();
	iocp.Release();
	_getch();
}