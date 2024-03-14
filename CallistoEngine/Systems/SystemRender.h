#pragma once
#include "ISystem.h"
#include "../Renderer.h"


class SystemRender : public ISystem
{
	IComponent::ComponentTypes mMask;
	Renderer* mRenderer;

	public:
	SystemRender(Renderer* pRenderer);
	~SystemRender() = default;
	virtual void Run(Entity* Entity);

	
};

