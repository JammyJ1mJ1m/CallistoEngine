#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Entity.h"
#include "Engine/Components/ModelComponent.h"
#include <vector>

class Game
{
protected:
	double _deltaTime;
	bool _keyStates[512];
	Window* _window;
	Renderer* _renderer;
	double _lastFrameTime;
	std::vector<Entity*> _entities;

public:
	virtual ~Game() {};

	// methods
	virtual void Initialise(Window* w) = 0;
	virtual void OnKeyboard(int key, bool down) = 0;
	virtual void Render() = 0;
	virtual void Run(const double dt) = 0;
	virtual bool IsRunning() = 0;
};
