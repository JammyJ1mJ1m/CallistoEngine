#pragma once
#include <glad/glad.h>

#include "RenderTarget.h"

class MainRenderTarget final
{
private:
	RenderTarget target;

	unsigned int mDepthTexture;

	void Free();

public:
	inline unsigned int GetDepthBufferID() const { return mDepthTexture; }
	inline unsigned int GetTextureID() const { return target.GetTexture(); }

	void Activate();

	void Create(int width, int height);

	void BindTextures();

	MainRenderTarget();
	~MainRenderTarget();
};