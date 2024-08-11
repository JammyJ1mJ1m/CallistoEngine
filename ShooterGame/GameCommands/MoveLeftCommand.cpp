#include "MoveLeftCommand.h"

void MoveLeftCommand::execute(Entity* pEntity)
{
	pEntity->MoveLeft();
}