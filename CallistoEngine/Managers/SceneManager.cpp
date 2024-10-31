#include "SceneManager.h"
#include "../Scenes/Scene.h"

/******************************************************************************************************************/
// Structors
/******************************************************************************************************************/

SceneManager::SceneManager(Game* pGame)
	: mGame(pGame)
{
}

/******************************************************************************************************************/

SceneManager::~SceneManager()
{
}


/******************************************************************************************************************/

void SceneManager::OnKeyboard(int pKey, bool pIsDown)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene)
	{
		currentScene->OnKeyboard(pKey, pIsDown);
	}
}

void SceneManager::Update(double pDeltaTime)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene)
	{
		currentScene->Update(pDeltaTime);
	}
}

/// Render current scene
void SceneManager::Render(SystemRender* pRenderer)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene)
	{
		currentScene->Render(pRenderer);
	}
}

void SceneManager::PushScene(Scene* pScene)
{
	mScenes.push(pScene);
	pScene->SetSceneManager(this);
	pScene->Initialise();
}
