#pragma once
#include "Scenes/Scene.h"
#include "Systems/SystemLight.h"
#include "GUI/GUIText.h"
#include "GUI/GUIContainer.h"
#include "GUI/GUIImage.h"

class MainMenuScene final : public Scene
{
	GUIText* text1;
	GUIText* text2;

	GUIContainer* container1;

	GUIImage* image1;

public:
	MainMenuScene();
	virtual ~MainMenuScene();
	virtual void Initialise();
	virtual void OnKeyboard(int key, bool down);
	virtual void Update(double deltaTime);
	virtual void Render(SystemRender* renderer);
};