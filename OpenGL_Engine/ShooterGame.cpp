#include "ShooterGame.h"

void ShooterGame::Initialise(Window* w)
{
	_window = w;
	_renderer = w->GetRenderer();

	// other game setup logic


	_gameState = Playing;

}

void ShooterGame::OnKeyboard(int key, bool down)
{
	_keyStates[key] = down;

	if (down) return; // Ignore key down events

	// Switch key presses
	switch (key)
	{
	case 27: // Esc
		_gameState = Quit;
		break;
	case 80: // P
		if (_gameState == Playing)
		{
			_gameState = Paused;
		}
		else if (_gameState = Paused)
		{
			_gameState = Playing;
		}
		break;
	
	}
}

void ShooterGame::Render()
{
	_renderer->ClearScreen();

	// other draw related logic

	// Swap buffers
	_renderer->SwapBuffers();
}

void ShooterGame::Run()
{
	// Get delta time
	double temp_time = clock();
	_deltaTime = (temp_time - _lastFrameTime) / CLOCKS_PER_SEC;
	_lastFrameTime = temp_time;

	if (_gameState != Paused)
	{
		// game logic here
	}

	Render();
}
