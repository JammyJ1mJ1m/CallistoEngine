#pragma once
#include "Commands\Command.h"
class MoveCamBackCommand : public Command
{
public:
	MoveCamBackCommand() = default;
	~MoveCamBackCommand() = default;

	virtual void execute(Entity* pEntity);
};

