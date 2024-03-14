#pragma once
#include "Game.h"
#include "Components/Entity.h"
#include "Components/ComponentModel.h"
#include "Components/ComponentShader.h"
#include "Components/ComponentTransform.h"
#include "Vector.h"

#include "Material.h"

#include "Systems/SystemRender.h"

#include "Camera.h"


class ShooterGame : public Game
{
	GameState _gameState;
	SystemRender* mRenderSystem;
	Camera* mCamera;

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

	virtual ~ShooterGame()
	{
		delete mCamera;
		delete mRenderSystem;
		// delete all dynamically allocated memory
		for (auto e : mEntities)
		{
			delete e;
		}

	}
};

