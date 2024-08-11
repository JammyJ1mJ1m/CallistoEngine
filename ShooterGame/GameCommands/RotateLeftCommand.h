#pragma once
#include "Commands\Command.h"
class RotateLeftCommand : public Command
{
public:
	RotateLeftCommand() = default;
	~RotateLeftCommand() = default;

	virtual void execute(Entity* pEntity);
};

