#include "ExplodableComponent.h"
#include "Components/Entity.h"
#include "Messages/ExplodeMessage.h"

#include "Components/ComponentTransform.h"

#include "Managers/PhysicsManager.h"

ExplodableComponent::ExplodableComponent(Entity* pParent)
{
	SetParent(pParent);

	pParent->RegisterListener("explode", this);
}

ExplodableComponent::~ExplodableComponent()
{
	mParent->UnregisterListener("explode", this);
}

IComponent::ComponentTypes ExplodableComponent::GetType() const
{
	return ComponentTypes::COMPONENT_TEST;
}

void ExplodableComponent::OnMessage(Message* msg)
{
	if (msg->GetMessageType() == "explode")
	{
		std::cout << "Big Boom" << std::endl;


		// applyExplosionForce(PhysicsManager::GetInstance().GetWorld(), btVector3(0, 0, 0), 1000, 100);
		btDiscreteDynamicsWorld& world = PhysicsManager::GetInstance().GetDynamicsWorld();
		auto origin = btVector3(mParent->GetComponent<ComponentTransform>()->GetPosition().x, mParent->GetComponent<ComponentTransform>()->GetPosition().y, mParent->GetComponent<ComponentTransform>()->GetPosition().z);
		auto strength = 100;
		auto radius = 50;
		applyExplosionForce(world, origin, strength, radius);
		//sound->Play3D(origin.x(), origin.y(), origin.z());
		//Game::GetGame()->GetAudioManager()->Play3DSound("Resources/Sounds/explosion.wav",origin.x(),origin.y(),origin.z(), false);

		// remove expBarrel from mEntities
        // set remove flag on the parent
        mParent->SetExpired();
		//mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), mParent), mEntities.end());


	}
}



void ExplodableComponent::applyExplosionForce(btDiscreteDynamicsWorld& world, const btVector3& explosionOrigin, btScalar explosionStrength, btScalar explosionRadius)
{
    // Iterate over all the collision objects in the world
    for (int i = 0; i < world.getNumCollisionObjects(); i++) {
        btCollisionObject* obj = world.getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);

        if (body && body->getInvMass() != 0) { // Only affect dynamic objects
            // Check if the body is at rest and wake it up
            if (body->getActivationState() == ISLAND_SLEEPING) {
                body->activate(true);
            }

            btVector3 bodyPos = body->getWorldTransform().getOrigin();
            btVector3 toBody = bodyPos - explosionOrigin;

            btScalar distance = toBody.length();
            if (distance < explosionRadius) {
                // Normalize the direction and calculate the force magnitude based on distance
                btVector3 forceDir = toBody.normalized();
                btScalar forceMagnitude = explosionStrength * (1 - distance / explosionRadius);
                btVector3 force = forceDir * forceMagnitude;

                body->applyCentralImpulse(force);
            }
        }
    }
}