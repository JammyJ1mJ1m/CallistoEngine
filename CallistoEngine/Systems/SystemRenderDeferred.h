#pragma once
#include "ISystem.h"
#include "../Graphical/Renderer.h"
#include "../Objects/ShaderObject_GL.h"
#include "../Graphical/RenderTarget.h"


class SystemRenderDeferred : public ISystem
{
	IComponent::ComponentTypes mMask;
	Renderer* mRenderer;
	ShaderObject* mLightingShader;

public:
	SystemRenderDeferred(Renderer* pRenderer);
	~SystemRenderDeferred() = default;
	virtual void Run(Entity* Entity);

	//void DrawPP();
	void Begin();
	void End();
	void PostProcess();
	void RunLighting();
	void CopyBuffer(const int pCopyFrom, const int pCopyTo);

};

