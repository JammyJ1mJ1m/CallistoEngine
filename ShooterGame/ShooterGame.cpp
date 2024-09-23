#include "ShooterGame.h"
#include "GameScene.h"
#include "Managers/PhysicsManager.h"
#include "Misc/BulletDebugDraw.h"
#include "Graphical/PostProcessor.h"
#include "GunLoader.h"

static BulletDebugDrawer_OpenGL* bulletDebugDraw;

void ShooterGame::InitialiseGame()
{
	// give shaders to the post processor //
	PostProcessor::GetInstance().LoadShader("Resources/Shaders/PP/PP.vert", "Resources/Shaders/PP/defaultPP.frag");

	bulletDebugDraw = new BulletDebugDrawer_OpenGL();
	mInputManager = new GameInputManager();
	/*const char* tt = mSteamManager->GetSteamUserID();
	std::cout << "Signed in as: " << tt << std::endl;*/


	//mSteamManager->UnlockAchievement("NEW_ACHIEVEMENT_0_4");
	//mSteamManager->UpdateSteamPresence("status", "In testing"); // Not sure why this doesnt seem to be working

	// other game setup logic
	mGameState = Playing;

	mCamera = new Camera(glm::vec3(0.0f, 0.0f, 45.0f), mWindow->GetWindowWidth(), mWindow->GetWindowHeight());

	ResourceManager& RM = ResourceManager::getInstance();
	LoadMesh("Resources/Geometry/Floor/FloorTwo.obj", "ship", RM);
	LoadMesh("Resources/Geometry/CardBox/box.obj", "tester", RM);
	//LoadMesh("Resources/Geometry/Guns/RPG/rpg.obj", "rpg", RM);
	LoadMesh("Resources/Geometry/CardBox/box.obj", "cube", RM);
	//LoadMesh("Resources/Geometry/Barrel/expBarrel.obj", "barrel", RM);

	//LoadMesh("Resources/Geometry/Guns/AK/AK.obj", "AK", RM);
	LoadMesh("Resources/Geometry/Guns/AK/magazineAK.obj", "AKmagazine", RM);

	LoadMesh("Resources/Geometry/error.obj", "error", RM);

	GunLoader& gLoader = GunLoader::GetInstance();

	gLoader.ReadManifest("GameObjects/AK/gunManifest.txt");

	//gLoader.ConstructFromDisk("GameObjects/AK/RayGun.toml");
	//gLoader.ConstructFromDisk("GameObjects/AK/AK.toml");
	//gLoader.ConstructFromDisk("GameObjects/AK/Glock.toml");

	//gLoader.ConstructFromDisk("GameObjects/AK/RPG.toml");

	const GunsToLoad meshes = gLoader.GetMeshesToLoad();

	for (auto& mesh : meshes)
	{
		LoadMesh(mesh.first.c_str(), mesh.second.c_str(), RM);
	}


	mSceneManager.PushScene(new GameScene());
}

void ShooterGame::RenderFrame()
{
	mSceneManager.Render(mRenderSystem);

	//PhysicsManager::GetInstance().GetDynamicsWorld().setDebugDrawer(bulletDebugDraw);
	//PhysicsManager::GetInstance().GetDynamicsWorld().debugDrawWorld();
}


void ShooterGame::Run()
{
	if (mGameState == Paused)
	{
		// paused logic here
		std::cout << "Paused" << std::endl;
		Render();
	}
	if (mGameState == Playing)
	{
		mSceneManager.Update(mDeltaTime);
		Render();
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

void ShooterGame::OnKeyboard(int key, bool down)
{
	if (key >= sizeof(_keyStates))
	{
		std::cout << "Key code out of keystate bounds" << std::endl;
		return; //If the key is out of bounds, DO NOT continue as memory will be corrupted
	}

	mInputManager->SetKeyState(key, down);

}
bool ShooterGame::HandleInput()
{
	// todo - move this to GAME SCENE
	// float moveSensitivity = 16.0f * mDeltaTime;

	if (mInputManager->GetKey(256))  // Esc
		mGameState = Quit;

	if (mInputManager->GetKeyDown(280))  // caps
	{
		mWindow->ToggleFullscreen(true);
		mDiscordManager->SetDiscordPresence("fullscreen", "test");
	}
	//mGameState = Quit;

	if (mGameState == Playing)
	{
		mSceneManager.OnKeyboard(-1, true);
	}
	mInputManager->UpdatePrevKeyStates();
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
