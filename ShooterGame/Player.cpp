#include "Player.h"
#include "ShooterGame.h"
#include "Components/ComponentRigidBody.h"

void Player::start()
{
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("ship"), "Resources/textures/TCube.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(),"Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));

	glm::vec3 pos = glm::vec3(0.0f, -5.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f)));
	//mEntities.push_back(tri);



	btVector3 halfExtents(4.0, 0.2, 4.0); // This will create a box of size 2x2x2
	btCollisionShape* boxShape = new btBoxShape(halfExtents);

	// empty btTransform

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z)); // Starting at position (2.0f, 0.0f, 0.0f)

	ComponentRigidBody* rb = new ComponentRigidBody(boxShape, 0.0f, btVector3(0, 0, 0), transform);
	AddComponent(rb);
}

Player::Player()
{

	start();
}
