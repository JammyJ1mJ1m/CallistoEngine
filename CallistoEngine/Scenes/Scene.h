#pragma once
#include <vector>
#include "../Components/Entity.h"

class SystemRender;
class SceneManager;

/// Represents an abstract scene, i.e. mode of the game
/// For example, MainMenu, Gameplay, GameOver etc
class Scene
{
protected:
	SceneManager* _sceneManager;
	std::vector<Entity*>		mEntities;		// The list of game objects

public:
	Scene();
	virtual ~Scene();

	std::vector<Entity*>& GetEntities() { return mEntities; }
	void AddEntity(Entity* obj) { mEntities.push_back(obj); }

	int GetEntityCount() const { return mEntities.size(); }

	void SetSceneManager(SceneManager* s) { _sceneManager = s; }
	SceneManager* GetSceneManager()	const { return _sceneManager; }

	virtual void Initialise() = 0;

	virtual void OnKeyboard(int key, bool down) = 0;

	virtual void Update(double deltaTime) = 0;

	virtual void Render(SystemRender* renderer) = 0;
};