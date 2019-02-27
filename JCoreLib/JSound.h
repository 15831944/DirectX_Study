#pragma once
#include "JStd.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment(lib,"fmod_vc.lib")
#pragma comment(lib,"fmod64_vc.lib")
using namespace FMOD;
// SOUND 0 :: OPENING
// SOUND 1 :: INGAME
// SOUND 2 :: BOMB
class JSound : public JSingleton<JSound>
{
public:
	friend class JSingleton<JSound>;
public:
	System * m_pSystem;
	Sound* m_pSound[3];
	Channel* m_pChannel[32];
	int m_iSoundList;
public:
	int Load(const char* pLoadSoundFile, bool bPlay = false);
	void Play(int iIndex);
	void Stop(int iIndex);
	void Paused(int iIndex);
	void Volume(int iIndex, bool bUp = true);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	JSound();
	virtual ~JSound();
};
#define I_Sound JSound::GetInstance()

