#include "Player.h"
#include "ShooterGame.h"

void Player::start()
{
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("ship"), "Resources/textures/TCube.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(),"Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));
	AddComponent(new ComponentTransform(glm::vec3(-0.0f, -5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f)));
	//mEntities.push_back(tri);
}

Player::Player()
{

	start();
}
