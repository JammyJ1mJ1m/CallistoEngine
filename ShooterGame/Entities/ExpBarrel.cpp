#include "ExpBarrel.h"
#include "ShooterGame.h"
#include "Components/ComponentRigidBody.h"
#include "Components/ComponentCollider.h"
#include "Components/ComponentShaderWindow.h"


void ExpBarrel::start()
{
    //AddComponent(new ComponentModel(Game::GetGame()->GetMesh("barrel"), "Resources/Geometry/Barrel/expBarrel.mtl"));
    AddComponent(new ComponentModel(Game::GetGame()->GetMesh("barrel"), "Resources/Geometry/Barrel/expBarrel.mtl"));
    //AddComponent(new ComponentShaderWindow(ShooterGame::GetGameCamera(), "Resources/Shaders/window.vert", "Resources/Shaders/window.frag"));
    // sAddComponent(new ComponentShaderScanLines(ShooterGame::GetGameCamera(), "Resources/Shaders/ScanLines.vert", "Resources/Shaders/ScanLines.frag"));

    Vector3f pos(-10.0f, 10.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1)));
	//mEntities.push_back(tri);

	// create mesh colider shape
	std::vector<Vertex> vertices = Game::GetGame()->GetMesh("barrel")->GetVertices();
	std::vector<int> indices = Game::GetGame()->GetMesh("barrel")->GetIndices();

    ComponentCollider* collider = new ComponentCollider(2, 2.75);
    //ComponentCollider* collider2 = new ComponentCollider(btVector3(3,4,4));
	//ComponentCollider* collider = new ComponentCollider(2/*,2.75*/);
	AddComponent(collider);
	//AddComponent(collider2);

	int mass = 1;
	ComponentRigidBody* rb = new ComponentRigidBody(collider, mass, pos, false);
	AddComponent(rb);

    ExplodableComponent* exp = new ExplodableComponent(this);

    AddComponent(exp);
}



ExpBarrel::ExpBarrel()
{
	start();
}

void ExpBarrel::SetPosition(const Vector3f& pPosition)
{
    GetComponent<ComponentTransform>()->SetPosition(pPosition);
    GetComponent<ComponentRigidBody>()->SetPosition(pPosition);
}

void ExpBarrel::OnMessage(Message* msg)
{
	if (msg->GetMessageType() == "explode")
	{
		std::cout << "Big Boom, messages!" << std::endl;
	}
	Entity::OnMessage(msg);
}

void ExpBarrel::MoveForward()
{
}

void ExpBarrel::MoveBackward()
{
}

void ExpBarrel::MoveLeft()
{
}

void ExpBarrel::MoveRight()
{
}