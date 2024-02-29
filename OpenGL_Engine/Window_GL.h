#pragma once
#if OPENGL

#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer_GL.h"

class Window_GL : public Window
{
	GLFWwindow* _window;
public:

	Window_GL(Game* game, const int width, const int height);
	virtual int Initialise();

	//virtual void OnResize( int width, int height) override;

	void processInput(GLFWwindow* window);

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	virtual void Close();

	virtual void Update();

	virtual ~Window_GL();
};
#endif // OPENGL