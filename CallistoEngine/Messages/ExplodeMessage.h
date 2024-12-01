#pragma once
#include "../Components/Message.h"

class Entity;


class ExplodeMessage : public Message
{
protected:
	Entity* mCollider;
	Entity* mCollidee;

public:
	ExplodeMessage();
	virtual ~ExplodeMessage();

	Entity* GetCollider() const { return mCollider; }
	Entity* GetCollidee() const { return mCollidee; }
	Entity* GetOtherCollisionObject(Entity* obj)	const { return mCollider == obj ? mCollidee : mCollider; }

};

