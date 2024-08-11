#pragma once
#include "Commands\Command.h"
#include "Components/Entity.h"
class RotateRightCommand : public Command
{
public:
	RotateRightCommand() = default;
	~RotateRightCommand() = default;

	virtual void execute(Entity* pEntity);
};

