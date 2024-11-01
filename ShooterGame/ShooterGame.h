#pragma once
#include "Game.h"
#include "Components/Entity.h"
#include "Components/ComponentModel.h"
#include "Components/ComponentShader.h"
#include "Components/ComponentTransform.h"
#include "Math/Vector.h"
#include "Misc/Material.h"
#include "Managers/SceneManager.h"

// #include "Managers/InputManager.h"
#include "Managers/GameInputManager.h"

//#include "Systems/SystemLight.h"
//#include "Managers/LightManager.h"


class ShooterGame : public Game
{
	//SystemRender* mRenderSystem;

	//SystemLight* mLightSystem;
	//LightManager* mLightManager;


	// non singleton, make sure that this doesn't get copied / or a new one is created. 

	// draws the game to the screen
	virtual void RenderFrame();
	// main game loop
	virtual void Run();
	// sets the game up
	virtual void InitialiseGame();


public:

	Mesh* GetMesh(std::string pMesh)
	{
	}


	// handles keyboard input
	virtual void OnKeyboard(int key, bool down);

	virtual bool HandleInput();

	bool IsRunning() override { return mGameState != GameState::Quit; }

	virtual bool LoadMesh(const char* pFilePath, const char* pModelName, ResourceManager& pResourceManager );

	virtual ~ShooterGame()
	{
		// delete all dynamically allocated memory
		for (auto e : mEntities)
		{
			delete e;
		}
		/*delete mCamera;
		delete mRenderSystem;
		delete mInputManager;*/
	}
};