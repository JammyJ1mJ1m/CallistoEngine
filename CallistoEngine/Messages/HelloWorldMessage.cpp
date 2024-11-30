#include "HelloWorldMessage.h"

HelloWorldMessage::HelloWorldMessage(Entity* collider, Entity* collidee)
	: Message("HelloWorldMessage"),
	mCollider(collider),
	mCollidee(collidee)
{

}

HelloWorldMessage::~HelloWorldMessage()
{ }