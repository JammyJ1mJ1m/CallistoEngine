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



	Window_GL _window = Window_GL(new ShooterGame(), 800, 800);
	game = _window.GetGame();
	game->Run();

	/*_window->Initialise();

	SceneManager* sceneManager = new SceneManager(800,800);
	sceneManager->Run();
	delete sceneManager;*/
#endif

#if DIRECTX
	// set up directx window
#endif
	static ShooterGame Shooters;

	return 0;
}
