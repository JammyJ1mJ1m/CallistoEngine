#include "Player.h"
#include "ShooterGame.h"

void Player::start()
{
	AddComponent(new ComponentModel("Resources/Geometry/test/Intergalactic_Spaceship.obj", "Resources/textures/TestCube.mtl"));
	AddComponent(new ComponentShader(ShooterGame::GetGameCamera()));
	AddComponent(new ComponentTransform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
	//mEntities.push_back(tri);
}

Player::Player()
{

	start();
}
