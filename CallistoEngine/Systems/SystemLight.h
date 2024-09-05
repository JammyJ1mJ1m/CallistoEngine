#pragma once
#include "ISystem.h"
#include "../Managers/LightManager.h"


class SystemLight : public ISystem
{
	LightManager* mLightManager;
	IComponent::ComponentTypes mMask;

public:
	SystemLight();
	~SystemLight() = default;
	virtual void Run(Entity* Entity);

	
};

