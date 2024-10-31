#pragma once
#include "ISystem.h"
#include "../Graphical/Renderer.h"
#include "SystemRenderForward.h"
#include "SystemRenderDeferred.h"


// master render system will handle and call relevant classes, forward, deferred UI etc
class SystemRender : public ISystem
{
	//IComponent::ComponentTypes mMask;
	Renderer* mRenderer;
	SystemRenderForward* mRenderSystemForward;
	SystemRenderDeferred* mRenderSystemDeferred;

public:
	SystemRender(Renderer* pRenderer);
	~SystemRender();
	virtual void Run(Entity* pEntity);
	void Render(std::vector<Entity*>& pEntities);
	
	//void DrawPP();
	void Begin();
	void End();
	void PostProcess();

};

