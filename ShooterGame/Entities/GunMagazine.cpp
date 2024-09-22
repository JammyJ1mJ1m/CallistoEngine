#include "GunMagazine.h"
#include "ShooterGame.h"
#include "Components/ComponentRigidBody.h"
#include "Components/ComponentCollider.h"

void GunMagazine::start()
{
	//AddComponent(new ComponentModel(Game::GetGame()->GetMesh("AKmagazine"), "Resources/textures/GunAK.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));

	Vector3f pos(0.0f, 0.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1)));
}



GunMagazine::GunMagazine()
{
	// start();
}

void GunMagazine::Initialise(const char* pModelName, const char* pModelMat)
{
	start();
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh(pModelName), pModelMat));

}

void GunMagazine::SetPosition(const Vector3f& pPosition)
{
	GetComponent<ComponentTransform>()->SetPosition(pPosition);

}

void GunMagazine::SetRotation(glm::vec3 pRot)
{
	GetComponent<ComponentTransform>()->SetRotation(pRot);
}

void GunMagazine::Rotate(float pAmount, float dt)
{
	glm::vec3 rot = GetComponent<ComponentTransform>()->GetRotation();
	rot.y += pAmount * dt;

	GetComponent<ComponentTransform>()->SetRotation(rot);
}


void GunMagazine::MoveForward()
{

}

void GunMagazine::MoveBackward()
{

}

void GunMagazine::MoveLeft()
{


}

void GunMagazine::MoveRight()
{
	

}

