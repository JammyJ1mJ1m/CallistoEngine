#include "IComponent.h"
#include "../Game.h"

IComponent::~IComponent() = default;

void IComponent::BroadcastMessage(Message* msg)
{
	Game::GetGame()->BroadcastMessage(msg);
}