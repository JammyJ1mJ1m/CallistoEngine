#include "TestCube.h"
#include "ShooterGame.h"
#include "Components/ComponentRigidBody.h"
#include "Components/ComponentCollider.h"

void TestCube::start()
{
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("cube"), "Resources/textures/TestCube.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));

	glm::vec3 pos = glm::vec3(-8.0f, 15.0f, 20.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1)));
	//mEntities.push_back(tri);

	// create mesh colider shape
	std::vector<Vertex> vertices = Game::GetGame()->GetMesh("cube")->GetVertices();
	std::vector<int> indices = Game::GetGame()->GetMesh("cube")->GetIndices();

	//ComponentCollider* collider = new ComponentCollider(vertices, indices);
	// CREATE A BOX COLLIDER
	ComponentCollider* collider = new ComponentCollider(2, 2, 2);

	AddComponent(collider);

	int mass = 64;
	ComponentRigidBody* rb = new ComponentRigidBody(collider, mass, pos);
	AddComponent(rb);
}

void TestCube::SetPosition()
{
}

TestCube::TestCube()
{
	start();
}

void TestCube::SetPosition(glm::vec3 pPos)
{
	GetComponent<ComponentTransform>()->SetPosition(pPos);
	GetComponent<ComponentRigidBody>()->SetPosition(pPos);
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
    // Wake the rigidbody up so it can move
    GetComponent<ComponentRigidBody>()->GetRigidBody()->activate(true);
    GetComponent<ComponentRigidBody>()->GetRigidBody()->setAngularFactor(btVector3(0, 0, 0));

    // Get the game delta time
    double mDeltaTime = Game::GetGame()->GetDeltaTime();

    // Apply force in the negative z-direction to move forward
    btVector3 force = btVector3(0, 0, -1024);
    GetComponent<ComponentRigidBody>()->GetRigidBody()->applyForce(force, btVector3(0, 0, 0));
}

void TestCube::MoveBackward()
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

void TestCube::MoveLeft()
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

void TestCube::MoveRight()
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

