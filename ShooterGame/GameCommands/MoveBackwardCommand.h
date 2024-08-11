#pragma once
#include "Commands\Command.h"
class MoveBackwardCommand : public Command
{
public:
	MoveBackwardCommand() = default;
	~MoveBackwardCommand() = default;

	virtual void execute(Entity* pEntity);
};

