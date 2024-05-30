#include "ShooterGame.h"
#include "Managers/ResourceManager.h"
#include "GameScene.h"

void ShooterGame::Initialise(Window* w)
{
	//theGame = this;

	mWindow = w;
	mRenderer = w->GetRenderer();
	mRenderSystem = new SystemRender(mRenderer);

	// other game setup logic
	mGameState = Playing;

	mCamera = new Camera(glm::vec3(0.0f, 0.0f, 15.0f), mWindow->GetWindowWidth(), mWindow->GetWindowHeight());

	ResourceManager& RM = ResourceManager::getInstance();
	Mesh* shipMesh = RM.LoadMesh("Resources/Geometry/test/Intergalactic_Spaceship.obj");
	if (shipMesh != nullptr)
	{
		shipMesh->AddMaterial("Resources/textures/TestCube.mtl");
		AddMesh("ship", shipMesh);
	}

	Mesh* tester = RM.LoadMesh("Resources/Geometry/test/Tester.obj");
	if (tester != nullptr)
	{
		tester->AddMaterial("Resources/textures/Tester.mtl");
		AddMesh("tester", tester);
	}

	mSceneManager.PushScene(new GameScene());
}

void ShooterGame::OnKeyboard(int key, bool down)
{
	if (key >= sizeof(_keyStates))
	{
		std::cout << "Key code out of keystate bounds" << std::endl;
	}
	//mSceneManager->OnKeyboard(key, down);

	_keyStates[key] = down;
}

void ShooterGame::Render()
{
	mRenderer->ClearScreen();

	mSceneManager.Render(mRenderSystem);
}

void ShooterGame::Run(double dt)
{
	mDeltaTime = dt;

	if (mGameState != Paused)
	{
		// game logic here
	}
	if (mGameState == Playing)
	{
		Render();
		HandleInput();

		// game logic here
	}
	if (mGameState == Quit)
	{
		ShooterGame* game = this;
		mWindow->Close();
	}
}

bool ShooterGame::HandleInput()
{
	float moveSensitivity = 16.0f * mDeltaTime;
	
	if (_keyStates[256])  // Esc
		mGameState = Quit;
	if (_keyStates[80])  // P
		if (mGameState == Playing)
		{
			mGameState = Paused;
		}
		else if (mGameState = Paused)
		{
			mGameState = Playing;
		}

	if (_keyStates[65])  // A
		if (mGameState == Playing)
		{
			mCamera->Strafe(-(moveSensitivity));
		}
	if (_keyStates[68])  // D
		if (mGameState == Playing)
		{
			// Move right
			mCamera->Strafe((moveSensitivity));
		}

	if (_keyStates[83])  // S
		if (mGameState == Playing)
		{
			// Move back
			mCamera->MoveForward(-(moveSensitivity));
		}
	if (_keyStates[87]) // W
		if (mGameState == Playing)
		{
			// Move forward
			mCamera->MoveForward(moveSensitivity);
		}
	return false;
}

