#pragma once
#include "Components\IComponent.h"
#include <Bullet/btBulletCollisionCommon.h>
#include "Bullet/btBulletDynamicsCommon.h"

class ShipControllerComponent : public IComponent
{
	float mRotationSpeed;
public:
	ShipControllerComponent(Entity* pParent);
	~ShipControllerComponent();

	virtual ComponentTypes GetType() const;
	virtual void OnMessage(Message* msg);
};

