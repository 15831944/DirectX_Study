#include "JLoginSvr.h"

bool JLoginSvr::PreInit()
{
	// DB서버 커넥트 작업~~~
	//m_hDBSocket = socket(AF_INet, SOCK_STReAM ~);
	//connect(m_hDBSocket, ~~);
	return true;
}
bool JLoginSvr::Run()
{
	return true;
}

JLoginSvr::JLoginSvr()
{
}


JLoginSvr::~JLoginSvr()
{
}
