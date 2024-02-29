#include "Window_GL.h"
#include <iostream>


Window_GL::Window_GL(Game* game, const int width, const int height)
{
	_width = width;
	_height = height;
    _game = game;
}

int Window_GL::Initialise(const char* pTitle)
{
    SetTitle(pTitle);
    _renderer = new Renderer_GL();

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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
    glfwMakeContextCurrent(_window);
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

void Window_GL::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        Close();
    }
}


void Window_GL::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window_GL::Close()
{
    glfwTerminate();
}

void Window_GL::Update()
{
    processInput(_window);

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
