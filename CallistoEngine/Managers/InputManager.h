#pragma once
#include "../Commands/Command.h"
#include <map>
#include <string>

#define mKeyCount 512

using CommandMap = std::map<std::string, Command*>;
using CommandMapIterator = CommandMap::iterator;


using KeyBindingMap = std::map<int, std::string>;
using KeyBindingMapIterator = KeyBindingMap::iterator;

class InputManager
{
	
	bool mKeys[mKeyCount];
	bool mPrevKeys[mKeyCount];
	
public:
	InputManager();
	~InputManager();

	const bool* GetKeys() { return mKeys; }
	const bool GetKey(int key) { return mKeys[key]; }
	const bool GetKeyDown(int key);
	void SetKeyState(int key, bool down) 
	{ 
		mPrevKeys[key] = mKeys[key];
		mKeys[key] = down;
	}

	void UpdatePrevKeyStates();
	//const void GetMousePosition(int& x, int& y);


	const int GetKeysSize() { return mKeyCount; }

};