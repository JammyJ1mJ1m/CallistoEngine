#include "MoveCamLeftCommand.h"
#include <iostream>
#include "../ShooterGame.h"

void MoveCamLeftCommand::execute(Entity* pEntity)
{
	// get game instance
	Game* game = Game::GetGame();

	game->GetGameCamera()->Strafe(-32.0f);

	// std::cout << "MoveLeftCommand executed" << std::endl;
}
