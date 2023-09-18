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
}

PointLight::~PointLight()
{
}

void PointLight::Run(glm::vec3 pos, int i, Shader* pShader)
{
	Shader* loc;
	loc = pShader;
	std::cout << "passed   ptr: " << loc << std::endl;

	
	//position = pos;
	//std::cout << "This is running in derived run" << std::endl;

	std::stringstream ss;
	ss << "pointLight[" << i << "].ambient\0";
	std::string am = ss.str();
	ss.str("");

	ss << "pointLight[" << i << "].diffuse\0";
	std::string di = ss.str();
	ss.str("");

	ss << "pointLight[" << i << "].specular\0";
	std::string sp = ss.str();
	ss.str("");

	ss << "pointLight[" << i << "].position\0";
	std::string po = ss.str();
	ss.str("");

	ss << "pointLight[" << i << "].constant\0";
	std::string co = ss.str();
	ss.str("");

	ss << "pointLight[" << i << "].linear\0";
	std::string li = ss.str();
	ss.str("");

	ss << "pointLight[" << i << "].quadratic\0";
	std::string qu = ss.str();

	ss.str("");

	//std::cout << "position "<< i <<" = " << position.x << position.y << position.z << std::endl;

	pShader->setVec3(am, 0.05f, 0.05f, 0.05f);
	pShader->setVec3(di, diffuse);
	pShader->setVec3(sp, 1.0f, 1.0f, 1.0f);
	pShader->setVec3(po, position);
	pShader->setFloat(co, 1.0f);
	pShader->setFloat(li, 0.022f);
	pShader->setFloat(qu, 0.0019f);
}
