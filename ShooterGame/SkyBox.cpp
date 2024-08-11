#include "SkyBox.h"
#include "Components/ComponentModel.h"
#include "ComponentShaderSkybox.h"

#include "Components/ComponentTransform.h"
#include "ShooterGame.h"

void SkyBox::start()
{
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("cube"), "Resources/textures/cubemaps/sky/skybox.mtl", true));
	AddComponent(new ComponentShaderSkybox (ShooterGame::GetGameCamera(), "Resources/Shaders/skybox.vert", "Resources/Shaders/skybox.frag"));
	AddComponent(new ComponentTransform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f)));

}

void SkyBox::SetPosition()
{
}

SkyBox::SkyBox()
{
	start();
}

void SkyBox::SetPosition(glm::vec3 pPos)
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
