#include "MoveBackCommand.h"
#include <iostream>
#include "../ShooterGame.h"

void MoveBackCommand::execute()
{
	// get game instance
	Game* game = Game::GetGame();

	game->GetGameCamera()->MoveForward(-0.1f);
	// std::cout << "MoveBackCommand executed" << std::endl;
}
