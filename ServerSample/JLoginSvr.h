#pragma once
//#include "JUserMgr.h"
class JLoginSvr //: public JUserMgr
{
public: 
	//SOCKET m_hDBSocket;
public:
	bool PreInit();
	bool Run();
public:
	JLoginSvr();
	virtual ~JLoginSvr();
};

