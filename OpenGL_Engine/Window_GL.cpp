#include "Window_GL.h"
#include <iostream>

void Window_GL::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window_GL* instance = static_cast<Window_GL*>(glfwGetWindowUserPointer(window));
	if (instance == nullptr) { return; }

	if (action == GLFW_PRESS) {
		instance->SetLastKey(key);
		std::cout << "Key pressed: " << key << std::endl;
	}

	//    // lastPressedKey = key;
	//    SetLastKey(key);
	//    std::cout << "Key pressed: " << key << std::endl;
}

Window_GL::Window_GL(Game* game, const int width, const int height)
{
	_width = width;
	_height = height;
	_game = game;
	lastPressedKey = -1;
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
	// glfw window creation
	// --------------------
	_window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
	if (_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	glfwSetKeyCallback(_window, key_callback);

	glfwSetWindowUserPointer(_window, this);


	glfwMakeContextCurrent(_window);
	// TheWindow = static_cast<Window_GL*>(glfwGetWindowUserPointer(_window));

	void framebuffer_size_callback(GLFWwindow * window, int width, int height);

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);


	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

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

void Window_GL::OnKeyboard(GLFWwindow* window)
{

	if (glfwGetKey(window, 256) == 1)
	{
		glfwSetWindowShouldClose(window, true);
		Close();
	}
}





void Window_GL::Close()
{
	glfwTerminate();
}

void Window_GL::Update()
{
	// OnKeyboard(_window);

	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void Window_GL::SetTitle(const char* pTitle)
{
	_title = pTitle;
}

Window_GL::~Window_GL()
{
	delete _renderer;
}
