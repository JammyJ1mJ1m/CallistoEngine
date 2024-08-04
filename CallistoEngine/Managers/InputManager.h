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
	
public:
	InputManager();
	~InputManager();

	const bool* GetKeys() { return mKeys; }
	const bool GetKey(int key) { return mKeys[key]; }
	void SetKeyState(int key, bool down) { mKeys[key] = down; }
	//const void GetMousePosition(int& x, int& y);


	const int GetKeysSize() { return mKeyCount; }

};