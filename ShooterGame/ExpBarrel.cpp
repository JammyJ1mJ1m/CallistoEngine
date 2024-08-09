#include "ExpBarrel.h"
#include "ShooterGame.h"
#include "Components/ComponentRigidBody.h"
#include "Components/ComponentCollider.h"


void ExpBarrel::start()
{
    //AddComponent(new ComponentModel(Game::GetGame()->GetMesh("barrel"), "Resources/Geometry/Barrel/expBarrel.mtl"));
    AddComponent(new ComponentModel(Game::GetGame()->GetMesh("barrel"), "Resources/Geometry/Barrel/expBarrel.mtl"));
	AddComponent(new ComponentShaderScanLines(ShooterGame::GetGameCamera(), "Resources/Shaders/ScanLines.vert", "Resources/Shaders/ScanLines.frag"));

	glm::vec3 pos = glm::vec3(-10.0f, 40.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1)));
	//mEntities.push_back(tri);

	// create mesh colider shape
	std::vector<Vertex> vertices = Game::GetGame()->GetMesh("barrel")->GetVertices();
	std::vector<int> indices = Game::GetGame()->GetMesh("barrel")->GetIndices();

	ComponentCollider* collider = new ComponentCollider(2, 2.75);
	//ComponentCollider* collider = new ComponentCollider(2/*,2.75*/);
	

	AddComponent(collider);

	int mass = 1;
	ComponentRigidBody* rb = new ComponentRigidBody(collider, mass, pos);
	AddComponent(rb);
}

void ExpBarrel::SetPosition()
{
}

ExpBarrel::ExpBarrel()
{
	start();
}

void ExpBarrel::SetPosition(glm::vec3 pPos)
{
	GetComponent<ComponentTransform>()->SetPosition(pPos);
	GetComponent<ComponentRigidBody>()->SetPosition(pPos);
}

void ExpBarrel::applyExplosionForce(btDiscreteDynamicsWorld& world, const btVector3& explosionOrigin, btScalar explosionStrength, btScalar explosionRadius)
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

