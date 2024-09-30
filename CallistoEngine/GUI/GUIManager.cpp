#include "GUIManager.h"
#include "../Game.h"

GUIManager* GUIManager::mInstance = nullptr;

void GUIManager::Resize(const int pWidth, const int pHeight)
{
	mUIPRojection = glm::ortho(0.0f, static_cast<float>(pWidth), 0.0f, static_cast<float>(pHeight));

	for (auto& element : mGUIElements)
		element->Resize(pWidth, pHeight);
}

void GUIManager::Render()
{
	// loop through and render all the GUI elements
}
