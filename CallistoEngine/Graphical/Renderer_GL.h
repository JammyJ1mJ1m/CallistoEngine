#pragma once
#include "Renderer.h"
// #define GLFW_INCLUDE_NONE
//#define GLFW_EXPOSE_NATIVE_X11
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "../Components/Entity.h"

#include "PostProcessor.h"

#include "RenderTarget.h"
#include "MainRenderTarget.h"
#include "FinalTarget.h"
#include "PostProcessEffect.h"


class Renderer_GL : public Renderer
{
	unsigned int shaderProgram;
	unsigned int VAO;

	MainRenderTarget* mMainTarget;
	FinalTarget* mFinalTarget;

	// PP stuff
	GLuint framebuffer;
	GLuint rbo;
	PostProcessor* PP;
/*	GLuint textureColorbuffer;
	GLuint quadVAO, quadVBO;
	GLuint postProcessingShader; */ // Shader program for post-processing

	// NEW PP stuff
	unsigned int quadVAO, quadVBO;

	void InitialisePP();

	unsigned int depth, f, b;
	PostProcessEffect finalPass;

	std::vector<PostProcessEffect*> postProcessShaders;

	// Private constructor to prevent instantiation
	Renderer_GL() = default;


	void InitialiseScreenQuad();

public:
	void RenderScreenQuad() override;
	

	static Renderer& GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new Renderer_GL();

		return *mInstance;
	}


	void SetID(unsigned int f) override { depth = GetDepth(); this->f = f; }
	unsigned int GetID() const override { return f; }
	// void SetPixelated(unsigned int b) override { this->b = b; }
	// unsigned int GetPixelated() const override { return b; }
	inline unsigned int GetRawFrame() const override { return mMainTarget->GetTextureID(); }
	unsigned int GetDepth() const override { return mMainTarget->GetDepthBufferID(); }

	// void Resize(int width, int height);

	void Begin() override;
	void End() override;
	void Postprocess() override;
	void AddEffect(PostProcessEffect* effect) override;


	virtual void ClearScreen();
	virtual void Destroy();
	virtual void Initialise(int width, int height);
	virtual void SwapBuffers();
	virtual void Render(Entity* entity);
	virtual void DrawPP();
	virtual void StartPP();
	virtual void Resize(int pWidth, int pHeight);
	void CreateRBO(int width, int height);
};

