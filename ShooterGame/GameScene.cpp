#include "GameScene.h"
#include "Components/Entity.h"
#include "Components/ComponentModel.h"
#include "Components/ComponentShader.h"
#include "Components/ComponentTransform.h"
#include "Vector.h"

#include "Material.h"

#include "Systems/SystemRender.h"

#include "Player.h"
#include "Enemy.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialise()
{
	Player* player = new Player();
	AddEntity(player);

	Enemy* enemy = new Enemy();
	AddEntity(enemy);

}

void GameScene::OnKeyboard(int key, bool down)
{
}

void GameScene::Update(double deltaTime)
{

}

void GameScene::Render(SystemRender* renderer)
{
	// TODO - renderer->Run(/* GameObjects */);
	for (auto& enti : mEntities)
	{
		renderer->Run(enti/* GameObjects */);
		//enti->Render(renderer);
	}
}