#include "MoveRightCommand.h"

void MoveRightCommand::execute(Entity* pEntity)
{
	pEntity->MoveRight();
}