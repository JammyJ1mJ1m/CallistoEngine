#include "Light.h"
Light::Light() 
{
	//std::cout << "This is the base class" << std::endl;
}

Light::~Light()
{
}

void Light::Run(glm::vec3 pos, int i, Shader* pShader)
{
	//std::cout << "This is running in base run" << std::endl;

}
