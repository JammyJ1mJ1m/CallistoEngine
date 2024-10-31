#include "SystemRender.h"
#include "ComponentTransform.h"
#include "ComponentShader.h"
#include "../Misc/Camera.h"
#include "../Graphical/MainRenderTarget.h"

SystemRender::SystemRender(Renderer* pRenderer)
{
	mRenderer = pRenderer;

	mRenderSystemDeferred = new SystemRenderDeferred(mRenderer);
	mRenderSystemForward = new SystemRenderForward(mRenderer);
}

SystemRender::~SystemRender()
{
	delete mRenderSystemForward;
	delete mRenderSystemDeferred;
}

void SystemRender::Run(Entity* pEntity)
{}

void SystemRender::Render(std::vector<Entity*>& pEntities)
{
	mRenderSystemDeferred->Begin();

	for (auto& enti : pEntities)
	{

		mRenderSystemDeferred->Run(enti);
		for (auto& child : enti->GetChildren())
		{
			mRenderSystemDeferred->Run(child);
		}
	}

	mRenderSystemDeferred->RunLighting();

	mRenderSystemDeferred->End();


	bool render = true;
	// blit the frame buffers
	if (render)
	{

		int from = mRenderer->GetGBuffer()->GetGBufferID();
		int to = mRenderer->GetMainTarget()->GetTextureID();

		mRenderSystemDeferred->CopyBuffer(from,to);

		mRenderSystemForward->Begin();

		// render forward here
		for (auto& enti : pEntities)
		{
			mRenderSystemForward->Run(enti);
		}
		mRenderSystemForward->End();
		// after all renderinng is done now post process
	}
	PostProcess();
}

void SystemRender::Begin()
{
	mRenderer->EndForward();
}

void SystemRender::End()
{
	mRenderer->End();
}

void SystemRender::PostProcess()
{
	mRenderer->Postprocess();
}

