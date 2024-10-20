#pragma once
#include "Scenes/Scene.h"
#include "Systems/SystemLight.h"
#include "GUI/GUIText.h"
#include "GUI/GUIContainer.h"
#include "GUI/GUIImage.h"

class GameScene final : public Scene
{
	bool isExploded;
	SystemLight* mLightSystem;


	GUIText* text1;
	GUIText* text2;

	GUIContainer* container1;

	GUIImage* image1;

	float mElapsed;
	float mTimeToSpawn;

	public:
	GameScene();
	virtual ~GameScene();
	virtual void Initialise();
	virtual void OnKeyboard(int key, bool down);
	virtual void Update(double deltaTime);
	virtual void Render(SystemRenderDeferred* renderer);
};