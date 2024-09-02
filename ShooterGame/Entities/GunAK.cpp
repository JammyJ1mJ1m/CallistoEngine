#include "GunAK.h"
#include "ShooterGame.h"
#include "Components/ComponentRigidBody.h"
#include "Components/ComponentCollider.h"
#include "TestCube.h"

void GunAK::start()
{
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("AK"), "Resources/textures/GunAK.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));

	glm::vec3 pos = glm::vec3(-15.0f, 3.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1)));
	//mEntities.push_back(tri);

	// create mesh colider shape
	std::vector<Vertex> vertices = Game::GetGame()->GetMesh("AK")->GetVertices();
	std::vector<int> indices = Game::GetGame()->GetMesh("AK")->GetIndices();

	Vector3f newPos;
	newPos.SetX(pos.x);
	newPos.SetY(pos.y);
	newPos.SetZ(pos.z);

	ComponentCollider* collider = new ComponentCollider(vertices);
	int mass = 0;
	ComponentRigidBody* rb = new ComponentRigidBody(collider, mass, pos);
	AddComponent(rb);

	TestCube* cub = new TestCube();
	//glm::vec3 newpos = pos + glm::vec3(0.0f, 0.0f, 0.0f);
	//cub->SetPosition(glm::vec3(newpos));
	AddChild(new TestCube(), Vector3f(0.0f, 0.0f, 0.0f));


}

void GunAK::SetPosition(const Vector3f& pPosition)
{
	GetComponent<ComponentTransform>()->SetPosition(pPosition);
	GetComponent<ComponentRigidBody>()->SetPosition(pPosition);
}

GunAK::GunAK()
{
	start();
}

/*oid GunAK::SetPosition(glm::vec3 pPos)
{
	GetComponent<ComponentTransform>()->SetPosition(pPos);
	GetComponent<ComponentRigidBody>()->SetPosition(pPos);
}*/

void GunAK::SetRotation(glm::vec3 pRot)
{
	GetComponent<ComponentTransform>()->SetRotation(pRot);
}

void GunAK::Rotate(float pAmount, float dt)
{
	glm::vec3 rot = GetComponent<ComponentTransform>()->GetRotation();
	rot.y += pAmount * dt;

	GetComponent<ComponentTransform>()->SetRotation(rot);
}


void GunAK::MoveForward()
{
}

void GunAK::MoveBackward()
{
}

void GunAK::MoveLeft()
{
}

void GunAK::MoveRight()
{
}