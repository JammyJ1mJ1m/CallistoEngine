#include "TestLight.h"
#include "game.h"
#include "Components/ComponentRigidBody.h"
#include "Components/ComponentCollider.h"
#include "Components/LightComponent.h"
#include "lighting/PointLight.h"
#include "Lighting/light.h"
#include <cmath>

#include "Managers/LightManager.h"

void TestLight::start()
{
	// wont need these two components later on for a basic light. Can include them for visual representation, i.e lamp model
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("tester"), "Resources/textures/TestCube.mtl"));
	AddComponent(new ComponentShaderDefault(Game::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));

	Vector3f pos(0.0f, 5.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f)));

	//PointLight* light = new PointLight(7.0f, Vector3f(1.0f, 0.5f, 1.0f));

	//AddComponent(new LightComponent(light));

	AddComponent(LightManager::GetInstance().CreatePointLight(7.0f, Vector3f(1.0f, 0.0f, 1.0f)));
}

TestLight::TestLight()
{
	start();
}

void TestLight::SetPosition(const Vector3f& pPosition)
{
	GetComponent<ComponentTransform>()->SetPosition(pPosition);

	if (GetComponent<ComponentRigidBody>() != nullptr)
		GetComponent<ComponentRigidBody>()->SetPosition(pPosition);
}

void TestLight::SetRotation(glm::vec3 pRot)
{
	GetComponent<ComponentTransform>()->SetRotation(pRot);
}

void TestLight::Rotate(float pAmount, float dt)
{
	glm::vec3 rot = GetComponent<ComponentTransform>()->GetRotation();
	rot.y += pAmount * dt;

	GetComponent<ComponentTransform>()->SetRotation(rot);
}


void TestLight::MoveForward() {
	// Example movement logic: Adjust the position forward
	ComponentTransform* transform = GetComponent<ComponentTransform>();
	if (transform) {
		glm::vec3 pos = glm::vec3(transform->GetPosition().GetX(), transform->GetPosition().GetY(), transform->GetPosition().GetZ());
		pos.z += 32.0f * Game::GetDeltaTime();  // Move forward along the Z-axis
		SetPosition(Vector3f(pos.x, pos.y, pos.z));
	}
}

void TestLight::MoveBackward() {
	ComponentTransform* transform = GetComponent<ComponentTransform>();
	if (transform) {
		glm::vec3 pos = glm::vec3(transform->GetPosition().GetX(), transform->GetPosition().GetY(), transform->GetPosition().GetZ());
		pos.z -= 32.0f * Game::GetDeltaTime();  // Move backward along the Z-axis
		SetPosition(Vector3f(pos.x, pos.y, pos.z));
	}
}

void TestLight::MoveLeft() {
	ComponentTransform* transform = GetComponent<ComponentTransform>();
	if (transform) {
		glm::vec3 pos = glm::vec3(transform->GetPosition().GetX(), transform->GetPosition().GetY(), transform->GetPosition().GetZ());
		pos.x -= 32.0f * Game::GetDeltaTime();  // Move left along the X-axis
		SetPosition(Vector3f(pos.x, pos.y, pos.z));
	}
}

void TestLight::MoveRight() {
	ComponentTransform* transform = GetComponent<ComponentTransform>();
	if (transform) {
		glm::vec3 pos = glm::vec3(transform->GetPosition().GetX(), transform->GetPosition().GetY(), transform->GetPosition().GetZ());
		pos.x += 32.0f * Game::GetDeltaTime();  // Move right along the X-axis
		SetPosition(Vector3f(pos.x, pos.y, pos.z));
	}
}