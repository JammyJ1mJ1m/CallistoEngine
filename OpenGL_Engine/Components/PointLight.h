#pragma once
#include "Light.h"
class PointLight :
    public Light
{
public:
    PointLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, Shader pShader, glm::vec3 pos);
    ~PointLight();

    void Run(glm::vec3 pos,int i, Shader* pShader) override;

    glm::vec3 position;
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
private:
};

