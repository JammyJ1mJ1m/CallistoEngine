#include "Enemy.h"
#include "Components/ComponentRigidBody.h"
//#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
//#include "Bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"	
#include "Components/ComponentCollider.h"
#include "Math/Vector.h"
#include "Misc/Sound.h"
#include "Components/ComponentShaderWindow.h"



void Enemy::start()
{
	
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("cube"), "Resources/textures/CardBox.mtl"));
	//AddComponent(new ComponentShaderWindow(ShooterGame::GetGameCamera(), "Resources/Shaders/window.vert", "Resources/Shaders/window.frag"));
	Vector3f pos(-10.0f, 40.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));


	ComponentCollider* collider = new ComponentCollider(2	 );
	AddComponent(collider);

	btScalar mass = 1.0;
	ComponentRigidBody* rb = new ComponentRigidBody(collider, mass, pos);
	AddComponent(rb);

	Sound* sound = new Sound("Resources/Sounds/Pop.wav");

	 sound->Play3D(pos.GetX(),pos.GetY(),pos.GetZ());

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
