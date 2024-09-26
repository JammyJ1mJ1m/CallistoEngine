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
#include "../Game.h"

class Window_GL : public Window
{
	GLFWwindow* mGlfwWindow;
	GLFWwindow* mOldWindow;
	int lastPressedKey;
	// void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	// mouse related
	float mLastMouseX;
	float mLastMouseY;
	bool mFirstMouse;
	float mYaw;
	float mPitch;


	// events - cant put these in the base class as most of them require glfw specific window
	static void OnMaximise(GLFWwindow* window, int maximized);
	static void OnMouse(GLFWwindow* window, double xpos, double ypos);
	static void OnWindowPos(GLFWwindow* window, int xpos, int ypos);
	static void OnResize(GLFWwindow* window, int width, int height);
	static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void OnClose(GLFWwindow* window);


public:
	const bool GetFirstMouse() { return mFirstMouse; }
	void SetFirstMouse(bool pState) { mFirstMouse = pState; }

	const float GetLastMouseX() { return mLastMouseX; }
	const float GetLastMouseY() { return mLastMouseY; }
	void SetLastMouseX(float pX) { mLastMouseX = pX; }
	void SetLastMouseY(float pY) { mLastMouseY = pY; }

	virtual const void GetMousePos(float& pX, float& pY) override { pX = mLastMouseX; pY = mLastMouseY; }

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
	//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#endif // OPENGL