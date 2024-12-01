#pragma once
#include "Components\IComponent.h"
#include <Bullet/btBulletCollisionCommon.h>
#include "Bullet/btBulletDynamicsCommon.h"

class ExplodableComponent : public IComponent
{
public:
	ExplodableComponent(Entity* pParent);
	~ExplodableComponent();
	//~ExplodableComponent() = default;
	virtual ComponentTypes GetType() const;
	virtual void OnMessage(Message* msg);

	void applyExplosionForce(btDiscreteDynamicsWorld& world, const btVector3& explosionOrigin, btScalar explosionStrength, btScalar explosionRadius);


};

