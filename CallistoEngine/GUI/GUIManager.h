#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GUIElement.h"

class GUIManager
{
	std::vector<GUIElement*> mGUIElements;
	glm::mat4 mUIPRojection;

	static GUIManager* mInstance;
	GUIManager() {};
public:

	static GUIManager& GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new GUIManager();

		return *mInstance;
	}

	const glm::mat4 GetUIProjection() { return mUIPRojection; }

	void AddElement(GUIElement* pElement) { mGUIElements.push_back(pElement); }

	void Resize(const int pWidth, const int pHeight);
	void Render();

	~GUIManager() = default;
};

