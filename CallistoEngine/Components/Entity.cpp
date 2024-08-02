#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(const Entity& other)
{
	create(other);
}

void Entity::AddComponent(IComponent* pComponent)
{
	mComponentList.push_back(pComponent);
	UpdateMask(pComponent->GetType());
}
