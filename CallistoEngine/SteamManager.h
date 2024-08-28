#pragma once
#include <string>
#include <steam/steam_api.h>
#include <fstream>
#include <iostream>

class SteamManager
{
	int mAppId;
	bool mIsInitialized;
	int ReadAppID();
	const int GetAppID() { return mAppId; }
	const void SetAppID(int pAppID) { mAppId = pAppID; }

public:
	SteamManager();
	~SteamManager()
	{
		SteamAPI_Shutdown();
	};
	int initSteam();
	void UpdateSteamPresence(const char* pKey, const char* pValue);
	//void SetSteamPresence(const char* details, const char* state, const char* largeImageKey, const char* largeImageText, const char* smallImageKey, const char* smallImageText);
};