#pragma once

#include "Window.h"
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
// #include "GLFW/glfw3.h"
#include "Renderer_GL.h"
#include "Game.h"
#include "Include/glad/glad.h"

class Window_GL : public Window
{
	GLFWwindow* _GlfwWindow;
	int lastPressedKey;
	// void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
	void SetLastKey(int pKey ) { lastPressedKey = pKey; }
	Window_GL(Game* game, const int width, const int height);
	virtual int Initialise(const char* pTitle);
	void OnKeyboard(int key );
	virtual void Close();
	virtual void Update();
	virtual void SetTitle(const char* pTitle);
	virtual ~Window_GL();
};
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#if OPENGL
#endif // OPENGL