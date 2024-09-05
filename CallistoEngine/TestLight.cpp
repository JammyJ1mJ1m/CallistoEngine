#include "TestLight.h"
#include "game.h"
#include "Components/ComponentRigidBody.h"
#include "Components/ComponentCollider.h"
#include "Components/LightComponent.h"
#include "lighting/PointLight.h"
#include "Lighting/light.h"
#include <cmath>

void TestLight::start()
{
	// wont need these two components later on for a basic light. Can include them for visual representation, i.e lamp model
	/*AddComponent(new ComponentModel(Game::GetGame()->GetMesh("tester"), "Resources/textures/TestCube.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));*/

	glm::vec3 pos = glm::vec3(40, 0.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.2, 1.2, 1.2)));

	//PointLight* light = new PointLight(7.0f, Vector3f(1.0f, 0.5f, 1.0f));

	//AddComponent(new LightComponent(light));

}

TestLight::TestLight(Light* pLight)
{
	start();
	AddComponent(new LightComponent(pLight));
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


void TestLight::MoveForward()
{
	// Wake the rigidbody up so it can move
	GetComponent<ComponentRigidBody>()->GetRigidBody()->activate(true);
	GetComponent<ComponentRigidBody>()->GetRigidBody()->setAngularFactor(btVector3(0, 0, 0));

	// Get the game delta time
	double mDeltaTime = Game::GetGame()->GetDeltaTime();

	// Apply force in the negative z-direction to move forward
	btVector3 force = btVector3(0, 0, -1024);
	GetComponent<ComponentRigidBody>()->GetRigidBody()->applyForce(force, btVector3(0, 0, 0));
}

void TestLight::MoveBackward()
{
	// Wake the rigidbody up so it can move
	GetComponent<ComponentRigidBody>()->GetRigidBody()->activate(true);
	GetComponent<ComponentRigidBody>()->GetRigidBody()->setAngularFactor(btVector3(0, 0, 0));

	// Get the game delta time
	double mDeltaTime = Game::GetGame()->GetDeltaTime();

	// Apply force in the positive z-direction to move backward
	btVector3 force = btVector3(0, 0, 1024);
	GetComponent<ComponentRigidBody>()->GetRigidBody()->applyForce(force, btVector3(0, 0, 0));
}

void TestLight::MoveLeft()
{
	// Wake the rigidbody up so it can move
	GetComponent<ComponentRigidBody>()->GetRigidBody()->activate(true);
	GetComponent<ComponentRigidBody>()->GetRigidBody()->setAngularFactor(btVector3(0, 0, 0));

	// Get the game delta time
	double mDeltaTime = Game::GetGame()->GetDeltaTime();

	// Apply force in the positive z-direction to move backward
	btVector3 force = btVector3(-512, 0, 0.0);
	GetComponent<ComponentRigidBody>()->GetRigidBody()->applyForce(force, btVector3(0, 0, 0));

}

void TestLight::MoveRight()
{
	// Wake the rigidbody up so it can move
	GetComponent<ComponentRigidBody>()->GetRigidBody()->activate(true);
	GetComponent<ComponentRigidBody>()->GetRigidBody()->setAngularFactor(btVector3(0, 0, 0));

	// Get the game delta time
	double mDeltaTime = Game::GetGame()->GetDeltaTime();

	// Apply force in the positive z-direction to move backward
	btVector3 force = btVector3(512, 0, 0.0);
	GetComponent<ComponentRigidBody>()->GetRigidBody()->applyForce(force, btVector3(0, 0, 0));

}

