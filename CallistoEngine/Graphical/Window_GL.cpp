#if OPENGL

#include "Window_GL.h"
#include <iostream>
#include "DisplayManager.h"
#include "PostProcessor.h"

void Window_GL::OnMaximise(GLFWwindow* window, int maximized)
{
	if (maximized)
	{
		// The window was maximized

	}
	else
	{
		// The window was restored

	}
}

void Window_GL::OnMouse(GLFWwindow* window, double xpos, double ypos)
{
	Window_GL* instance = static_cast<Window_GL*>(glfwGetWindowUserPointer(window));
	if (!instance) { return; }


	instance->SetLastMouseX((float)xpos);
	instance->SetLastMouseY((float)ypos);
}

// when the window position changes
void Window_GL::OnWindowPos(GLFWwindow* window, int xpos, int ypos)
{
	Window_GL* instance = static_cast<Window_GL*>(glfwGetWindowUserPointer(window));
	if (instance) {
		if (xpos <= 0 || ypos <= 0)
			return;
		instance->SetWindowPosX(xpos);
		instance->SetWindowPosY(ypos);
	}
}

// when the window size changes
void Window_GL::OnResize(GLFWwindow* window, int width, int height)
{
	if (width == 0 || height == 0) {
		return;
	}

	Window_GL* instance = static_cast<Window_GL*>(glfwGetWindowUserPointer(window));
	if (instance) {
		instance->mWindowWidth = width;
		instance->mWindowHeight = height;
		//instance->SetHasWindowSizeChanged(true);


		glViewport(0, 0, width, height);

		// Resize the renderer which will also resize all the PP
		instance->_renderer->Resize(width, height);
	}
}

// when keys are pressed
void Window_GL::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window_GL* instance = dynamic_cast<Window_GL*>(Window::TheWindow);
	if (instance == nullptr) { return throw; }

	if (action == GLFW_PRESS) {
		instance->SetLastKey(key);
		instance->OnKeyboard(key, true);
		std::cout << "Key pressed: " << key << std::endl;
	}
	else if (action == GLFW_RELEASE) {
		instance->SetLastKey(-1);
		instance->OnKeyboard(key, false);
		std::cout << "Key released: " << key << std::endl;
	}
}

void Window_GL::OnClose(GLFWwindow* window)
{
	Window_GL* instance = static_cast<Window_GL*>(glfwGetWindowUserPointer(window));
	instance->GetGame()->SetGameState(Quit);
}

Window_GL::Window_GL(Game* game, const int width, const int height)
{
	mWindowWidth = width;
	mWindowHeight = height;
	_game = game;
	lastPressedKey = -1;
	mFirstMouse = false;
	mLastMouseX = 0.0f;
	mLastMouseY = 0.0f;
	mYaw = -90.0f;
	mPitch = 0.0f;
	mGlfwWindow = nullptr;
}

int Window_GL::Initialise(const char* pTitle)
{

	mWindowPosX = 0;
	mWindowPosY = 0;

	SetTitle(pTitle);
	_renderer = &Renderer_GL::GetInstance();

	DisplayManager& displayManager = DisplayManager::GetInstance();



	// glfw: initialize and configure
   // ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// window transparency
	//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); -- use this when doing fullscreen borderless


	if (displayManager.GetFullscreen())
		SetFullscreen();
	else
		SetWindowed();
		//_GlfwWindow = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
	
	if (mGlfwWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mGlfwWindow);

	glfwSetWindowUserPointer(mGlfwWindow, this);

	// this setting will be passed from display manager
	if (!displayManager.GetVSync() ? false : true)
		glfwSwapInterval(0); // disable vsync

	if (displayManager.GetCursorEnabled())
		glfwSetInputMode(mGlfwWindow, GLFW_CURSOR, GLFW_CURSOR);
	else
		glfwSetInputMode(mGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(mGlfwWindow, OnKey);
	glfwSetFramebufferSizeCallback(mGlfwWindow, OnResize);
	glfwSetWindowPosCallback(mGlfwWindow, OnWindowPos);
	glfwSetCursorPosCallback(mGlfwWindow, OnMouse);
	glfwSetWindowCloseCallback(mGlfwWindow, OnClose);
	glfwSetWindowMaximizeCallback(mGlfwWindow, OnMaximise);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	_renderer->Initialise(GetWindowWidth(), GetWindowHeight());

	glfwGetWindowPos(mGlfwWindow, &mWindowPosX, &mWindowPosY);

	glfwPollEvents();

	// window transparency
	//glfwSetWindowOpacity(mGlfwWindow, 0.5f);

	return 0;

}

void Window_GL::OnKeyboard(int key, bool ispress)
{
	_game->OnKeyboard(key, ispress);
}

void Window_GL::Close()
{
	glfwTerminate();
}

void Window_GL::Update()
{
	glfwSwapBuffers(mGlfwWindow);
	glfwPollEvents();
}

void Window_GL::SetTitle(const char* pTitle)
{
	_title = pTitle;
	glfwSetWindowTitle(mGlfwWindow, pTitle);
}

void Window_GL::SetWindowPosX(const int pX)
{
	mWindowPosX = pX;
}

void Window_GL::SetWindowPosY(const int pY)
{
	mWindowPosY = pY;
}

const void Window_GL::SetFullscreen()
{
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	mWindowWidth = mode->width;
	mWindowHeight = mode->height;
	mGlfwWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, _title.c_str(), glfwGetPrimaryMonitor(), NULL); // fullscreen
	SetIsFullscreen(true);
}

const void Window_GL::SetWindowed()
{
	mGlfwWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, _title.c_str(), NULL, NULL);
	SetIsFullscreen(false);
}

const void Window_GL::ToggleFullscreen(bool pState)
{

	SetIsFullscreen(!GetIsFullscreen());

	//SetIsFullscreen(pState);

	if (GetIsFullscreen())
	{
		mWindowWidthBackup = mWindowWidth;
		mWindowHeightBackup = mWindowHeight;


		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

		//glfwSetWindowMonitor(mGlfwWindow, monitor, 0, 0, mode->width, mode->height, 0); - exclusive fullscreen
		glfwSetWindowMonitor(mGlfwWindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate); // windowed fullscreen

	}
	else
	{
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);

		int xy = 0;
		glfwSetWindowMonitor(mGlfwWindow, nullptr, GetWindowPosX(), GetWindowPosY(), mWindowWidthBackup, mWindowHeightBackup, 0);
		int x = GetWindowPosX();
		int y = GetWindowPosY();
	}

}

Window_GL::~Window_GL()
{
	delete _renderer;
	delete _game;
}
#endif // OPENGL