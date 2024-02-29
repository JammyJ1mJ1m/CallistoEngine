#pragma once
#if OPENGL

#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window_GL : public Window
{
public:

	Window_GL(Game* game, const int width, const int height);
	virtual int Initialise();

	//virtual void OnResize( int width, int height) override;

	void processInput(GLFWwindow* window);

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	virtual ~Window_GL();
};
#endif // OPENGL