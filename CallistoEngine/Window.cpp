#include "Window.h"

Window* Window::TheWindow = nullptr;

Window::Window()
{
	TheWindow = this;
}


Window::~Window()
{
}

