#pragma once
#include "PointLight.h"

class SpotLight :
    public PointLight
{
public:
    SpotLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, Shader pShader, glm::vec3 pos, float inner, float outer, glm::vec3 dir);
    ~SpotLight();
    void Run(glm::vec3 pos, int i, Shader* pShader) override;


    float innerCutoff;
    float outerCutoff;
    glm::vec3 direction;

    std::string operator+ (char a);
};

