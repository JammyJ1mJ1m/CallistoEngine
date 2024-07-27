#pragma once

#define mKeyCount 512

class InputManager
{
	static InputManager* mInstance;

	 //int mKeyCount = 256;
	bool mKeys[mKeyCount];

	InputManager();
public:
	static InputManager& GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new InputManager();

		return *mInstance;
	}
	~InputManager();

	const bool* GetKeys() { return mKeys; }
	const bool GetKey(int key) { return mKeys[key]; }
	void SetKeyState(int key, bool down) { mKeys[key] = down; }
};