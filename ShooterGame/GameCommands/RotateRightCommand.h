#pragma once
#include "Commands\Command.h"
class RotateRightCommand : public Command
{
public:
	RotateRightCommand() = default;
	~RotateRightCommand() = default;

	virtual void execute();
};

