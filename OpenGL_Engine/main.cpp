#include "main.h"
#include "ShooterGame.h"

#if OPENGL
#include "Window_GL.h"
#endif

// this is part of the game
int main()
{
#if OPENGL	
	Game* game;

	Window_GL* _window = new Window_GL(new ShooterGame(), 800, 800);
	_window->Initialise();

	game = _window->GetGame();
	game->Initialise(_window);

	while (true)
	{
		_window->Update();
		game->Run();
	}

	/*_window->Initialise();

	SceneManager* sceneManager = new SceneManager(800,800);
	sceneManager->Run();
	delete sceneManager;*/

	delete _window;
#endif

#if DIRECTX
	// set up directx window
#endif
	static ShooterGame Shooters;

	return 0;
}
