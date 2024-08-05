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
	GLFWwindow* mGlfwWindow;
	GLFWwindow* mOldWindow;
	int lastPressedKey;
	// void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
	void SetLastKey(int pKey ) { lastPressedKey = pKey; }
	Window_GL(Game* game, const int width, const int height);
	virtual int Initialise(const char* pTitle);
	void OnKeyboard(int key, bool ispress );
	virtual void Close();
	virtual void Update();
	virtual void SetTitle(const char* pTitle);
	virtual int GetWindowWidth() { return mWindowWidth; };
	virtual int GetWindowHeight() { return mWindowHeight; }
	virtual int GetWindowPosX() { return mWindowPosX; }
	virtual int GetWindowPosY() { return mWindowPosY; }
	virtual void SetWindowPosX(const int pX);
	virtual void SetWindowPosY(const int pY);
	virtual const void SetFullscreen();
	virtual const void SetWindowed();
	virtual const void ToggleFullscreen(bool pState);


	virtual ~Window_GL();
};
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#endif // OPENGL