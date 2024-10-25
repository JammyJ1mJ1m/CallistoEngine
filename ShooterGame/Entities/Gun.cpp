#include "Gun.h"
#include "ShooterGame.h"
#include "Components/ComponentRigidBody.h"
#include "Components/ComponentCollider.h"
#include "TestCube.h"
#include "Components/ComponentTransform.h"
#include "Math/Vector.h"
#include "GunMagazine.h"

void Gun::start()
{
	//AddComponent(new ComponentModel(Game::GetGame()->GetMesh("AK"), "Resources/textures/GunAK.mtl"));
	//AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));

	//Vector3f pos = Vector3f(0.0f, 3.0f, 0.0f);
	//AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1)));
	////mEntities.push_back(tri);

	//// create mesh colider shape
	//std::vector<Vertex> vertices = Game::GetGame()->GetMesh("AK")->GetVertices();
	//std::vector<int> indices = Game::GetGame()->GetMesh("AK")->GetIndices();

	////Vector3f newPos;
	////newPos.SetX(pos.x);
	////newPos.SetY(pos.y);
	////newPos.SetZ(pos.z);

	////ComponentCollider* collider = new ComponentCollider(vertices);
	//// AddComponent(collider);
	////	int mass = 1;
	////	ComponentRigidBody* rb = new ComponentRigidBody(collider, mass, pos);
	////	AddComponent(rb);


	////glm::vec3 newpos = pos + glm::vec3(0.0f, 0.0f, 0.0f);
	////cub->SetPosition(glm::vec3(newpos));
	//AddChild(new TestCube(), Vector3f(0.0f, 0.0f, 0.0f));


}

Gun::Gun()
{
	// start();
}

void Gun::Initialise(GunInformation* pGuninfo)
{
	start();
	Vector3f pos = pGuninfo->getPosition();
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1)));

	AddComponent(new ComponentModel(Game::GetGame()->GetMesh(pGuninfo->getGunName()), pGuninfo->getModelMat()));

	if (pGuninfo->GetHasChild())
	{
		GunMagazine* gunMag = new GunMagazine();
		gunMag->Initialise(pGuninfo->getChildName().c_str(), pGuninfo->getModelMat().c_str());
		AddChild(gunMag, Vector3f(0.0f, 0.0f, 0.0f));
	}

}

void Gun::SetPosition(const Vector3f& pPosition)
{
	//GetComponent<ComponentTransform>()->SetPosition(pPosition);

	ComponentTransform* transform = GetComponent<ComponentTransform>();
	if (transform)
	{
		transform->SetPosition(pPosition);
		UpdateChildPositions();  // Update all children when the parent's position changes
	}

	ComponentRigidBody* rb = GetComponent<ComponentRigidBody>();
	if (rb)
	{
		GetComponent<ComponentRigidBody>()->SetPosition(pPosition);
	}
	//UpdateChildPositions();
}


/*oid Gun::SetPosition(glm::vec3 pPos)
{
	GetComponent<ComponentTransform>()->SetPosition(pPos);
	GetComponent<ComponentRigidBody>()->SetPosition(pPos);
}*/

void Gun::SetRotation(glm::vec3 pRot)
{
	GetComponent<ComponentTransform>()->SetRotation(pRot);
}

void Gun::Rotate(float pAmount, float dt)
{
	glm::vec3 rot = GetComponent<ComponentTransform>()->GetRotation();
	rot.y += pAmount * dt;

	GetComponent<ComponentTransform>()->SetRotation(rot);
}

void Gun::MoveForward() {
	// Example movement logic: Adjust the position forward
	ComponentTransform* transform = GetComponent<ComponentTransform>();
	if (transform) {
		glm::vec3 pos = glm::vec3(transform->GetPosition().GetX(), transform->GetPosition().GetY(), transform->GetPosition().GetZ());
		pos.z += 32.0f * Game::GetDeltaTime();  // Move forward along the Z-axis
		SetPosition(Vector3f(pos.x, pos.y, pos.z));
	}
	/*ComponentRigidBody* rb = GetComponent<ComponentRigidBody>();
	if (rb)
	{
		glm::vec3 pos = glm::vec3(transform->GetPosition().GetX(), transform->GetPosition().GetY(), transform->GetPosition().GetZ());

		rb->SetPosition(Vector3f(pos.x, pos.y, pos.z));
	}*/

}

void Gun::MoveBackward() {
	ComponentTransform* transform = GetComponent<ComponentTransform>();
	if (transform) {
		glm::vec3 pos = glm::vec3(transform->GetPosition().GetX(), transform->GetPosition().GetY(), transform->GetPosition().GetZ());
		pos.z -= 32.0f * Game::GetDeltaTime();  // Move backward along the Z-axis
		SetPosition(Vector3f(pos.x, pos.y, pos.z));
	}
}

void Gun::MoveLeft() {
	ComponentTransform* transform = GetComponent<ComponentTransform>();
	if (transform) {
		glm::vec3 pos = glm::vec3(transform->GetPosition().GetX(), transform->GetPosition().GetY(), transform->GetPosition().GetZ());
		pos.x -= 32.0f * Game::GetDeltaTime();  // Move left along the X-axis
		SetPosition(Vector3f(pos.x, pos.y, pos.z));
	}
}

void Gun::MoveRight() {
	ComponentTransform* transform = GetComponent<ComponentTransform>();
	if (transform) {
		glm::vec3 pos = glm::vec3(transform->GetPosition().GetX(), transform->GetPosition().GetY(), transform->GetPosition().GetZ());
		pos.x += 32.0f * Game::GetDeltaTime();  // Move right along the X-axis
		SetPosition(Vector3f(pos.x, pos.y, pos.z));
	}
}
