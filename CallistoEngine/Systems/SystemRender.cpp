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


	int mainTargetBufferID = mRenderer->GetMainTarget()->GetTextureID(); //   <-- i want to write to this buffers depth
	int mainTargetDepthID = mRenderer->GetMainTarget()->GetDepthBufferID();

	GBuffer* gBuff = mRenderer->GetGBuffer();

	int bufferID = gBuff->GetGBufferID();
	int albedoId = gBuff->GetAlbedoSpecTextureID();
	int depthId = gBuff->GetDepthBufferID();
	int normalsID = gBuff->GetNormalTextureID();
	int posID = gBuff->GetPositionTextureID();


	int from = mRenderer->GetGBuffer()->GetGBufferID();
	int to = mRenderer->GetMainTarget()->GetTextureID();

	mRenderSystemDeferred->CopyBuffer(from, to);


	mRenderSystemDeferred->End();


	bool render = true;
	// blit the frame buffers
	if (render)
	{
		

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

