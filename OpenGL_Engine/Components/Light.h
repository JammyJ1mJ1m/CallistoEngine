#pragma once
#include "../common.h"

class Light
{
public:
	Light();
	~Light();

	virtual void Run(glm::vec3 pos, int i, Shader* pShader);
	std::string InsertVar(const char* first, const char* second, int var);

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Shader* shader;

	const char* name;
private:

};

