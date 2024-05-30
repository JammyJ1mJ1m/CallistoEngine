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

/// <summary>
/// All game objects are created here and members are initialised
/// </summary>
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
	for (auto& enti : mEntities)
	//{
	 renderer->Run(enti);
	//}
}