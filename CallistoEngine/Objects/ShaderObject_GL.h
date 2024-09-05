#pragma once
#include "ShaderObject.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderObject_GL : public ShaderObject
{
	int shaderProgram;
public:
	const int GetShaderProgram() const { return shaderProgram; }

	ShaderObject_GL(const char* pVertexPath, const char* pFragPath);
	virtual ~ShaderObject_GL() = default;
	const virtual void UseProgram();
	virtual void Render();

	virtual void SetMat4(const char* pName, glm::mat4 pMatrix);
	virtual void SetVec3(const char* pName, const Vector3f& pVec);
	virtual void SetFloat(const char* pName, float pFloat);

};