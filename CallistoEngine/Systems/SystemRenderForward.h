#pragma once
#include "ISystem.h"
#include "../Graphical/Renderer.h"


class SystemRenderForward : public ISystem
{
	IComponent::ComponentTypes mMask;
	Renderer* mRenderer;

	public:
	SystemRenderForward(Renderer* pRenderer);
	~SystemRenderForward() = default;
	virtual void Run(Entity* Entity);

	//void DrawPP();
	void Begin();
	void End();
	void PostProcess();

};

