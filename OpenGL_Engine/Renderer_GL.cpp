#include "Renderer_GL.h"

void Renderer_GL::ClearScreen()
{
	glClearColor(_clearColour.GetX(), _clearColour.GetY(), _clearColour.GetZ(), _clearColour.GetW());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer_GL::Destroy()
{
	// delete _shader; // Will delete shader objects automatically through ref counting
}

void Renderer_GL::Initialise(int width, int height)
{
	// Setup projection
	// _PM = glm::ortho(-1, +1, -1, +1, -1, +1);

	// Setup viewport and enable depth testing
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);


	/////////////////////////////
	// Setup shaders

	// Create shader objects (and compile them)
	//_vertexShader = new ShaderObject_GL("shader.vert", GL_VERTEX_SHADER);
	//_fragmentShader = new ShaderObject_GL("shader.frag", GL_FRAGMENT_SHADER);

	//// Create shader program and attach shader objects
	//_shader = new ShaderProgram_GL();
	//_shader->attachShader(_vertexShader);
	//_shader->attachShader(_fragmentShader);

	//// Link and use the shader
	//_shader->link();
	//_shader->use();

	//_shader->setUniformMatrix("PM", 4, 1, false, glm::value_ptr(_PM));
}

void Renderer_GL::SwapBuffers()
{
}
