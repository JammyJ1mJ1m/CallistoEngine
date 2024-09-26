#pragma once

class RenderTarget
{
private:
	// FrameBufferObject
	unsigned int mFBO;
	// FrameBufferTexture
	unsigned int mFBT;

	void Free();

public:
	virtual void Activate();

	void BindTextures();

	inline unsigned int GetTexture() const { return mFBT; }

	void Resize(int width, int height);

	RenderTarget();
	~RenderTarget();
};

