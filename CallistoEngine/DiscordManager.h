#pragma once
#include "Discord/discord_rpc.h"
#include <iostream>
#include <string>
class DiscordManager
{
	public:
	DiscordManager() = default;
	~DiscordManager()
	{
		Discord_Shutdown();
		//delete core;
	};
	void initDiscord();
	void UpdateDiscordPresence();
	void SetDiscordPresence(const char* details, const char* state, const char* largeImageKey, const char* largeImageText, const char* smallImageKey, const char* smallImageText);
	void SetDiscordPresence(const char* details, const char* state);
	void SetDiscordPresence(std::string& details, std::string& state, std::string& largeImageKey, std::string& largeImageText, std::string& smallImageKey, std::string& smallImageText);
	void SetDiscordPresence(std::string& details, std::string& state);
	void SetDiscordPresence(const char* details, const int state);
	void UpdatePresence(DiscordRichPresence& pPresence);
};

