#include "Window.h"

Window* Window::TheWindow = nullptr;

Window::Window()
{
	mHasWindowSizeChanged = false;
	TheWindow = this;
}


Window::~Window()
{
}

