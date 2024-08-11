#pragma once
#include "Commands/Command.h"

class MoveCamForwardCommand : public Command
{
    public:
	MoveCamForwardCommand() = default;
	~MoveCamForwardCommand() = default;

	virtual void execute(Entity* pEntity);
};

