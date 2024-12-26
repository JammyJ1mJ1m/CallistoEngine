#include "SystemRender.h"
#include "ComponentTransform.h"
#include "ComponentShader.h"
#include "../Misc/Camera.h"
#include "../Graphical/MainRenderTarget.h"
#include "../Game.h"
#include "../Lighting/PointLight.h"



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
		
		// 1. geometry pass: render scene's geometry/color data into gbuffer
		// -----------------------------------------------------------------
		mRenderSystemDeferred->Begin();

	
		for (auto& enti : pEntities)
		{
	
			mRenderSystemDeferred->Run(enti);
			for (auto& child : enti->GetChildren())
			{
				mRenderSystemDeferred->Run(child);
			}
		}
		mRenderer->UnbindFrame();
	
		// 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
		// -----------------------------------------------------------------------------------------------------------------------
	
		mRenderSystemDeferred->RunLighting();
	
		// mRenderSystemDeferred->End();
	
	
		 // 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
	// ----------------------------------------------------------------------------------
		int from = mRenderer->GetGBuffer()->GetGBufferID();
		int to = mRenderer->GetMainTarget()->GetBufferID();
	
		mRenderSystemDeferred->CopyBuffer(from, to);
	
	
	
		// 3. render lights / non deferred on top of scene
		// -----------------------------------------------
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

