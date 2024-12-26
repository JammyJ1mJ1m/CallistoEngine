#include "Renderer.h"

Renderer* Renderer::mInstance = nullptr;

//Renderer::Renderer()
//{
//}

Renderer::~Renderer()
{
}

void Renderer::CycleRenderMode()
{
	mRenderMode++;
	if (mRenderMode > 5)
		mRenderMode = 0;
}
