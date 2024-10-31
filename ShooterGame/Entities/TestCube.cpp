#include "TestCube.h"
#include "ShooterGame.h"
#include "Components/ComponentRigidBody.h"
#include "Components/ComponentCollider.h"

void TestCube::start()
{
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("AKmagazine"), "Resources/textures/GunAK.mtl"));
	AddComponent(new ComponentShaderDefault(this,ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));

	Vector3f pos(15.0f, 0.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 3, 1)));
}



TestCube::TestCube()
{
	start();
}

void TestCube::SetPosition(const Vector3f& pPosition)
{
	GetComponent<ComponentTransform>()->SetPosition(pPosition);

}

void TestCube::SetRotation(glm::vec3 pRot)
{
	GetComponent<ComponentTransform>()->SetRotation(pRot);
}

void TestCube::Rotate(float pAmount, float dt)
{
	glm::vec3 rot = GetComponent<ComponentTransform>()->GetRotation();
	rot.y += pAmount * dt;

	GetComponent<ComponentTransform>()->SetRotation(rot);
}


void TestCube::MoveForward()
{
   
}

void TestCube::MoveBackward()
{
    
}

void TestCube::MoveLeft()
{
	

}

void TestCube::MoveRight()
{
	

}

