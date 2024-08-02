#pragma once
#include "../Components/Entity.h"
#include <string>
class ISystem
{
public:
	ISystem() = default;
	virtual ~ISystem() = default;
	virtual void Run(Entity* Entity) = 0;
};

