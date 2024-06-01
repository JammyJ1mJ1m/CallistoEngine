#include "Enemy.h"

void Enemy::start()
{
	AddComponent(new ComponentModel("Resources/Geometry/test/AwesomeAxolotls_1.obj", "Resources//Geometry/test/AwesomeAxolotls_1.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));
	AddComponent(new ComponentTransform(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
	//mEntities.push_back(tri);
}

Enemy::Enemy()
{
	start();
}
