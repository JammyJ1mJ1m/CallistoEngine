#include "PointLight.h"
#include "../common.h"


PointLight::PointLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, Shader pShader, glm::vec3 pos)
{
	ambient = amb;
	diffuse = diff;
	specular = spec;
	shader = &pShader;
	position = pos;
	//std::cout << "This is the derived class" << std::endl;
	name = "pointLight[";
}

PointLight::PointLight()
{
}

PointLight::~PointLight()
{
}

void PointLight::Run(glm::vec3 pos, int i, Shader* pShader)
{
	pShader->setVec3(InsertVar(name, "].ambient\0", i), 0.05f, 0.05f, 0.05f);
	pShader->setVec3(InsertVar(name, "].diffuse\0", i), diffuse);
	pShader->setVec3(InsertVar(name, "].specular\0", i), diffuse);
	pShader->setVec3(InsertVar(name, "].position\0", i), position);
	pShader->setFloat(InsertVar(name, "].constant\0", i), 1.0f);
	pShader->setFloat(InsertVar(name, "].linear\0", i), 0.022f);
	pShader->setFloat(InsertVar(name, "].quadratic\0",i) , 0.0019f);

}



void PointLight::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;

	//std::cout << position.x << position.y << position.z << std::endl;
}
