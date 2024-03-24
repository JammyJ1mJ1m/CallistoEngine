#pragma once
#include "Vector.h"

//struct Vertex
//{
//public:
//	 /*Vector3f position;
//	 Vector2f texCoords;*/
//	// position
//	float x, y, z;
//
//	// colour
//	// float r, g, b;// , a;
//
//	// tex coords
//	float u, v;
//	
//	// Vector3f colour;
//	//Vector3 normal;
//	//Vector3 biNormal;
//	//Vector3 tangent;
//};

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