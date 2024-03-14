#pragma once
#if OPENGL

#include "Window.h"
//#include "GLFW/glfw3.h"
//#include "glad/glad.h"

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include "Renderer_GL.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "Game.h"

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
	virtual int GetWindowWidth() { return _width; };
	virtual int GetWindowHeight() { return _height; }


	virtual ~Window_GL();
};
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#endif // OPENGL