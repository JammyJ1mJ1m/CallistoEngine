#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (size_t i = 0; i < _gameObjects.size(); i++)
	{
		delete _gameObjects[i];
	}
	_gameObjects.clear();
}

void Scene::Update(double deltaTime)
{

}