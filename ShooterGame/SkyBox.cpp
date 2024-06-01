#include "SkyBox.h"
#include "Components/ComponentModel.h"
#include "ComponentShaderSkybox.h"

#include "Components/ComponentTransform.h"
#include "ShooterGame.h"

void SkyBox::start()
{
	AddComponent(new ComponentModel("Resources/Geometry/TCube/TCube.obj", "Resources/textures/cubemaps/skybox.mtl", true));
	AddComponent(new ComponentShaderSkybox (ShooterGame::GetGameCamera(), "Resources/Shaders/skybox.vert", "Resources/Shaders/skybox.frag"));
	AddComponent(new ComponentTransform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f)));

}

SkyBox::SkyBox()
{
	start();
}
