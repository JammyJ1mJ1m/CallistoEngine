#pragma once
#include "Commands/Command.h"

class MoveRightCommand : public Command
{
    public:
		MoveRightCommand() = default;
	~MoveRightCommand() = default;

	virtual void execute();
};

