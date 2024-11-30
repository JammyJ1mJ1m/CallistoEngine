#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (size_t i = 0; i < mEntities.size(); i++)
	{
		delete mEntities[i];
	}
	mEntities.clear();
}

void Scene::OnMessage(Message* msg)
{
	for (int i = 0; i < (int)mEntities.size(); i++)
	{
		// check if the entity is a valid target
			mEntities[i]->OnMessage(msg);
		
	}
}