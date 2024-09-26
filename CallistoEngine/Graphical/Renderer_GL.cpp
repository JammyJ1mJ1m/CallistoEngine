#include "Renderer_GL.h"
#include "../Components/ComponentModel.h"
#include "../Components/ComponentShader.h"
#include "../Managers/ResourceManager.h"

void Renderer_GL::InitialisePP()
{
	float quadVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

}

void Renderer_GL::InitialiseScreenQuad()
{
	float quadVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

}

void Renderer_GL::RenderScreenQuad()
{
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//	glBindVertexArray(0);
	//	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer_GL::Begin()
{
	glEnable(GL_DEPTH_TEST);
	mMainTarget->Activate();
}

void Renderer_GL::End()
{
	glDisable(GL_DEPTH_TEST);
	mMainTarget->BindTextures();
}

void Renderer_GL::Postprocess()
{
	for (PostProcessEffect* postProPass : postProcessShaders)
	{
		if (postProPass->IsActive())
			postProPass->Render();

	}

	finalPass.Render();
}

void Renderer_GL::AddEffect(PostProcessEffect* effect)
{
	postProcessShaders.push_back(effect); effect->Create();
}

void Renderer_GL::ClearScreen()
{
	// binds to the frame buffer for drawing the scene - later used in PP
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glEnable(GL_DEPTH_TEST);
	glClearColor(_clearColour.GetX(), _clearColour.GetY(), _clearColour.GetZ(), _clearColour.GetW());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer_GL::Destroy()
{
}

void Renderer_GL::Initialise(int width, int height)
{
	PostProcessEffect pp2 = PostProcessEffect();
	pp2.LoadShader("Resources/Shaders/PP/PP.vert", "Resources/Shaders/PP/defaultPP.frag", "DefaultPP");
	finalPass = pp2;
	//finalPass("Assets/Shaders/PostProcessing/pp_FinalImage")

	mFinalTarget = new FinalTarget();
	finalPass.SetTarget(mFinalTarget);




	_clearColour = { 0.5f, 0.5f, 0.5f, 1.0f };

	PP = &PostProcessor::GetInstance();
	//// 1. Create framebuffer
	//glGenFramebuffers(1, &framebuffer);
	//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	mMainTarget = new MainRenderTarget();
	mFinalTarget = new FinalTarget();

	InitialisePP();
	//PP->Initialise();

	//// 2. Create texture to store scene
	//glGenTextures(1, &textureColorbuffer);
	//glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	// 3. Create renderbuffer for depth and stencil
	CreateRBO(width, height);
}

void Renderer_GL::CreateRBO(int width, int height)
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glDeleteRenderbuffers(1, &rbo);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	// Check framebuffer completeness
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer_GL::Resize(int pWidth, int pHeight)
{
	mMainTarget->Create(pWidth, pHeight);
	mFinalTarget->Resize(pWidth, pHeight);

	//for (PostProcess* postProPass : postProcessShaders)
	//	postProPass->Resize(pWidth, pHeight);


	// glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//CreateRBO(pWidth, pHeight);
	//glBindFramebuffer(GL_FRAMEBUFFER, rbo);
}

void Renderer_GL::SwapBuffers()
{
}

void Renderer_GL::Render(Entity* entity)
{

	ComponentModel* model = entity->GetComponent <ComponentModel>();
	model->GetMesh()->Draw();
}

void Renderer_GL::DrawPP()
{
	PP->DrawPP();
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glDisable(GL_DEPTH_TEST); 
	//glClear(GL_COLOR_BUFFER_BIT);

	//glUseProgram(postProcessingShader);
	//glBindVertexArray(quadVAO);
	//glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// Screen quad texture (the scene)
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer_GL::StartPP()
{
}

