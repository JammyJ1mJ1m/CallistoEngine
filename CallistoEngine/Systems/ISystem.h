#pragma once
#include "../Components/Entity.h"
#include <string>
#include <vector>
class ISystem
{
public:
	ISystem() = default;
	virtual ~ISystem() = default;
	virtual void Run(Entity* pEntity) = 0;
};

