#pragma once
#if OPENGL

#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer_GL.h"
#include "Game.h"

class Window_GL : public Window
{
	GLFWwindow* _GlfwWindow;
	int lastPressedKey;

public:
	void SetLastKey(int pKey ) { lastPressedKey = pKey; }

	Window_GL(Game* game, const int width, const int height);
	virtual int Initialise(const char* pTitle);

	//virtual void OnResize( int width, int height) override;

	void OnKeyboard(int key );

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);


	virtual void Close();

	virtual void Update();
	virtual void SetTitle(const char* pTitle);

	virtual ~Window_GL();
};
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#endif // OPENGL