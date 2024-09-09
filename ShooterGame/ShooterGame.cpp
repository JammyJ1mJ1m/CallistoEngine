#include "ShooterGame.h"
#include "GameScene.h"
#include "Managers/PhysicsManager.h"
#include "Misc/BulletDebugDraw.h"

static BulletDebugDrawer_OpenGL* bulletDebugDraw;

void ShooterGame::Initialise(Window* pWindow)
{
	const char* tt = mSteamManager->GetSteamUserID();
	std::cout << "Signed in as: " << tt << std::endl;
	mHasWindowSizeChanged = false;
	bulletDebugDraw = new BulletDebugDrawer_OpenGL();
	mAudioManager = &AudioManager::GetInstance();
	mInputManager = new GameInputManager();

	PhysicsManager::GetInstance();
	mWindow = pWindow;
	mRenderer = pWindow->GetRenderer();
	mRenderSystem = new SystemRender(mRenderer);

	mLightManager = &LightManager::GetInstance();

	//mSteamManager->UnlockAchievement("NEW_ACHIEVEMENT_0_4");

	// huh?
	//mLightSystem = new SystemLight();

	// other game setup logic
	mGameState = Playing;

	mCamera = new Camera(glm::vec3(0.0f, 0.0f, 45.0f), mWindow->GetWindowWidth(), mWindow->GetWindowHeight());

	ResourceManager& RM = ResourceManager::getInstance();
	LoadMesh("Resources/Geometry/Floor/FloorTwo.obj", "ship", RM);
	LoadMesh("Resources/Geometry/CardBox/box.obj", "tester", RM);
	LoadMesh("Resources/Geometry/Guns/RPG/rpg.obj", "rpg", RM);
	LoadMesh("Resources/Geometry/CardBox/box.obj", "cube", RM);
	LoadMesh("Resources/Geometry/Barrel/expBarrel.obj", "barrel", RM);
	LoadMesh("Resources/Geometry/Guns/AK/AK3.obj", "AK", RM);
	LoadMesh("Resources/Geometry/Guns/AK/magazineAK.obj", "AKmagazine", RM);

	mSceneManager.PushScene(new GameScene());
}

void ShooterGame::OnKeyboard(int key, bool down)
{
	if (key >= sizeof(_keyStates))
	{
		std::cout << "Key code out of keystate bounds" << std::endl;
		return; //If the key is out of bounds, DO NOT continue as memory will be corrupted
	}

	mInputManager->SetKeyState(key, down);
}

void ShooterGame::Render()
{
	mSceneManager.Render(mRenderSystem);

	// if you're looking for the physics debug draw, it's in the base game class ;)
}

void ShooterGame::Run()
{
	if (mGameState == Paused)
	{
		// paused logic here
	}
	if (mGameState == Playing)
	{
		mSceneManager.Update(mDeltaTime);
		RenderFrame();
		HandleInput();
	}
	if (mGameState == Quit)
	{
		// save the game first
		// then quit
		/*ShooterGame* game = this;*/
		mWindow->Close();
	}
}

bool ShooterGame::HandleInput()
{
	// todo - move this to GAME SCENE
	// float moveSensitivity = 16.0f * mDeltaTime;

	if (mInputManager->GetKey(256))  // Esc
		mGameState = Quit;

	if (mInputManager->GetKey(280))  // caps
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

bool ShooterGame::LoadMesh(const char* pFilePath, const char* pModelName, ResourceManager& pResourceManager)
{
	Mesh* modelMesh = pResourceManager.LoadMesh(pFilePath);
	if (modelMesh != nullptr)
	{
		AddMesh(pModelName, modelMesh);
		return true;
	}

	return false;
}


