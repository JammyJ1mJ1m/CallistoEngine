#include "GameScene.h"
#include "Components/Entity.h"
#include "Components/ComponentModel.h"
#include "Components/ComponentShader.h"
#include "Components/ComponentTransform.h"
#include "Components/ComponentRigidBody.h"

#include "Vector.h"

#include "Material.h"

#include "Systems/SystemRender.h"

#include "Player.h"
#include "Enemy.h"
#include "SkyBox.h"

#include "Managers/PhysicsManager.h"
Enemy* enemy;
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


	/*Player* player = new Player();
	AddEntity(player);*/

	enemy = new Enemy();
	AddEntity(enemy);

	/*SkyBox* skybox = new SkyBox();
	AddEntity(skybox);*/
}

void GameScene::OnKeyboard(int key, bool down)
{
}

void GameScene::Update(double deltaTime)
{
	PhysicsManager::GetInstance().Update(deltaTime);

	btTransform pos;
	enemy->GetComponent<ComponentRigidBody>()->GetMotionState()->getWorldTransform(pos);
	std::cout << pos.getOrigin().x() << " " << pos.getOrigin().y() << " " << pos.getOrigin().z() << std::endl;
	enemy->GetComponent<ComponentRigidBody>()->SyncWithTransform(enemy->GetComponent<ComponentTransform>());

}

void GameScene::Render(SystemRender* renderer)
{
	for (auto& enti : mEntities)
	//{
	 renderer->Run(enti);
	//}
}