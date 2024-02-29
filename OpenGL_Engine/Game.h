#pragma once
#include "Window.h"
#include "Renderer.h"
class Game
{
protected:
	double _deltaTime;
	bool _keyStates[256];
	Window* _window;
	Renderer* _renderer;
	double _lastFrameTime;


public:
	virtual ~Game() {};

	// methods
	virtual void Initialise(Window* w) = 0;
	virtual void OnKeyboard(int key, bool down) = 0;
	virtual void Render() = 0;
	virtual void Run() = 0;
	virtual bool IsRunning() = 0;
};
