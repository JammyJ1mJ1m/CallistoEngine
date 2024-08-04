#include "MoveForwardCommand.h"
#include <iostream>
#include "../ShooterGame.h"

void MoveForwardCommand::execute()
{
	// get game instance
	Game* game = Game::GetGame();

	game->GetGameCamera()->MoveForward(32.0f * game->GetDeltaTime());

	// std::cout << "MoveForwardCommand executed" << std::endl;
}
