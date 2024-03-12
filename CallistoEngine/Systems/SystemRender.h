#pragma once
#include "ISystem.h"


class SystemRender : public ISystem
{
	IComponent::ComponentTypes mMask;

	public:
	SystemRender();
	~SystemRender() = default;
	virtual void Run(Entity* Entity);

	
};

