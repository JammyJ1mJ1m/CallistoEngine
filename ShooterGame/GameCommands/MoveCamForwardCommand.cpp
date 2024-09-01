#include "MoveCamForwardCommand.h"
#include <iostream>
#include "../ShooterGame.h"

void MoveCamForwardCommand::execute(Entity* pEntity)
{
	// get game instance
	Game* game = Game::GetGame();

	game->GetGameCamera()->MoveForward(32.0f);

	// std::cout << "MoveForwardCommand executed" << std::endl;
}
