#pragma once
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Math/Vector.h"

class Camera;

class ShaderObject
{
	public:
	ShaderObject() = default;
	virtual ~ShaderObject() = default;
	const virtual void UseProgram() = 0;

	// virtual void Create(const char* pVertexShader, const char* pFragmentShader);
	virtual void Render() = 0;
	virtual void SetMat4(const char* pName, glm::mat4 pMatrix) = 0;
	virtual void SetVec3(const char* pName, const Vector3f& pVec) = 0;
	virtual void SetFloat(const char* pName, float pFloat) = 0;

};

