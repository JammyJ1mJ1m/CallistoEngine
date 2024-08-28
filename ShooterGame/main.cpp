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
#include <stdio.h>

#if OPENGL
#include "Window_GL.h"
#endif
#include <fstream>
#if OPENGL	

// this is part of the game
int main()
{
#ifdef _DEBUG
	// pls work
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	auto& DispManager = DisplayManager::GetInstance();
	DispManager.LoadConfig("Config/settings.toml");

	Game* game;

	Window_GL* _window = new Window_GL(new ShooterGame(), DispManager.GetResolutionWidth(), DispManager.GetResolutionHeight());

	_window->Initialise("Gamey game");

	game = _window->GetGame();
	game->Initialise(_window);


	while (game->IsRunning())
	{
		game->CalculateDeltaTime();
		game->Run();
		_window->Update();
	}
	delete _window;
	return 0;
}
#endif
