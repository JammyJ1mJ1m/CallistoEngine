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

	//void Update(double deltaTime);
};


