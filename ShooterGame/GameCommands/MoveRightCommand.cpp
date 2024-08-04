#include "MoveRightCommand.h"
#include <iostream>
#include "../ShooterGame.h"

void MoveRightCommand::execute()
{
	// get game instance
	Game* game = Game::GetGame();

	game->GetGameCamera()->Strafe(32.0f * game->GetDeltaTime());

	// std::cout << "MoveRightCommand executed" << std::endl;
}
