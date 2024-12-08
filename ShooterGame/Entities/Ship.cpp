#include "Ship.h"
#include "Components/ComponentRigidBody.h"

#include "Components/ComponentCollider.h"
#include "Math/Vector.h"
#include "Misc/Sound.h"
#include "Components/ComponentShaderWindow.h"
#include "messages/ThrustMessage.h"
#include "Components/ShipControllerComponent.h"



void Ship::start()
{
	mMoveForce = 50.0f;

	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("spaceship"), "Resources/Geometry/ship/ship.mtl"));
	//AddComponent(new ComponentShaderWindow(ShooterGame::GetGameCamera(), "Resources/Shaders/window.vert", "Resources/Shaders/window.frag"));
	Vector3f pos(0.0f, 40.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f)));

	std::vector<Vertex> vertices = Game::GetGame()->GetMesh("spaceship")->GetVertices();
	std::vector<int> indices = Game::GetGame()->GetMesh("spaceship")->GetIndices();

	// getforward vector of the transform

	// ComponentCollider* collider = new ComponentCollider(vertices, indices);
	ComponentCollider* collider = new ComponentCollider(2);
	AddComponent(collider);

	btScalar mass = 1.0;
	ComponentRigidBody* rb = new ComponentRigidBody(collider, mass, pos);
	AddComponent(rb);

	 AddComponent(LightManager::GetInstance().CreatePointLight(158.0f, Vector3f(1.0f, 0.0f, 1.0f), Vector3f(10,3,-20)));

	AddComponent(new ShipControllerComponent(this));
}

void Ship::SetPosition(const Vector3f& pPosition)
{
	GetComponent<ComponentTransform>()->SetPosition(pPosition);
	GetComponent<ComponentRigidBody>()->SetPosition(pPosition);
}

void Ship::MoveForward()
{
	Vector3f forward = GetComponent<ComponentTransform>()->GetForwardVector();

	// get rigidbody
	ComponentRigidBody* rb = GetComponent<ComponentRigidBody>();
	// add forward force to the rb
	Vector3f v = forward * mMoveForce;
	rb->ApplyForce(v);

}

void Ship::MoveBackward()
{
	Vector3f forward = GetComponent<ComponentTransform>()->GetForwardVector();

	// get rigidbody
	ComponentRigidBody* rb = GetComponent<ComponentRigidBody>();
	// add forward force to the rb
	Vector3f v = forward * -mMoveForce;
	rb->ApplyForce(v);
}

void Ship::MoveLeft()
{
	Vector3f right = GetComponent<ComponentTransform>()->GetRightVector();

	// get rigidbody
	ComponentRigidBody* rb = GetComponent<ComponentRigidBody>();
	// add forward force to the rb
	Vector3f v = right * -mMoveForce;
	rb->ApplyForce(v);
}

void Ship::MoveRight()
{
	Vector3f right = GetComponent<ComponentTransform>()->GetRightVector();

	// get rigidbody
	ComponentRigidBody* rb = GetComponent<ComponentRigidBody>();
	// add forward force to the rb
	Vector3f v = right * mMoveForce;
	rb->ApplyForce(v);
}

void Ship::OnMessage(Message* msg)
{
	/*if (msg->GetMessageType() == "rotateR")
	{
		ComponentRigidBody* rb = GetComponent<ComponentRigidBody>();
		rb->ApplyTorque(Vector3f(0.0f,2.0f, 0.0f));
	}
	if (msg->GetMessageType() == "rotateL")
	{
		ComponentRigidBody* rb = GetComponent<ComponentRigidBody>();
		rb->ApplyTorque(Vector3f(0.0f, -2.0f, 0.0f));
	}*/
	Entity::OnMessage(msg);
}

Ship::Ship()
{
	start();
}
