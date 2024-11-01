#include "ShooterGame.h"
#include "GameScene.h"
#include "Managers/PhysicsManager.h"
#include "Misc/BulletDebugDraw.h"
#include "Graphical/PostProcessor.h"
#include "GunLoader.h"
#include "MainMenuScene.h"
#include "Graphical/PostProcessEffect.h"
#include "Graphical/PostProcessing/BloomEffect.h"

#include "GUI/GUIManager.h"

static BulletDebugDrawer_OpenGL* bulletDebugDraw;

void ShooterGame::InitialiseGame()
{


	// give shaders to the post processor //
	//PostProcessor::GetInstance().LoadShader("Resources/Shaders/PP/PP.vert", "Resources/Shaders/PP/Matrix.frag");



	//PostProcessEffect* pp2 = new PostProcessEffect();
	//pp2->LoadShader("Resources/Shaders/PP/PP.vert", "Resources/Shaders/PP/EdgeDetection.frag", "Edge");
	//mRenderer->AddEffect(pp2);

	//PostProcessEffect* pp3 = new PostProcessEffect();
	//pp3->LoadShader("Resources/Shaders/PP/PP.vert", "Resources/Shaders/PP/Blur.frag", "Blur");
	//mRenderer->AddEffect(pp3);

	//BloomEffect* bloomEffect = new BloomEffect();
	//bloomEffect->LoadShader("Resources/Shaders/PP/PP.vert", "Resources/Shaders/PP/Bloom.frag", "Bloom");
	//mRenderer->AddEffect(bloomEffect);

	//PostProcessEffect* pp4 = new PostProcessEffect();
	//pp4->LoadShader("Resources/Shaders/PP/PP.vert", "Resources/Shaders/PP/Blur.frag", "Blur2");
	//mRenderer->AddEffect(pp4);

	PostProcessEffect* pp1 = new PostProcessEffect();
	pp1->LoadShader("Resources/Shaders/PP/PP.vert", "Resources/Shaders/PP/Matrix.frag", "Matrix");
	mRenderer->AddEffect(pp1);



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
	LoadMesh("Resources/Geometry/Floor/SkyIsland.obj", "ship", RM);
	LoadMesh("Resources/Geometry/CardBox/box.obj", "tester", RM);
	//LoadMesh("Resources/Geometry/Guns/RPG/rpg.obj", "rpg", RM);
	LoadMesh("Resources/Geometry/CardBox/box.obj", "cube", RM);
	LoadMesh("Resources/Geometry/Barrel/expBarrel.obj", "barrel", RM);

	//LoadMesh("Resources/Geometry/Guns/AK/AK.obj", "AK", RM);
	LoadMesh("Resources/Geometry/Guns/AK/magazineAK.obj", "AKmagazine", RM);

	LoadMesh("Resources/Geometry/error.obj", "error", RM);


	GunLoader::GetInstance().ReadManifest("GameObjects/AK/gunManifest.txt");

	for (auto& mesh : GunLoader::GetInstance().GetMeshesToLoad())
	{
		LoadMesh(mesh.first.c_str(), mesh.second.c_str(), RM);
	}


	mSceneManager.PushScene(new GameScene());
	//mSceneManager.PushScene(new MainMenuScene());
	GUIManager::GetInstance().Resize(Game::GetGame()->GetGameCamera()->mWidth, Game::GetGame()->GetGameCamera()->mHeight);

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

		if (mWindow->GetIsFullscreen())
			mDiscordManager->SetDiscordPresence("fullscreen", "test");
		else
			mDiscordManager->SetDiscordPresence("Making game", "In Game", "cglarge", "AAAA", "asset1", "Look at his smile");
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
