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
}