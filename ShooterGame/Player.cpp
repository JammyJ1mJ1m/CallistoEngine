#include "Player.h"
#include "ShooterGame.h"
#include "Components/ComponentRigidBody.h"
#include "Components/ComponentCollider.h"

void Player::start()
{
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("ship"), "Resources/textures/Floor.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));

	glm::vec3 pos = glm::vec3(0.0f, -5.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1)));
	//mEntities.push_back(tri);

	// create mesh colider shape
	std::vector<Vertex> vertices = Game::GetGame()->GetMesh("ship")->GetVertices();
	std::vector<int> indices = Game::GetGame()->GetMesh("ship")->GetIndices();

	ComponentCollider* collider = new ComponentCollider(vertices, indices);
	AddComponent(collider);

	int mass = 0;
	ComponentRigidBody* rb = new ComponentRigidBody(collider, mass, pos);
	AddComponent(rb);


}

void Player::SetPosition()
{
}

Player::Player()
{

	start();
}

void Player::SetPosition(glm::vec3 pPos)
{
	GetComponent<ComponentTransform>()->SetPosition(pPos);
	GetComponent<ComponentRigidBody>()->SetPosition(pPos);
}
