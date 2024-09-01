#include "MoveCamBackCommand.h"
#include <iostream>
#include "../ShooterGame.h"

void MoveCamBackCommand::execute(Entity* pEntity)
{
	// get game instance
	Game* game = Game::GetGame();
	game->GetGameCamera()->MoveForward(-32.0f );
	// std::cout << "MoveBackCommand executed" << std::endl;
}
