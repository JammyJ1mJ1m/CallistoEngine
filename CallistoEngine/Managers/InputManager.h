#pragma once
#include "../Commands/Command.h"


#define mKeyCount 512

class InputManager
{
	
	bool mKeys[mKeyCount];
	
public:
	InputManager();
	~InputManager();

	const bool* GetKeys() { return mKeys; }
	const bool GetKey(int key) { return mKeys[key]; }
	void SetKeyState(int key, bool down) { mKeys[key] = down; }
	//const void GetMousePosition(int& x, int& y);


	const int GetKeysSize() { return mKeyCount; }

};