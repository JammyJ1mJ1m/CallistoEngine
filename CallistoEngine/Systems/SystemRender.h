#pragma once
#include "ISystem.h"
#include "../Graphical/Renderer.h"
#include "SystemRenderForward.h"
#include "SystemRenderDeferred.h"

enum class RenderMode
{
	STANDARD = 0,
	NORMALS = 1,
	POSITION = 2,
	SPECULAR = 3,
	//DEPTH
};

// master render system will handle and call relevant classes, forward, deferred UI etc
class SystemRender : public ISystem
{
	//IComponent::ComponentTypes mMask;
	Renderer* mRenderer;
	SystemRenderForward* mRenderSystemForward;
	SystemRenderDeferred* mRenderSystemDeferred;

	unsigned int gBuffer;
	unsigned int gPosition, gNormal, gAlbedoSpec, rboDepth;

	ShaderObject_GL* shaderGeometryPass;
	ShaderObject_GL* shaderLightingPass;
	ShaderObject_GL* shaderLightBox;



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

