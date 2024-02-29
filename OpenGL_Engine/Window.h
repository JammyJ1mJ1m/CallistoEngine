#pragma once
class Game;
class Renderer;

enum GameState
{
	Playing,
	Paused,
	Dead,
	Resetting,
	Quit
};

class Window
{
	// Constants and statics
public:

	static Window* TheWindow;

	int _width;
	int _height;

	Game* _game;
	Renderer* _renderer;



	// Data
public:

	// Structors
public:
	Window();
	virtual ~Window();

	Game* GetGame() const { return _game; }
	Renderer* GetRenderer() const { return _renderer; }

	virtual void Update() = 0;

	virtual int Initialise() = 0;
	//virtual void OnResize(int width, int height) = 0;
	virtual void Close() = 0;

};

