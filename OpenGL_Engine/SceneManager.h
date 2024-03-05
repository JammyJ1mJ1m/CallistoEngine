#pragma once
#include "Window.h"



class SceneManager
{
	int _width;
	int _height;

	Window* _window;

public:

	SceneManager(const int pWidth, const int pHeight);

	// getters
	int  GetWindowWidth() { return _width; }
	int  GetWindowHeight() { return _height; }

	// methods
	void Run();

	~SceneManager() = default;
};