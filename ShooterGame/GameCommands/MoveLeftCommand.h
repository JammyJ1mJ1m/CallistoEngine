#pragma once
#include "Commands/Command.h"

class MoveLeftCommand : public Command
{
    public:
		MoveLeftCommand() = default;
	~MoveLeftCommand() = default;

	virtual void execute();
};

