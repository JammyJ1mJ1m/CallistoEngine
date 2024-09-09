#include "Game.h"

Game* Game::theGame = nullptr;

Camera* Game::GetGameCamera() {
	return (theGame != nullptr) ? theGame->mCamera : nullptr;
}

Game::Game() :
	mSceneManager(this)
{
	mAudioManager = nullptr;
	mCamera = nullptr;
	mInputManager = nullptr;
	mRenderer = nullptr;
	mWindow = nullptr;
	mRenderSystem = nullptr;
	mHasWindowSizeChanged = false;

	// initiallise _keyStates
	for (int i = 0; i < 512; i++)
	{
		_keyStates[i] = false;
	}

	theGame = this;
	mDeltaTime = 0.0;
	mLastFrameTime = 0.0;
	mRenderSystem = nullptr;
	mDiscordManager = new DiscordManager();
	mDiscordManager->initDiscord();

	// TODO: renable this at a later date, this avoids spamming my steam friends with dev testing notifs
	mSteamManager = new SteamManager();
	mSteamManager->initSteam();
}

const double Game::CalculateDeltaTime()
{

	++frameCount;

	double temp_time = clock();
	mDeltaTime = (temp_time - mLastFrameTime) / CLOCKS_PER_SEC;
	mLastFrameTime = temp_time;




	//deltaTime = calculateDeltaTime(lastFrameTime);

	auto newTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(newTime - time);

	if (time_span.count() > 1.0f)
	{
		fps = frameCount - lastFrameCount;
		lastFrameCount = frameCount;
		time = newTime;

		std::stringstream ss;
		ss << "Gamey game :: " << GetFPS() << " FPS";
		mWindow->SetTitle(ss.str().c_str());
	}


	return mDeltaTime;
}

void Game::BaseRun()
{
	mSteamManager->RunCallbacks();
}

void Game::BaseRender()
{
	mRenderer->ClearScreen();
	mDiscordManager->UpdateDiscordPresence();
	if (mWindow->GetHasWindowSizeChanged())
	{
		mCamera->UpdateProjection(mWindow->GetWindowWidth(), mWindow->GetWindowHeight());
		mWindow->SetHasWindowSizeChanged(false);
	}

	float x, y;
	mWindow->GetMousePos(x, y);
	mCamera->HandleMouse(x, y);

	//PhysicsManager::GetInstance().GetDynamicsWorld().setDebugDrawer(bulletDebugDraw);
//PhysicsManager::GetInstance().GetDynamicsWorld().debugDrawWorld();
}
