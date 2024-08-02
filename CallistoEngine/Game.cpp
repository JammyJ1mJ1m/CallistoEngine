#include "Game.h"

Game* Game::theGame = nullptr;

Camera* Game::GetGameCamera() {
	return (theGame != nullptr) ? theGame->mCamera : nullptr;
}

Game::Game() :
	mSceneManager(this)
{
	theGame = this;
	mDeltaTime = 0.0;
	mLastFrameTime = 0.0;
	mRenderSystem = nullptr;
}