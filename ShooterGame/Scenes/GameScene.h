#pragma once
#include "Scenes/Scene.h"
#include "Systems/SystemLight.h"
#include "GUI/GUIText.h"

class GameScene final : public Scene
{
	bool isExploded;
	SystemLight* mLightSystem;
	GUIText* text1;

	public:
	GameScene();
	virtual ~GameScene();
	virtual void Initialise();
	virtual void OnKeyboard(int key, bool down);
	virtual void Update(double deltaTime);
	virtual void Render(SystemRender* renderer);
};