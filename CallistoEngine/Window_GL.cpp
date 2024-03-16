#include "Window_GL.h"
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Window::TheWindow->SetLastKey(key);
	Window_GL* instance = dynamic_cast<Window_GL*>(Window::TheWindow);
	// Window_GL* instance = dynamic_cast<Window_GL*>((Window*)glfwGetWindowUserPointer(window));
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
	_width = width;
	_height = height;
	_game = game;
	lastPressedKey = -1;
	// TheWindow = this;
}

int Window_GL::Initialise(const char* pTitle)
{
	SetTitle(pTitle);
	_renderer = new Renderer_GL();


	// glfw: initialize and configure
   // ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// glfw window creation
	// --------------------
	_GlfwWindow = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
	if (_GlfwWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	glfwSetKeyCallback(_GlfwWindow, key_callback);

	glfwSetWindowUserPointer(_GlfwWindow, this);


	glfwMakeContextCurrent(_GlfwWindow);
	// TheWindow = static_cast<Window_GL*>(glfwGetWindowUserPointer(_window));
	// Window::TheWindow = this;

	void framebuffer_size_callback(GLFWwindow * window, int width, int height);

	glfwSetFramebufferSizeCallback(_GlfwWindow, framebuffer_size_callback);


	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	_renderer->Initialise(0, 0);
	return 0;
	//while (!glfwWindowShouldClose(window))
	//{
	//    // input
	//    // -----
	//    processInput(window);

	//    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	//    // -------------------------------------------------------------------------------
	//    glfwSwapBuffers(window);
	//    glfwPollEvents();
	//}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	// glfwTerminate();
}

void Window_GL::OnKeyboard(int key, bool ispress)
{
	_game->OnKeyboard(key, ispress);

	/*if (glfwGetKey(window, 256) == 1)
	{
		glfwSetWindowShouldClose(window, true);
		Close();
	}*/
}





void Window_GL::Close()
{
	glfwTerminate();
}

void Window_GL::Update()
{
	// OnKeyboard(_window);

	glfwSwapBuffers(_GlfwWindow);
	glfwPollEvents();
}

void Window_GL::SetTitle(const char* pTitle)
{
	_title = pTitle;
}

Window_GL::~Window_GL()
{
	delete _renderer;
	delete _game;
}
