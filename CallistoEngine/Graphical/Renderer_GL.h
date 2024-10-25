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

#include "PositionColourTarget.h"
#include "NormalColourTarget.h"
#include "SpecularAndColourTarget.h"

#include "GBuffer.h"


class Renderer_GL : public Renderer
{
	unsigned int shaderProgram;
	unsigned int VAO;

	// use this buffer as the gBuffer?
	MainRenderTarget* mMainTarget;

	FinalTarget* mFinalTarget;

	// position color buffer
	PositionColourTarget* positionColor;
	// normal color buffer
	NormalColourTarget* normalColour;
	// color + specular color buffer
	SpecularAndColourTarget* colorSpecular;

	GBuffer* mGBuffer;

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

	unsigned int depth, frame;
	PostProcessEffect finalPass;

	std::vector<PostProcessEffect*> postProcessShaders;

	// Private constructor to prevent instantiation
	Renderer_GL() = default;


public:
	void RenderScreenQuad() override;
	

	static Renderer& GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new Renderer_GL();

		return *mInstance;
	}

	MainRenderTarget* GetMainTarget() override{ return mMainTarget; }
	void SetFrame(unsigned int pFrame) override { depth = GetDepth(); this->frame = pFrame; }
	unsigned int GetFrame() const override { return frame; }
	// void SetPixelated(unsigned int b) override { this->b = b; }
	// unsigned int GetPixelated() const override { return b; }
	inline unsigned int GetRawFrame() const override { return mMainTarget->GetTextureID(); }
	//unsigned int GetDepth() const override { return mMainTarget->GetDepthBufferID(); }
	unsigned int GetDepth() const override { return mGBuffer->GetDepthBufferID(); }
	virtual GBuffer* GetGBuffer() override { return mGBuffer; }

	// void Resize(int width, int height);

	void Begin() override;
	void End() override;
	void Postprocess() override;
	void AddEffect(PostProcessEffect* effect) override;
	void SetEffectStatus(const char* pName, const bool pBool) const;


	virtual void ClearScreen();
	// virtual void Destroy();
	virtual void Initialise(int width, int height);
	// virtual void SwapBuffers();
	virtual void Render(Entity* entity);
	// virtual void DrawPP();
	// virtual void StartPP();
	virtual void Resize(int pWidth, int pHeight);
	void CreateRBO(int width, int height);

	void UnbindFrame() override;
	void EnableDepthTest() const;
	void DisableDepthTest() const;

};

