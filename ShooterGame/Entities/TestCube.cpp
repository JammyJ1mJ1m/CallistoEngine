#include "TestCube.h"
#include "ShooterGame.h"
#include "Components/ComponentRigidBody.h"
#include "Components/ComponentCollider.h"

void TestCube::start()
{
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("AKmagazine"), "Resources/textures/GunAK.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));

	glm::vec3 pos = glm::vec3(15.0f, 0.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1)));
	//mEntities.push_back(tri);

	// create mesh colider shape
	std::vector<Vertex> vertices = Game::GetGame()->GetMesh("AKmagazine")->GetVertices();
	std::vector<int> indices = Game::GetGame()->GetMesh("AKmagazine")->GetIndices();

	Vector3f newPos;
	newPos.SetX(pos.x);
	newPos.SetY(pos.y);
	newPos.SetZ(pos.z);

	ComponentCollider* collider = new ComponentCollider(vertices);
	int mass = 1;
	ComponentRigidBody* rb = new ComponentRigidBody(collider, mass, pos);
	AddComponent(rb);
}



TestCube::TestCube()
{
	start();
}

void TestCube::SetPosition(const Vector3f& pPosition)
{
	GetComponent<ComponentTransform>()->SetPosition(pPosition);
	GetComponent<ComponentRigidBody>()->SetPosition(pPosition);
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

