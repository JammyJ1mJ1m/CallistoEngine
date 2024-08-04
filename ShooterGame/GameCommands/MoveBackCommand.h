#pragma once
#include "Commands\Command.h"
class MoveBackCommand : public Command
{
public:
	MoveBackCommand() = default;
	~MoveBackCommand() = default;

	virtual void execute();
};

