#include "JSound.h"
#include "JInput.h"

int JSound::Load(const char* pLoadSoundFile, bool bPlay)
{
	m_pSystem->createSound(pLoadSoundFile, FMOD_DEFAULT, 0, &m_pSound[m_iSoundList++]);
	if (bPlay == true)
	{
		m_pSystem->playSound(m_pSound[m_iSoundList - 1], 0, false, &m_pChannel[m_iSoundList - 1]);
	}
	return m_iSoundList - 1;
}
void JSound::Play(int iIndex)
{
	bool playing = false;
	if (iIndex == 2)
	{
		int i = 2;
		while (1)
		{
			if (m_pChannel[i]->isPlaying(&playing))
			{
				m_pSystem->playSound(m_pSound[iIndex], 0, false, &m_pChannel[i]);
				break;
			}
			if( i < 32) i++;
		}
	}
	else
	{
		if (m_pChannel[iIndex] != NULL)
			m_pChannel[iIndex]->isPlaying(&playing);
		if (playing == false)
		{
			m_pSystem->playSound(m_pSound[iIndex], 0, false, &m_pChannel[iIndex]);
		}
	}
}
void JSound::Stop(int iIndex)
{
	bool playing = false;
	if (m_pChannel != NULL)
		m_pChannel[iIndex]->isPlaying(&playing);
	if (playing == false)
	{
		m_pSystem->playSound(m_pSound[iIndex], 0, false, &m_pChannel[iIndex]);
		float m_fCurrentVolume;
		m_fCurrentVolume = 0.1f;
		m_pChannel[iIndex]->setVolume(m_fCurrentVolume);
	}
	else
		m_pChannel[iIndex]->stop();
}
void JSound::Paused(int iIndex)
{
	bool paused;
	m_pChannel[iIndex]->getPaused(&paused);
	m_pChannel[iIndex]->setPaused(!paused);
}
void JSound::Volume(int iIndex, bool bUp)
{
	float fCurrentVolume;
	m_pChannel[iIndex]->getVolume(&fCurrentVolume);
	if (bUp == true)
	{
		if (fCurrentVolume <= 1.0f)
			fCurrentVolume += g_fSecPerFrame;
	}
	else
	{
		if (fCurrentVolume >= 0.0f)
			fCurrentVolume -= g_fSecPerFrame;
	}
	m_pChannel[iIndex]->setVolume(fCurrentVolume);
}
bool JSound::Init()
{
	m_iSoundList = 0;
	System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	return true;
}
bool JSound::Frame()
{
	if (I_Input.KeyCheck(VK_HOME) == KEY_PUSH || I_Input.KeyCheck(VK_HOME) == KEY_HOLD)
	{
		Volume(0, true);
		Volume(1, true);
	}
	if (I_Input.KeyCheck(VK_END) == KEY_PUSH || I_Input.KeyCheck(VK_END) == KEY_HOLD)
	{
		Volume(0, false);
		Volume(1, false);
	}
	m_pSystem->update();
	return true;
}
bool JSound::Render()
{
	return true;
}
bool JSound::Release()
{
	for (int iSound = 0; iSound < 3; iSound++)
	{
		m_pSound[iSound]->release();
		m_pSound[iSound] = NULL;
	}
	m_pSystem->close();
	m_pSystem->release();
	return true;
}

JSound::JSound()
{
}


JSound::~JSound()
{
}
