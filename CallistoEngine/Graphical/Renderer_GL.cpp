#include "Renderer_GL.h"
#include "../Components/ComponentModel.h"
#include "../Components/ComponentShader.h"
#include "../Managers/ResourceManager.h"
#include "../Game.h"

void Renderer_GL::InitialisePP()
{
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
}

void Renderer_GL::RenderScreenQuad()
{

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
	//	glBindVertexArray(0);
	//	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer_GL::Begin()
{
	// ClearScreen();
	//glEnable(GL_DEPTH_TEST);
	//mMainTarget->Activate();
	mGBuffer->Activate();
	GBuffer* gBuffer = GetGBuffer();
	// send the projection mat
	gBuffer->GetShader()->SetMat4("projection", Game::GetGame()->GetGameCamera()->GetProjection());
	// send the view mat
	gBuffer->GetShader()->SetMat4("view", Game::GetGame()->GetGameCamera()->GetView());
}

void Renderer_GL::BeginForward()
{
	//int gfbo = GetGBuffer()->GetGBufferID();
	//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gfbo); // write to default framebuffer

	//glBindFramebuffer(GL_FRAMEBUFFER, gfbo);

	EnableDepthTest();

	mMainTarget->Activate();
}

void Renderer_GL::End()
{

	mMainTarget->BindTextures();
	mGBuffer->BindTextures();
}

void Renderer_GL::EndForward()
{

	//glDisable(GL_DEPTH_TEST);
	mMainTarget->BindTextures();
}

void Renderer_GL::Postprocess()
{
	mMainTarget->BindTextures();

	for (PostProcessEffect* postProPass : postProcessShaders)
	{
		if (postProPass->IsActive())
			postProPass->Render();

	}

	finalPass.Render();
}

void Renderer_GL::AddEffect(PostProcessEffect* effect)
{
	postProcessShaders.push_back(effect); 
	effect->Create();
}

void Renderer_GL::SetEffectStatus(const char* pName, const bool pBool) const
{
	for (auto& effect : postProcessShaders)
	{
		std::string nmame = effect->GetName();
		if (nmame == pName)
			effect->SetActive(pBool);
	}
}

// will clear the depth and colour bits
void Renderer_GL::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//void Renderer_GL::Destroy()
//{
//}

void Renderer_GL::Initialise(int width, int height)
{

	PostProcessEffect pp2 = PostProcessEffect();
	pp2.LoadShader("Resources/Shaders/PP/PP.vert", "Resources/Shaders/PP/defaultPP.frag", "DefaultPP");
	finalPass = pp2;
	//finalPass("Assets/Shaders/PostProcessing/pp_FinalImage")

	mFinalTarget = new FinalTarget();
	finalPass.SetTarget(mFinalTarget);


	_clearColour = { 0.0f, 1.0f, 0.0f, 1.0f };
	glClearColor(_clearColour.GetX(), _clearColour.GetY(), _clearColour.GetZ(), _clearColour.GetW());


	//PP = &PostProcessor::GetInstance();
	//// 1. Create framebuffer
	//glGenFramebuffers(1, &framebuffer);
	//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	mMainTarget = new MainRenderTarget();
	//mFinalTarget = new FinalTarget();

	mGBuffer = new GBuffer();
	mGBuffer->Resize(width,height);

	InitialisePP();

	CreateRBO(width, height);
	EnableDepthTest();
}

void Renderer_GL::Render(Entity* entity)
{

	ComponentModel* model = entity->GetComponent <ComponentModel>();
	model->GetMesh()->Draw();
	// glDisable(GL_CULL_FACE);
	glActiveTexture(GL_TEXTURE0);

}

void Renderer_GL::Resize(int pWidth, int pHeight)
{
	//mMainTarget->Create(pWidth, pHeight);
	mFinalTarget->Resize(pWidth, pHeight);
	mGBuffer->Resize(pWidth,pHeight);

	for (PostProcessEffect* postProPass : postProcessShaders)
		postProPass->Resize(pWidth, pHeight);

}

void Renderer_GL::CreateRBO(int width, int height)
{
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//glDeleteRenderbuffers(1, &rbo);

	//glGenRenderbuffers(1, &rbo);
	//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	//// Check framebuffer completeness
	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	//	std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	////glBindFramebuffer(GL_FRAMEBUFFER, 0);
	rbo = mGBuffer->GetDepthBufferID();
	depth = mGBuffer->GetDepthBufferID();
}

void Renderer_GL::UnbindFrame()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer_GL::EnableDepthTest() const
{
	glEnable(GL_DEPTH_TEST);
}

void Renderer_GL::DisableDepthTest() const
{
	glDisable(GL_DEPTH_TEST);
}

void Renderer_GL::CopyBuffer(const int pCopyFrom, const int pCopyTo)
{
	int width, height;
	width = Game::GetGame()->GetGameCamera()->mWidth;
	height = Game::GetGame()->GetGameCamera()->mHeight;



	glBindFramebuffer(GL_READ_FRAMEBUFFER, pCopyFrom);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, pCopyTo); // write to default framebuffer
	// blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
	// the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
	// depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	UnbindFrame();
}