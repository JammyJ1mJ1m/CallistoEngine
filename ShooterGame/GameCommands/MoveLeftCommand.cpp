#include "MoveLeftCommand.h"
#include <iostream>
#include "../ShooterGame.h"

void MoveLeftCommand::execute()
{
	// get game instance
	Game* game = Game::GetGame();

	game->GetGameCamera()->Strafe(-32.0f * game->GetDeltaTime());

	// std::cout << "MoveLeftCommand executed" << std::endl;
}
