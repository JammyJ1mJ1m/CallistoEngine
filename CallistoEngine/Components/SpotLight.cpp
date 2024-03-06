#include "SpotLight.h"
#include "../common.h"


SpotLight::SpotLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, Shader pShader, glm::vec3 pos, float inner, float outer, glm::vec3 dir)
{
	position = pos;
	direction = dir;
	ambient = amb;
	diffuse = diff;
	specular = spec;

	shader = &pShader;

	innerCutoff = glm::cos(glm::radians(inner));
	outerCutoff = glm::cos(glm::radians( outer));
	name = "spotLight[";
}

SpotLight::~SpotLight()
{
}

void SpotLight::Run(glm::vec3 pos, int i, Shader* pShader)
{
	PointLight::Run(pos, i, pShader);
	pShader->setVec3(InsertVar(name, "].direction\0", i), direction);
	pShader->setFloat(InsertVar(name, "].cutOff\0", i), innerCutoff);
	pShader->setFloat(InsertVar(name, "].outerCutOff\0", i), outerCutoff);
}

