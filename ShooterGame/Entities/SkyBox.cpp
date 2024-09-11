#include "SkyBox.h"
#include "Components/ComponentModel.h"
#include "ComponentShaderSkybox.h"

#include "Components/ComponentTransform.h"
#include "ShooterGame.h"
#include "Math/Vector.h"

void SkyBox::start()
{
	Vector3f pos(0.0f, 0.0f, 0.0f);
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("cube"), "Resources/textures/cubemaps/sky/skybox.mtl", true));
	AddComponent(new ComponentShaderSkybox (ShooterGame::GetGameCamera(), "Resources/Shaders/skybox.vert", "Resources/Shaders/skybox.frag"));
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f)));

}


SkyBox::SkyBox()
{
	start();
}

void SkyBox::SetPosition(const Vector3f& pPosition)
{
}

void SkyBox::MoveForward()
{
}

void SkyBox::MoveBackward()
{
}

void SkyBox::MoveLeft()
{
}

void SkyBox::MoveRight()
{
}
