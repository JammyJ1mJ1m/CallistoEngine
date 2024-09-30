#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
	#include <cstdlib>
#endif

#include "main.h"
#pragma comment(lib, "CallistoEngine.lib")
#include "Managers/DisplayManager.h"
#include "ShooterGame.h"
#include "Misc/toml.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include "time.h"
#include "chrono"


#if OPENGL
#include "Graphical/Window_GL.h"
#endif
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

	//game->Update();

	while (game->IsRunning())
	{
		_window->Update();
		game->CalculateDeltaTime();
		game->Update();
	}
	delete _window;
	return 0;
}
#endif
