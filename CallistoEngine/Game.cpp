#include "Game.h"

Game::Game() :
	mSceneManager(this)
{
	mDeltaTime = 0.0;
	mLastFrameTime = 0.0;
	mRenderSystem = nullptr;
}