#pragma once
#include "../Components/Entity.h"
class Command
{
public:
	Command() {}
	virtual ~Command() {}
	// virtual void execute() = 0;
	virtual void execute(Entity* pEntity) = 0;
};
