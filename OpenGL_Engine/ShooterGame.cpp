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
	if (key >= sizeof(_keyStates))
	{
		std::cout << "Key code out of keystate bounds" << std::endl;
	}

	_keyStates[key] = down;

	if (down) return; // Ignore key down events

	// Switch key presses
	switch (key)
	{
	case 256: // Esc
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

void ShooterGame::Run(double dt)
{
	// prints the window pointer
	// std::cout << _window << std::endl;

	if (_gameState != Paused)
	{
		// game logic here
	}
	if (_gameState == Playing)
	{
		// game logic here
	}
	if (_gameState == Quit)
	{
		ShooterGame* game = this;
		_window->Close();
	}

	Render();
}
