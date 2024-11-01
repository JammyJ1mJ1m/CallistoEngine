#include "SteamManager.h"
#include "../Game.h"
SteamManager* SteamManager::mInstance = nullptr;

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
	ReadAppID();
	SteamAPI_SetTryCatchCallbacks(true);
	bool steamOpen = SteamAPI_Init();
	SteamAPI_RestartAppIfNecessary(GetAppID());
	//mIsInitialized = true;
	UpdateSteamPresence("status", "Testing");

	/*else
	{
		std::cout << "Steam API not initialized" << std::endl;
		return -1;
	}*/

	if (SteamAPI_RestartAppIfNecessary(GetAppID())) // Replace with your App ID
	{
		std::cout << "Steam API initialized successfully!" << std::endl;
		//		SteamFriends()->SetRichPresence("status", "Testing");

		//return 1;
		//mIsInitialized = true;

	}

	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n";
		return -1;
	}
	mIsInitialized = true;

	return 1;
}

void SteamManager::UpdateSteamPresence(const char* pKey, const char* pValue)
{
	if (mIsInitialized)
	{
		SteamFriends()->SetRichPresence(pKey, pValue);
	}
}

void SteamManager::UnlockAchievement(const char* pAchievementID)
{
	if (IsAchievementUnlocked(pAchievementID))
		return;

	if (!SteamUserStats() || !SteamUser()) {
		std::cerr << "Steam not initialized properly.\n";
		return;
	}

	// Set the achievement as unlocked
	if (SteamUserStats()->SetAchievement(pAchievementID)) {
		std::cout << "Achievement :: " << pAchievementID << " :: unlocked\n";

		if (SteamUserStats()->StoreStats())
			std::cout << "Achievement :: " << pAchievementID << " :: status stored successfully\n";

		else
			std::cerr << "Achievement :: " << pAchievementID << " :: Failed to store achievement status\n";
	}
	else {
		std::cerr << "Achievement :: " << pAchievementID << " :: Failed to unlock achievement\n";
	}
}

bool SteamManager::IsAchievementUnlocked(const char* pAchievementID)
{
	if (!SteamUserStats() || !SteamUser()) {
		std::cerr << "Steam not initialized properly.\n";
		return false;
	}

	bool unlocked = false;
	SteamUserStats()->GetAchievement(pAchievementID, &unlocked);

	if (unlocked)
		std::cout << "Achievement :: " << pAchievementID << " :: already unlocked\n";

	return unlocked;
}

const char* SteamManager::GetSteamUserID()
{
	if (mIsInitialized) 
		return SteamFriends()->GetPersonaName(); 
	else 
		return "No username";
	
}

void SteamManager::RunCallbacks()
{
	SteamAPI_RunCallbacks();
}


void SteamManager::OnGameOverlayActivated(GameOverlayActivated_t* pCallback)
{
	if (pCallback->m_bActive)
	{
		printf("Steam overlay now active\n");
		Game::GetGame()->SetGameState(Paused);
	}
	else
	{
		Game::GetGame()->SetGameState(Playing);
		printf("Steam overlay now inactive\n");
	}
}