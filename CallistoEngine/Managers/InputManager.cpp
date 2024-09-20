#include "InputManager.h"

InputManager::InputManager() 
{
	for (int i = 0; i < mKeyCount; i++)
	{
		mKeys[i] = false;
	}
}

const bool InputManager::GetKeyDown(int key)
{
	return mKeys[key] && !mPrevKeys[key];
}

void InputManager::UpdatePrevKeyStates()
{
	// Copy the current key states to the previous key states array
	std::copy(std::begin(mKeys), std::end(mKeys), std::begin(mPrevKeys));
}


InputManager::~InputManager()
{
}
