#pragma once
#include "Light.h"
class DirectionalLight :
    public Light
{
public:
    DirectionalLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, glm::vec3 dir);
    ~DirectionalLight();

    void Run(glm::vec3 pos, int i, Shader* pShader) override;
    glm::vec3 direction;

};

