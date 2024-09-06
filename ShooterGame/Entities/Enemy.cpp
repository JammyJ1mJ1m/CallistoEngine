#include "Enemy.h"
#include "Components/ComponentRigidBody.h"
//#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
//#include "Bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"	
#include "Components/ComponentCollider.h"



void Enemy::start()
{
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("cube"), "Resources/textures/CardBox.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));
	glm::vec3 pos = glm::vec3(0.0f, 5.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f)));

	Vector3f newPos;
	newPos.SetX(pos.x);
	newPos.SetY(pos.y);
	newPos.SetZ(pos.z);
	ComponentCollider* collider = new ComponentCollider(Game::GetGame()->GetMesh("cube")->GetVertices());

	//pos[0] = collider->GetCenter().GetX();
	//pos[1] = collider->GetCenter().GetY();
	//pos[2] = collider->GetCenter().GetZ();


	//ComponentCollider* collider = new ComponentCollider(btVector3(0.177980006, 0.989475012, 4.58138275));
	//ComponentCollider* collider = new ComponentCollider(1);

	AddComponent(collider);

	btScalar mass = 1.0;
	//glm::vec3 posi = glm::vec3(GetComponent<ComponentCollider>()->GetCenter().GetX(), GetComponent<ComponentCollider>()->GetCenter().GetY(), GetComponent<ComponentCollider>()->GetCenter().GetZ());

	ComponentRigidBody* rb = new ComponentRigidBody(collider, mass, pos);
	AddComponent(rb);
}

void Enemy::SetPosition(const Vector3f& pPosition)
{
	GetComponent<ComponentTransform>()->SetPosition(pPosition);
	GetComponent<ComponentRigidBody>()->SetPosition(pPosition);
}

void Enemy::MoveForward()
{
}

void Enemy::MoveBackward()
{
}

void Enemy::MoveLeft()
{
}

void Enemy::MoveRight()
{
}

Enemy::Enemy()
{
	start();
}
