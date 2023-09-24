#include "DirectionalLight.h"
#include "../common.h"

DirectionalLight::DirectionalLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, glm::vec3 dir)
{
	ambient = amb;
	diffuse = diff;
	specular = spec;
	direction = dir;
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::Run(glm::vec3 pos, int i, Shader* pShader)
{
	pShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	pShader->setVec3("dirLight.diffuse", diffuse);
	pShader->setVec3("dirLight.specular", diffuse);

	pShader->setVec3("dirLight.direction", direction);

}

