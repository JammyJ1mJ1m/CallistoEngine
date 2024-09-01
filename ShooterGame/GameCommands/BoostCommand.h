#pragma once
#include "Commands\Command.h"
class BoostCommand : public Command
{
public:
	BoostCommand() = default;
	~BoostCommand() = default;

	virtual void execute(Entity* pEntity);
};

