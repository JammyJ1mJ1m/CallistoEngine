#pragma once
#include "Scenes/Scene.h"

class GameScene final : public Scene
{
	bool isExploded;
	public:
	GameScene();
	virtual ~GameScene();
	virtual void Initialise();
	virtual void OnKeyboard(int key, bool down);
	virtual void Update(double deltaTime);
	virtual void Render(SystemRender* renderer);
};