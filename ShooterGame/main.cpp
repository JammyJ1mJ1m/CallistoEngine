#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <cstdlib>
	#include <crtdbg.h>
#endif

#include "main.h"
#pragma comment(lib, "CallistoEngine.lib")

#include "ShooterGame.h"
#include "time.h"
#include "chrono"
#include <sstream>
#include "toml.hpp"
#include <iostream>

#include "Managers/DisplayManager.h"

#include <steam/steam_api.h>
#include <stdio.h>

#if OPENGL
#include "Window_GL.h"
#endif

#include <fstream>

#if OPENGL	
double calculateDeltaTime(double& lastFrameTime)
{
	double temp_time = clock();
	double deltaTime = (temp_time - lastFrameTime) / CLOCKS_PER_SEC;
	lastFrameTime = temp_time;
	return deltaTime;
}

// this is part of the game
int main()
{
	// load steam api config file
	//	// load a file from disk
	//	std::ifstream file("steam_appid.txt");
	//	if (file.is_open())
	//	{
	//		std::string line;
	//		std::getline(file, line);
	//		SteamAPI_SetTryCatchCallbacks(true);
	//		SteamAPI_Init();
	//		SteamAPI_RestartAppIfNecessary(std::stoi(line));
	//		SteamFriends()->SetRichPresence("status", "Testing");
	//	}
	//	else
	//	{
	//		std::cout << "Steam API not initialized" << std::endl;
	//		return -1;	
	//	}

	//if (SteamAPI_RestartAppIfNecessary(480)) // Replace with your App ID
	//{
	//	std::cout << "Steam API initialized successfully!" << std::endl;
	//	//		SteamFriends()->SetRichPresence("status", "Testing");

	//	//return 1;
	//}

	//if (!SteamAPI_Init())
	//{
	//	printf("Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n");
	//	return 1;
	//}


#ifdef _DEBUG
	// pls work
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	auto& DispManager = DisplayManager::GetInstance();
	DispManager.LoadConfig("Config/settings.toml");

	double deltaTime = 0.0f;
	double lastFrameTime = 0.0f;
	float fps = 0.0f;
	int frameCount = 0;
	int lastFrameCount = 0;

	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();

	Game* game;

	Window_GL* _window = new Window_GL(new ShooterGame(), DispManager.GetResolutionWidth(), DispManager.GetResolutionHeight());

	_window->Initialise("Gamey game");

	game = _window->GetGame();
	game->Initialise(_window);


	while (game->IsRunning())
	{
		++frameCount;
		game->Run(deltaTime);
		_window->Update();

		deltaTime = calculateDeltaTime(lastFrameTime);
		auto newTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(newTime - time);

		if (time_span.count() > 1.0f)
		{
			fps = frameCount - lastFrameCount;
			lastFrameCount = frameCount;
			time = newTime;
			//std::cout << "FPS: " << fps << std::endl;

			std::stringstream ss;
			ss << "Gamey game :: " << fps << " FPS";
			_window->SetTitle(ss.str().c_str());
		}
	}
	SteamAPI_Shutdown();
	delete _window;
	return 0;
}
#endif
