#pragma once
#include "Scenes/Scene.h"
#include "Systems/SystemLight.h"
#include "GUI/GUIText.h"

class MainMenuScene final : public Scene
{
	GUIText* text1;

public:
	MainMenuScene();
	virtual ~MainMenuScene();
	virtual void Initialise();
	virtual void OnKeyboard(int key, bool down);
	virtual void Update(double deltaTime);
	virtual void Render(SystemRender* renderer);
};