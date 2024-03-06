#pragma once
#include "Renderer.h"
// #define GLFW_INCLUDE_NONE
//#define GLFW_EXPOSE_NATIVE_X11
#include <glad/glad.h>
#include "GLFW/glfw3.h"


class Renderer_GL : public Renderer
{
	unsigned int shaderProgram;
	unsigned int VAO;

public:
	virtual void ClearScreen();
	virtual void Destroy();
	// virtual void Draw(const Mesh* mesh, glm::mat4 MVM, const Colour& colour);
	virtual void Initialise(int width, int height);
	virtual void SwapBuffers();
	virtual void Render();
};

