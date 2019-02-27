#include "stdafx.h"
#include "JSample.h"
bool JSample::Init()
{
	return true;
}
bool JSample::Frame()
{
	return true;
}
bool JSample::Render()
{
	return true;
}
bool JSample::Release()
{
	return true;
}
bool JSample::Run()
{
	GameFrame();
	GameRender();
	return true;
}
JSample::JSample()
{
}


JSample::~JSample()
{
}
