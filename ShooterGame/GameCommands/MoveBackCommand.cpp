#include "MoveBackCommand.h"
#include <iostream>
#include "../ShooterGame.h"

void MoveBackCommand::execute()
{
	// get game instance
	Game* game = Game::GetGame();
	float moveSensitivity = 32.0f;

	game->GetGameCamera()->MoveForward(-moveSensitivity * game->GetDeltaTime());
	// std::cout << "MoveBackCommand executed" << std::endl;
}
