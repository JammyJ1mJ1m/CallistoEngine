#include "InputManager.h"

InputManager* InputManager::mInstance = nullptr;

InputManager::InputManager() 
{
	for (int i = 0; i < mKeyCount; i++)
	{
		mKeys[i] = false;
	}
}

InputManager::~InputManager()
{
}
