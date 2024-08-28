#include "SteamManager.h"

int SteamManager::ReadAppID()
{
	std::ifstream file("steam_appid.txt");
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);

		if (std::stoi(line))
			SetAppID(std::stoi(line));
	}
	return GetAppID();
}

SteamManager::SteamManager()
{
	mIsInitialized = false;
	mAppId = -1;
}

int SteamManager::initSteam()
{
	/*SteamAPI_SetTryCatchCallbacks(true);
	SteamAPI_Init();
	SteamAPI_RestartAppIfNecessary(GetAppID());
	mIsInitialized = true;
	UpdateSteamPresence("status", "Testing");*/

	/*else
	{
		std::cout << "Steam API not initialized" << std::endl;
		return -1;
	}*/

	if (SteamAPI_RestartAppIfNecessary(480)) // Replace with your App ID
	{
		std::cout << "Steam API initialized successfully!" << std::endl;
		//		SteamFriends()->SetRichPresence("status", "Testing");

		//return 1;
		mIsInitialized = true;

	}

	if (!SteamAPI_Init())
	{
		printf("Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n");
		return -1;
	}
	return 1;
}

void SteamManager::UpdateSteamPresence(const char* pKey, const char* pValue)
{
	if (mIsInitialized)
	{
		//SteamFriends()->SetRichPresence(pKey, pValue);
	}
}
