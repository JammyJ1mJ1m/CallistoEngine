#include "MoveForwardCommand.h"
#include <iostream>
#include "../ShooterGame.h"

void MoveForwardCommand::execute()
{
	// get game instance
	Game* game = Game::GetGame();

	game->GetGameCamera()->MoveForward(0.1f);

	// std::cout << "MoveForwardCommand executed" << std::endl;
}
