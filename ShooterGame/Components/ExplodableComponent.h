#pragma once
#include "Components\IComponent.h"
class ExplodableComponent : public IComponent
{
public:
	ExplodableComponent(Entity* pParent);
	~ExplodableComponent() = default;
	//~ExplodableComponent() = default;
	virtual ComponentTypes GetType() const;
	virtual void OnMessage(Message* msg);


};

