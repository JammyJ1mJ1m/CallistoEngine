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
	bool mHasWindowSizeChanged;

protected:
	std::string _title;
	bool mIsFullscreen;

public:

	static Window* TheWindow;

	int mWindowWidth;
	int mWindowHeight;

	int mWindowWidthBackup;
	int mWindowHeightBackup;

	int mWindowPosX;
	int mWindowPosY;

	Game* _game;
	Renderer* _renderer;

	// Structors

	Window();
	virtual ~Window();

	Game* GetGame() const { return _game; }
	Renderer* GetRenderer() const { return _renderer; }

	virtual void Update() = 0;
	virtual void SetTitle(const char* pTitle) = 0;

	virtual int GetWindowWidth() = 0;
	virtual int GetWindowHeight() = 0;
	virtual int GetWindowPosX() = 0;
	virtual int GetWindowPosY() = 0;
	virtual void SetWindowPosX(const int pX) = 0;
	virtual void SetWindowPosY(const int pY) = 0;
	virtual const void SetFullscreen() = 0;
	virtual const void SetWindowed() = 0;
	virtual const void ToggleFullscreen(bool pState) = 0;

	const bool GetHasWindowSizeChanged() { return mHasWindowSizeChanged; }
	const void SetHasWindowSizeChanged(bool value) { mHasWindowSizeChanged = value; }
	const bool GetIsFullscreen() { return mIsFullscreen; }
	void SetIsFullscreen(bool value) { mIsFullscreen = value; }


	virtual int Initialise(const char* pTitle) = 0;
	//virtual void OnResize(int width, int height) = 0;
	virtual void Close() = 0;

};

