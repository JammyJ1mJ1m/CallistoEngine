#include "Entity.h"
#include "ComponentRigidBody.h"

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

const void Entity::UpdateChildPositions()
{
    ComponentTransform* parentTransform = GetComponent<ComponentTransform>();
    if (!parentTransform) return;

    Vector3f parentPosition = parentTransform->GetPosition();

    // Loop through each child entity and update its position
    for (Entity* child : mChildren)
    {
        ComponentTransform* childTransform = child->GetComponent<ComponentTransform>();
        if (childTransform)
        {

            // update / pass over the model matrix here
            childTransform->UpdateModelMatrix(parentTransform->GetModelMatrix());

            std::cout << childTransform->GetPosition() << std::endl;

            // keep this as it will update all the other children
            child->UpdateChildPositions();
            std::cout << childTransform->GetPosition() << std::endl;

            ComponentRigidBody* rb = child->GetComponent<ComponentRigidBody>();
            if(rb)
            {
				rb->SetPosition(childTransform->GetPosition());
			}

        }
    }
}

const void Entity::AddChild(Entity* pChild, const Vector3f& pPos)
{
    ComponentTransform* transform = GetComponent<ComponentTransform>();

    pChild->SetPosition(pPos);
    pChild->GetComponent<ComponentTransform>()->UpdateModelMatrix(GetComponent<ComponentTransform>()->GetModelMatrix());
    mChildren.push_back(pChild);
}