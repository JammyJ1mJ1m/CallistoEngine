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
	if (mRenderMode > 4)
		mRenderMode = 0;
}
