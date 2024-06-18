#include "AudioManager.h"
#include "../Game.h"
#include "../Vector.h"

AudioManager* AudioManager::mInstance = nullptr;

AudioManager::AudioManager()
{
	mSoundEngine = createIrrKlangDevice();
}

AudioManager::~AudioManager()
{
	mSoundEngine->drop();
}


// Plays sound from a file with bool to loop the sound
void AudioManager::PlaySound(const char* pFile, bool pLoop)
{
	mSoundEngine->play2D(pFile, pLoop);

}

void AudioManager::Play3DSound(const char* pFile, float x, float y, float z, bool pLoop)
{
	mSoundEngine->play3D(pFile, vec3df(x, y, z), pLoop);
	mSoundEngine->setSoundVolume(1);
	
}

void AudioManager::SetListenerPosition(float x, float y, float z)
{
	Vector3f vec = Game::GetGameCamera()->GetPosition();
	Vector3f dir = Game::GetGameCamera()->GetDirection();
	mSoundEngine->setListenerPosition( vec3df(vec.GetX(), vec.GetY(), vec.GetZ()), vec3df(dir.GetX(), dir.GetY(), dir.GetZ()));
}
