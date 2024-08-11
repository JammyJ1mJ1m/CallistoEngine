#pragma once
#include "../toml.hpp"
#include <string>
#include <sstream>
#include <iostream>

struct Resolution
{
	int width;
	int height;
};

class DisplayManager
{
	Resolution mResolution;
	bool mFullscreen;
	bool mVSync;
	int mFov;
	bool mCursorEnabled;

	static DisplayManager* mInstance;

	DisplayManager() = default;

public:
	static DisplayManager& GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new DisplayManager();

		return *mInstance;
	}

	~DisplayManager() = default;

	void LoadConfig(std::string pFilename);

	void SetResolution(int pWidth, int pHeight) { mResolution.width = pWidth; mResolution.height = pHeight; }
	void SetFullscreen(bool pFullscreen) { mFullscreen = pFullscreen; }
	void SetVSync(bool pVSync) { mVSync = pVSync; }
	void SetFov(int pFov) { mFov = pFov; }

	int GetResolutionWidth() const { return mResolution.width; }
	int GetResolutionHeight() const { return mResolution.height; }
	bool GetFullscreen() const { return mFullscreen; }
	bool GetVSync() const { return mVSync; }
	int GetFov() const { return mFov; }

	void SetCursorEnabled(bool pEnabled) { mCursorEnabled = pEnabled; }
	const bool GetCursorEnabled() const { return mCursorEnabled; }
};