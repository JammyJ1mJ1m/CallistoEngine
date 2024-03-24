#pragma once
#include "Vector.h"

#if OPENGL
#include <glm/glm.hpp>

struct Vertex {
    // position
    glm::vec3 Position;
    //// normal
    //glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;

};
#endif