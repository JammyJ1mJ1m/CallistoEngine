#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <iostream>
#include <fstream>
class Sound
{
	ALuint mBuffer;
	ALuint mSource;
	std::vector<char> mData;
	ALenum mFormat;
	ALsizei mFreq;
	bool loadFile(const std::string& filename);

public:

	Sound(const std::string& filename);
	~Sound();

	void Play();
	void Play3D(float x, float y, float z);
	void Stop();
	void SetLooping(bool pLoop);
};