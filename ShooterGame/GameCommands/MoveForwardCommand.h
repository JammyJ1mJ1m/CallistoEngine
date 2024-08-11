#pragma once
#include "Commands/Command.h"

class MoveForwardCommand : public Command
{
public:
	MoveForwardCommand() = default;
	~MoveForwardCommand() = default;

	virtual void execute(Entity* pEntity);
};

