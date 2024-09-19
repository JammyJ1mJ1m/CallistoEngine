#pragma once
#include "Renderer.h"
// #define GLFW_INCLUDE_NONE
//#define GLFW_EXPOSE_NATIVE_X11
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "../Components/Entity.h"

#include "PostProcessor.h"


class Renderer_GL : public Renderer
{
	unsigned int shaderProgram;
	unsigned int VAO;

	// PP stuff
	GLuint framebuffer;
	GLuint rbo;
	PostProcessor* PP;
/*	GLuint textureColorbuffer;
	GLuint quadVAO, quadVBO;
	GLuint postProcessingShader; */ // Shader program for post-processing


public:
	virtual void ClearScreen();
	virtual void Destroy();
	// virtual void Draw(const Mesh* mesh, glm::mat4 MVM, const Colour& colour);
	virtual void Initialise(int width, int height);
	void CreateRBO(int width, int height);
	virtual void SwapBuffers();
	virtual void Render(Entity* entity);
	virtual void DrawPP();
	virtual void StartPP();
	virtual void BindRBO(int W, int H) ;
};

