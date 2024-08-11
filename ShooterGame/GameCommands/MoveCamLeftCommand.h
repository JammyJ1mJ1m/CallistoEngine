#pragma once
#include "Commands/Command.h"

class MoveCamLeftCommand : public Command
{
    public:
		MoveCamLeftCommand() = default;
	~MoveCamLeftCommand() = default;

	virtual void execute(Entity* pEntity);
};

