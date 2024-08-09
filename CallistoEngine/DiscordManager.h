#pragma once
#include "Discord/discord_rpc.h"
#include <iostream>
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
};

