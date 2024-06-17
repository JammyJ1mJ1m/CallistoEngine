#include "Enemy.h"
#include "Components/ComponentRigidBody.h"
//#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
//#include "Bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"	
#include "Components/ComponentCollider.h"



void Enemy::start()
{
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("cube"), "Resources//Geometry/test/AwesomeAxolotls_1.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));
	glm::vec3 pos = glm::vec3(-8.0f, 15.0f, -15.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f)));

	ComponentCollider* collider = new ComponentCollider(btVector3(1, 1, 1));
	//ComponentCollider* collider = new ComponentCollider(1);

	AddComponent(collider);

	btScalar mass = 1.0;
	ComponentRigidBody* rb = new ComponentRigidBody(collider, mass, pos);
	AddComponent(rb);
}

void Enemy::SetPosition()
{
}

void Enemy::SetPosition(glm::vec3 pPos)
{
	GetComponent<ComponentTransform>()->SetPosition(pPos);
	GetComponent<ComponentRigidBody>()->SetPosition(pPos);
}

Enemy::Enemy()
{
	start();
}
