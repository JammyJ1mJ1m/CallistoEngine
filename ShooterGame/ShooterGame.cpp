#include "ShooterGame.h"
#include "Managers/ResourceManager.h"
#include "GameScene.h"
#include "Managers/PhysicsManager.h"
#include "BulletDebugDraw.h"



static BulletDebugDrawer_OpenGL* bulletDebugDraw;

void ShooterGame::Initialise(Window* pWindow)
{
	mHasWindowSizeChanged = false;
	bulletDebugDraw = new BulletDebugDrawer_OpenGL();
	//theGame = this;
	mAudioManager = &AudioManager::GetInstance();
	mInputManager = new GameInputManager();

	PhysicsManager::GetInstance();
	mWindow = pWindow;
	mRenderer = pWindow->GetRenderer();
	mRenderSystem = new SystemRender(mRenderer);

	// other game setup logic
	mGameState = Playing;

	mCamera = new Camera(glm::vec3(0.0f, 0.0f, 45.0f), mWindow->GetWindowWidth(), mWindow->GetWindowHeight());

	ResourceManager& RM = ResourceManager::getInstance();
	Mesh* shipMesh = RM.LoadMesh("Resources/Geometry/Floor/FloorTwo.obj");
	if (shipMesh != nullptr)
	{
		shipMesh->AddMaterial("Resources/textures/TCube.mtl");
		AddMesh("ship", shipMesh);
	}

	Mesh* tester = RM.LoadMesh("Resources/Geometry/test/Tester.obj");
	if (tester != nullptr)
	{
		tester->AddMaterial("Resources/textures/TCube.mtl");
		AddMesh("tester", tester);
	}



	Mesh* rpg = RM.LoadMesh("Resources/Geometry/RPG/rpg.obj");
	if (rpg != nullptr)
	{
		rpg->AddMaterial("Resources/textures/TCube.mtl");
		AddMesh("rpg", rpg);
	}


	Mesh* cube = RM.LoadMesh("Resources/Geometry/test/TCube.obj");
	if (cube != nullptr)
	{
		cube->AddMaterial("Resources/textures/TCube.mtl");
		AddMesh("cube", cube);
	}

	Mesh* barrel = RM.LoadMesh("Resources/Geometry/Barrel/expBarrel.obj");
	if (barrel != nullptr)
	{
		barrel->AddMaterial("Resources/textures/TCube.mtl");
		AddMesh("barrel", barrel);
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

	mInputManager->SetKeyState(key, down);
	//_keyStates[key] = down;
}

void ShooterGame::Render()
{
	mDiscordManager->UpdateDiscordPresence();
	mRenderer->ClearScreen();

	mSceneManager.Render(mRenderSystem);

	if (mWindow->GetHasWindowSizeChanged())
	{
		mCamera->UpdateProjection(mWindow->GetWindowWidth(), mWindow->GetWindowHeight());
		mWindow->SetHasWindowSizeChanged(false);
	}

	// pass mouse x and y to the camera
	float x, y;
	mWindow->GetMousePos(x,y);
	 mCamera->HandleMouse(x, y);

	//PhysicsManager::GetInstance().GetDynamicsWorld().setDebugDrawer(bulletDebugDraw);
	//PhysicsManager::GetInstance().GetDynamicsWorld().debugDrawWorld();
}

void ShooterGame::Run(double dt)
{
	mDeltaTime = dt;

	if (mGameState == Paused)
	{
		// paused logic here
	}
	if (mGameState == Playing)
	{
		mSceneManager.Update(dt);
		Render();
		HandleInput();


		// run current scene update loop

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
	// todo - move this to GAME SCENE
	// float moveSensitivity = 16.0f * mDeltaTime;

	if (mInputManager->GetKey(256))  // Esc
		mGameState = Quit;

	if (mInputManager->GetKey(280))  // tab
	{
		mWindow->ToggleFullscreen(true);
		mDiscordManager->SetDiscordPresence("fullscreen", "test");
	}
		//mGameState = Quit;


	if (mGameState == Playing)
	{
		mSceneManager.OnKeyboard(-1, true);
	}

	return false;
}

