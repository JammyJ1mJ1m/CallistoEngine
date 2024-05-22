#include "GameScene.h"
#include "Components/Entity.h"
#include "Components/ComponentModel.h"
#include "Components/ComponentShader.h"
#include "Components/ComponentTransform.h"
#include "Vector.h"

#include "Material.h"

#include "Systems/SystemRender.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialise()
{

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
}