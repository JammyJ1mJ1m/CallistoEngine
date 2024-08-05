#include "main.h"
#pragma comment(lib, "CallistoEngine.lib")

#include "ShooterGame.h"
#include "time.h"
#include "chrono"
#include <sstream>
#include "toml.hpp"
#include <iostream>

#include "Managers/DisplayManager.h"


#if OPENGL
#include "Window_GL.h"
#endif

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

	delete _window;
	return 0;
}
#endif
