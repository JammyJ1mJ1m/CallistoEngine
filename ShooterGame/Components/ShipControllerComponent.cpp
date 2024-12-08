#include "ShipControllerComponent.h"
#include "Components/Entity.h"
#include "Messages/ExplodeMessage.h"

#include "Components/ComponentRigidBody.h"
#include "Managers/PhysicsManager.h"

ShipControllerComponent::ShipControllerComponent(Entity* pParent)
{
    SetParent(pParent);

	pParent->RegisterListener("rotateR", this);
	pParent->RegisterListener("rotateL", this);
	mRotationSpeed = 2;
}

ShipControllerComponent::~ShipControllerComponent()
{
	mParent->UnregisterListener("rotateR", this);
	mParent->UnregisterListener("rotateL", this);
}

IComponent::ComponentTypes ShipControllerComponent::GetType() const
{
    return ComponentTypes::COMPONENT_TEST;
}

void ShipControllerComponent::OnMessage(Message* msg)
{
	if (msg->GetMessageType() == "rotateR")
	{
		ComponentRigidBody* rb = mParent->GetComponent<ComponentRigidBody>();
		rb->ApplyTorque(Vector3f(0.0f, mRotationSpeed, 0.0f));
	}
	if (msg->GetMessageType() == "rotateL")
	{
		ComponentRigidBody* rb = mParent->GetComponent<ComponentRigidBody>();
		rb->ApplyTorque(Vector3f(0.0f, -mRotationSpeed, 0.0f));
	}
}
