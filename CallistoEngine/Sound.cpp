#include "Sound.h"

bool Sound::loadFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file) return false;

	// Read the header
	char chunkId[4];
	file.read(chunkId, 4);
	if (std::strncmp(chunkId, "RIFF", 4) != 0) return false;

	file.seekg(22);
	short channels;
	file.read(reinterpret_cast<char*>(&channels), sizeof(short));
	file.read(reinterpret_cast<char*>(&mFreq), sizeof(int));

	short bitsPerSample;
	file.seekg(34);
	file.read(reinterpret_cast<char*>(&bitsPerSample), sizeof(short));

	if (channels == 1) {
		mFormat = (bitsPerSample == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
	}
	else {
		mFormat = (bitsPerSample == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
	}

	// Read data chunk
	file.seekg(40);
	int dataSize;
	file.read(reinterpret_cast<char*>(&dataSize), sizeof(int));

	mData.resize(dataSize);
	file.read(mData.data(), dataSize);

	return true;
	return false;
}

Sound::Sound(const std::string& filename)
{
	if (!loadFile(filename)) {
		std::cerr << "Failed to load WAV file" << std::endl;
		return;
	}

	alGenBuffers(1, &mBuffer);
	alBufferData(mBuffer, mFormat, mData.data(), mData.size(), mFreq);

	alGenSources(1, &mSource);
	alSourcei(mSource, AL_BUFFER, mBuffer);

	alSourcef(mSource, AL_PITCH, 1.0f);

	alSourcef(mSource, AL_GAIN, 100.0f);
}

Sound::~Sound()
{
	alDeleteSources(1, &mSource);
	alDeleteBuffers(1, &mBuffer);
}

void Sound::Play()
{
	alSourcePlay(mSource);

	// ALint state;
	// do {
	//     alGetSourcei(mSource, AL_SOURCE_STATE, &state);
	// } while (state == AL_PLAYING);
}

void Sound::Play3D(float x, float y, float z)
{
	alSource3f(mSource, AL_POSITION, x, y, z);
	alSourcePlay(mSource);


}

void Sound::Stop()
{
	alSourceStop(mSource);

}

void Sound::SetLooping(bool pLoop)
{
	alSourcei(mSource, AL_LOOPING, pLoop ? AL_TRUE : AL_FALSE);
}
