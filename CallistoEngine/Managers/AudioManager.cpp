#include "AudioManager.h"

AudioManager* AudioManager::mInstance = nullptr;

AudioManager::AudioManager()
{
	mSoundEngine = createIrrKlangDevice();
}

AudioManager::~AudioManager()
{
	mSoundEngine->drop();
}

void AudioManager::PlaySound(const char* pFile, bool pLoop)
{
	mSoundEngine->play2D(pFile, pLoop);
}
