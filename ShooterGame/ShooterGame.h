#pragma once
#include "Game.h"
#include "Components/Entity.h"
#include "Components/ComponentModel.h"
#include "Components/ComponentShader.h"
#include "Components/ComponentTransform.h"
#include "Vector.h"
#include "Material.h"
#include "SceneManager.h"

// #include "Managers/InputManager.h"
#include "Managers/GameInputManager.h"


class ShooterGame : public Game
{
	GameState mGameState;
	SystemRender* mRenderSystem;

	// non singleton, make sure that this doesn't get copied / or a new one is created. 


public:


	Mesh* GetMesh(std::string pMesh)
	{
	}

	// sets the game up
	virtual void Initialise(Window* w);

	// handles keyboard input
	virtual void OnKeyboard(int key, bool down);

	// draws the game to the screen
	virtual void Render();

	// main game loop
	virtual void Run(double dt);

	virtual bool HandleInput();

	bool IsRunning() override { return mGameState != GameState::Quit; }

	virtual ~ShooterGame()
	{
		// delete all dynamically allocated memory
		for (auto e : mEntities)
		{
			delete e;
		}
		delete mCamera;
		delete mRenderSystem;
		delete mInputManager;
	}
};