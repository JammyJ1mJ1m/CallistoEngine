#pragma once
#include "../common.h"

class Light
{
public:
	Light();
	~Light();

	virtual void Run(glm::vec3 pos, int i, Shader* pShader);

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Shader* shader;

private:
};

