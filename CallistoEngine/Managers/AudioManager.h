#pragma once
#include "irrKlang/irrKlang.h"

using namespace irrklang;

class AudioManager
{

	static AudioManager* mInstance;
	ISoundEngine* mSoundEngine;

	AudioManager();
public:

	static AudioManager& GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new AudioManager();

		return *mInstance;
	}

	~AudioManager();

	// void Initialise();

	void PlaySound(const char* pFile, bool pLoop = false);
	void Play3DSound(const char* pFile, float x, float y, float z, bool pLoop = false);
	void SetListenerPosition(float x, float y, float z);

	//void Update(double deltaTime);
};


