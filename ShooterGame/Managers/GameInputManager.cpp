#include "GameInputManager.h"
#include "../GameCommands/MoveForwardCommand.h"

GameInputManager::GameInputManager()
{
	mWalkForwardCommand = new MoveForwardCommand();
}

GameInputManager::~GameInputManager()
{
}
