#pragma once
#include <string>

class Game;
class Renderer;


// not entirely sure what this is doing here
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

protected:
	std::string _title;

public:

	static Window* TheWindow;

	float _width;
	float _height;

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
	virtual void SetTitle(const char* pTitle) = 0;

	virtual int GetWindowWidth() = 0;
	virtual int GetWindowHeight() = 0;

	virtual int Initialise(const char* pTitle) = 0;
	//virtual void OnResize(int width, int height) = 0;
	virtual void Close() = 0;

};

