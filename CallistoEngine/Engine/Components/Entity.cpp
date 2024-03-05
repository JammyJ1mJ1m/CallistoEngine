#include "Entity.h"

Entity::Entity(const Entity& A)
{
	create(A);
}

void Entity::AddComponent(std::shared_ptr <IComponent> pComponent)
{
	mComponentList.push_back(pComponent);
	UpdateMask(pComponent->GetType());
}