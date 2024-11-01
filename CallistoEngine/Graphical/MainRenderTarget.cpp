#include "MainRenderTarget.h"
#include "Window_GL.h"

void MainRenderTarget::Free()
{
	if (mDepthTexture > 0)
	{
		glDeleteTextures(1, &mDepthTexture);
		mDepthTexture = 0;
	}
}

void MainRenderTarget::Activate()
{
	target.Activate();
}

void MainRenderTarget::Create(int width, int height)
{
	Free();
	target.Resize(width, height);

	glGenTextures(1, &mDepthTexture);
	glBindTexture(GL_TEXTURE_2D, mDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTexture, 0);
}

void MainRenderTarget::BindTextures()
{
	target.BindTextures();
}

MainRenderTarget::MainRenderTarget() : mDepthTexture(0)
{
	Create(Window_GL::TheWindow->GetWindowWidth(), Window_GL::TheWindow->GetWindowHeight());
}

MainRenderTarget::~MainRenderTarget()
{
	Free();
}
