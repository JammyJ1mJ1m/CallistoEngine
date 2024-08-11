#include "RotateRightCommand.h"
#include <iostream>
#include "../ShooterGame.h"

void RotateRightCommand::execute(Entity* pEntity)
{
	// get game instance
	Game* game = Game::GetGame();
	float moveSensitivity = 84.0f;

	game->GetGameCamera()->Rotate(-moveSensitivity * game->GetDeltaTime());
	// std::cout << "RotateRightCommand executed" << std::endl;
}
