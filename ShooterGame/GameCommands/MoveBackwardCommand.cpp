#include "MoveBackwardCommand.h"

void MoveBackwardCommand::execute(Entity* pEntity)
{
	pEntity->MoveBackward();
}
