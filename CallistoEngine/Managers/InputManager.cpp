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

void InputManager::LoadDefaultKeyBindings()
{
	mKeyBindingMap = {
		{ 'W', "move_forward" },
		{ 'S', "move_back" },
		{ 'A', "move_left" },
		{ 'D', "move_right" },
		{ 'Q', "look_left" },
		{ 'E', "look_right" }
	};
}

void InputManager::UpdatePrevKeyStates()
{
	// Copy the current key states to the previous key states array
	std::copy(std::begin(mKeys), std::end(mKeys), std::begin(mPrevKeys));
}


InputManager::~InputManager()
{
}
