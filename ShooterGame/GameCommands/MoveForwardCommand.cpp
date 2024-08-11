#include "MoveForwardCommand.h"

void MoveForwardCommand::execute(Entity* pEntity)
{
	pEntity->MoveForward();
}
