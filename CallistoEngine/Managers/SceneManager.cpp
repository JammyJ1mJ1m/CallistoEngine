#include "SceneManager.h"
#include "../Scenes/Scene.h"

/******************************************************************************************************************/
// Structors
/******************************************************************************************************************/

SceneManager::SceneManager(Game* game)
	: _game(game)
{
}

/******************************************************************************************************************/

SceneManager::~SceneManager()
{
}


/******************************************************************************************************************/

void SceneManager::OnKeyboard(int key, bool down)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene)
	{
		currentScene->OnKeyboard(key, down);
	}
}

void SceneManager::Update(double deltaTime)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene)
	{
		currentScene->Update(deltaTime);
	}
}

/// Render current scene
void SceneManager::Render(SystemRenderDeferred* renderer)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene)
	{
		currentScene->Render(renderer);
	}
}

void SceneManager::PushScene(Scene* s)
{
	_scenes.push(s);
	s->SetSceneManager(this);
	s->Initialise();
}
