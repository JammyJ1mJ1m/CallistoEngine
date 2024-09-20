#if OPENGL

#include "Window_GL.h"
#include <iostream>
#include "DisplayManager.h"
#include "PostProcessor.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Window_GL* instance = static_cast<Window_GL*>(glfwGetWindowUserPointer(window));
	if (!instance) { return; }


	instance->SetLastMouseX((float)xpos);
	instance->SetLastMouseY((float)ypos);
}

// when the window position changes
void window_pos_callback(GLFWwindow* window, int xpos, int ypos)
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
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	if (width == 0 || height == 0) {
		return;
	}

	Window_GL* instance = static_cast<Window_GL*>(glfwGetWindowUserPointer(window));
	if (instance) {
		instance->mWindowWidth = width;
		instance->mWindowHeight = height;
		instance->SetHasWindowSizeChanged(true);

		glViewport(0, 0, width, height);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		// re calculate the RBO
		instance->_renderer->BindRBO(width, height);
		// also want to update the post processing size
		PostProcessor::GetInstance().UpdateSize(width, height);
	}
}

// when keys are pressed
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
	_renderer = new Renderer_GL();

	DisplayManager& displayManager = DisplayManager::GetInstance();



	// glfw: initialize and configure
   // ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); -- use this when doing fullscreen borderless
#ifdef __APPLE__
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// glfw window creation
	// --------------------



	// this setting will be passed from display manager
	if (displayManager.GetFullscreen())
	{
		SetFullscreen();
	}
	else
	{
		SetWindowed();
		//_GlfwWindow = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
	}
	if (mGlfwWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mGlfwWindow);

	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	glfwSetKeyCallback(mGlfwWindow, key_callback);

	glfwSetWindowUserPointer(mGlfwWindow, this);

	// this setting will be passed from display manager
	if (!displayManager.GetVSync() ? false : true)
		glfwSwapInterval(0); // disable vsync


	void framebuffer_size_callback(GLFWwindow * window, int width, int height);

	glfwSetFramebufferSizeCallback(mGlfwWindow, framebuffer_size_callback);

	void window_pos_callback(GLFWwindow * window, int xpos, int ypos);
	glfwSetWindowPosCallback(mGlfwWindow, window_pos_callback);

	if (displayManager.GetCursorEnabled())
		glfwSetInputMode(mGlfwWindow, GLFW_CURSOR, GLFW_CURSOR);
	else
		glfwSetInputMode(mGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	void mouse_callback(GLFWwindow * window, double xpos, double ypos);
	glfwSetCursorPosCallback(mGlfwWindow, mouse_callback);


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
		glfwSetWindowMonitor(mGlfwWindow, monitor, 0, 0, mode->width, mode->height, 0);
	}
	else
	{
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