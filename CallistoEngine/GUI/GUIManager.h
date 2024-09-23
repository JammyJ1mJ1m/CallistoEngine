#pragma once
#include <vector>

class GUIManager
{
	static GUIManager* mInstance;
	GUIManager();
public:

	static GUIManager& GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new GUIManager();

		return *mInstance;
	}

	~GUIManager() = default;

	void Render();
};

