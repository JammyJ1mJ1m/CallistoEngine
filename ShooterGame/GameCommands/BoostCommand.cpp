#include "BoostCommand.h"
#include "../ShooterGame.h"
void BoostCommand::execute(Entity* pEntity)
{
	Game* game = Game::GetGame();
	game->GetGameCamera()->IncreaseSpeedMod(4);

}
