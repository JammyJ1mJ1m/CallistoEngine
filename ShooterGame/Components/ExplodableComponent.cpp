#include "ExplodableComponent.h"
#include "Components/Entity.h"
#include "Messages/HelloWorldMessage.h"

ExplodableComponent::ExplodableComponent(Entity* pParent)
{
	SetParent(pParent);

	pParent->RegisterListener("HelloWorldMessage", this);
}

IComponent::ComponentTypes ExplodableComponent::GetType() const
{
	return ComponentTypes::COMPONENT_TEST;
}

void ExplodableComponent::OnMessage(Message* msg)
{
	if (msg->GetMessageType() == "HelloWorldMessage")
	{
		std::cout << "Hello world message from a component" << std::endl;
	}
}
