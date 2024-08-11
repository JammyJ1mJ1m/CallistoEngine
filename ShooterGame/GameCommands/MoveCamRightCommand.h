#pragma once
#include "Commands/Command.h"

class MoveCamRightCommand : public Command
{
    public:
		MoveCamRightCommand() = default;
	~MoveCamRightCommand() = default;

	virtual void execute(Entity* pEntity);
};

