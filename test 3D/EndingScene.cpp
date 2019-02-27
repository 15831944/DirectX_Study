#include "EndingScene.h"



bool EndingScene::Init() noexcept
{



	return true;
}


// 프레임
bool EndingScene::Frame() noexcept
{
	DxManager::Get().Frame();
	ObjectManager::Get().Frame(Timer::SPF, Timer::AccumulateTime);
	SoundManager::Get().Frame();
	return true;
}

// 랜더
bool EndingScene::Render() noexcept
{
	DxManager::Get().Render();
	ObjectManager::Get().Render(DxManager::Get().GetDContext());
	SoundManager::Get().Render();
	return true;
}

// 릴리즈
bool EndingScene::Release() noexcept
{
	// 릴리즈
	ObjectManager::Get().Release();
	//DxManager::Get().Release();
	//SoundManager::Get().Release();
	return true;
}