#include "Entity.h"
#include "ComponentRigidBody.h"

#include "Message.h"

Entity::Entity()
{
    mIsExpired = false;
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

void Entity::OnMessage(Message* msg)
{
    // Dispatch message to all registered listeners
    MessageListenerMapIterator i = _messageListeners.find(msg->GetMessageType());

    // If we have registered listeners for this message
    if (i != _messageListeners.end())
    {
        std::vector<IComponent*>& list = i->second;

        for(auto& comp : mComponentList)
        //for (ComponentListIterator j = list.begin();
        //    j != list.end();
        //    ++j)
        {
            // Send listener the message
            comp->OnMessage(msg);
        }
    }
}

void Entity::RegisterListener(std::string msg, IComponent* goc)
{
    MessageListenerMapIterator i = _messageListeners.find(msg);

    // Make entry and add listener
    if (i == _messageListeners.end())
    {
        _messageListeners[msg] = std::vector<IComponent*>();
        _messageListeners[msg].push_back(goc);
    }
    else
    {
        // Already have list; just add
        _messageListeners[msg].push_back(goc);
    }
}


void Entity::UnregisterListener(std::string msg, IComponent* goc)
{
    MessageListenerMapIterator i = _messageListeners.find(msg);

    // Exists?
    if (i != _messageListeners.end())
    {
        std::vector<IComponent*>& list = i->second;

        for (auto& comp : mComponentList)

        for (ComponentListIterator j = list.begin(); j != list.end(); ++j)
        {
            if (comp == goc)
            {
                // Found it - so remove the listener
                list.erase(j);
                break;
            }
        }
    }
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