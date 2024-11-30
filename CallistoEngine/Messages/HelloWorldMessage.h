#pragma once
#include "../Components/Message.h"

class Entity;


class HelloWorldMessage : public Message
{
protected:
	Entity* mCollider;
	Entity* mCollidee;

public:
	HelloWorldMessage(Entity* collider, Entity* collidee);
	virtual ~HelloWorldMessage();

	Entity* GetCollider() const { return mCollider; }
	Entity* GetCollidee() const { return mCollidee; }
	Entity* GetOtherCollisionObject(Entity* obj)	const { return mCollider == obj ? mCollidee : mCollider; }

};

