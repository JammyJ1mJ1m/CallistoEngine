#pragma once
#include "Game.h"
class ShooterGame : public Game
{
	GameState _gameState;
public:

	// sets the game up
	virtual void Initialise(Window* w);

	// handles keyboard input
	virtual void OnKeyboard(int key, bool down);

	// draws the game to the screen
	virtual void Render();

	// main game loop
	virtual void Run(double dt);

	bool IsRunning() override { return _gameState != GameState::Quit; }
};

