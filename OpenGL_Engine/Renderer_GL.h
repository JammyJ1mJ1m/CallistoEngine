#pragma once
#include "Renderer.h"
class Renderer_GL : public Renderer
{
	virtual void ClearScreen();
	virtual void Destroy();
	// virtual void Draw(const Mesh* mesh, glm::mat4 MVM, const Colour& colour);
	virtual void Initialise(int width, int height);
	virtual void SwapBuffers();
};

