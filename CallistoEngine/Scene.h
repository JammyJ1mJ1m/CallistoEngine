#pragma once
#include <vector>

class GameObject;
class SystemRender;
class SceneManager;

/// Represents an abstract scene, i.e. mode of the game
/// For example, MainMenu, Gameplay, GameOver etc
class Scene
{
protected:
	SceneManager* _sceneManager;
	std::vector<GameObject*>		_gameObjects;		// The list of game objects

public:
	Scene();
	virtual ~Scene();

	std::vector<GameObject*>& GetGameObjects() { return _gameObjects; }
	void AddGameObject(GameObject* obj) { _gameObjects.push_back(obj); }

	void SetSceneManager(SceneManager* s) { _sceneManager = s; }
	SceneManager* GetSceneManager()	const { return _sceneManager; }

	virtual void Initialise() = 0;

	virtual void OnKeyboard(int key, bool down) = 0;

	virtual void Update(double deltaTime);

	virtual void Render(SystemRender* renderer) = 0;
};