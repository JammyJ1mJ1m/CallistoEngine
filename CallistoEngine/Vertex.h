#pragma once
#include "Vector.h"

#if OPENGL
#include <glm/glm.hpp>

struct Vertex {
    // position
    glm::vec3 Position;
    // texCoords
    glm::vec2 TexCoords;
    //// normal
    glm::vec3 Normal;

};
#endif