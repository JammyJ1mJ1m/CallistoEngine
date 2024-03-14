#include "main.h"
#pragma comment(lib, "CallistoEngine.lib")

#include "ShooterGame.h"
#include "time.h"
#include "chrono"

#if OPENGL
#include "Window_GL.h"
#endif

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
	double deltaTime = 0.0f;
	double lastFrameTime = 0.0f;
	float fps = 0.0f;
	int frameCount = 0;
	int lastFrameCount = 0;

	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();

#if OPENGL	
	Game* game;

	Window_GL* _window = new Window_GL(new ShooterGame(), 800, 800);

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
			std::cout << "FPS: " << fps << std::endl;
		}
	}

	delete _window;
#endif

#if DIRECTX
	// set up directx window
#endif
	return 0;
}