#include "RotateLeftCommand.h"
#include <iostream>
#include "../ShooterGame.h"

void RotateLeftCommand::execute()
{
	// get game instance
	Game* game = Game::GetGame();
	float moveSensitivity = 84.0f;

	game->GetGameCamera()->Rotate(moveSensitivity * game->GetDeltaTime());
	// std::cout << "RotateLeftCommand executed" << std::endl;
}
