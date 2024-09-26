#include "RenderTarget.h"
#include "Window_GL.h"
#include "Renderer_GL.h"

#define EXISTS(buffer) buffer > 0

void RenderTarget::Free()
{
	if (EXISTS(mFBO))
	{
		glDeleteFramebuffers(1, &mFBO);
		mFBO = 0;
	}

	if (EXISTS(mFBT))
	{
		glDeleteTextures(1, &mFBT);
		mFBT = 0;
	}
}

void RenderTarget::Activate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderTarget::BindTextures()
{
	Renderer_GL::GetInstance().SetID(mFBT);

}

void RenderTarget::Resize(int width, int height)
{
	if (width == 0 || height == 0)
		return;

	Free();

	glGenFramebuffers(1, &mFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

	glGenTextures(1, &mFBT);
	glBindTexture(GL_TEXTURE_2D, mFBT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mFBT, 0);
}

RenderTarget::RenderTarget() :
	mFBO(0), mFBT(0)
{
	Resize(Window::TheWindow->GetWindowWidth(), Window::TheWindow->GetWindowHeight());
}

RenderTarget::~RenderTarget()
{
	Free();
}
