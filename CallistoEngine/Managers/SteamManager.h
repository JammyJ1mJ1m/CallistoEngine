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

	STEAM_CALLBACK(SteamManager, OnGameOverlayActivated, GameOverlayActivated_t);

	SteamManager();
	static SteamManager* mInstance;

public:

	static SteamManager& GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new SteamManager();

		return *mInstance;
	}

	~SteamManager()
	{
		SteamAPI_Shutdown();
	};
	int initSteam();
	void UpdateSteamPresence(const char* pKey, const char* pValue);
	void UnlockAchievement(const char* pAchievementID);
	bool IsAchievementUnlocked(const char* pAchievementID);
	// Gets the currently signed in user's Steam ID
	const char* GetSteamUserID();

	void RunCallbacks();
	//void SetSteamPresence(const char* details, const char* state, const char* largeImageKey, const char* largeImageText, const char* smallImageKey, const char* smallImageText);
};