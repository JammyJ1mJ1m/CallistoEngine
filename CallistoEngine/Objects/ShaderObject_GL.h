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
	ShaderObject_GL();
	virtual ~ShaderObject_GL() = default;
	const virtual void UseProgram();

	// virtual void Create(const char* pVertexShader, const char* pFragmentShader);
	virtual void Render();
	virtual void LoadShader(const char* pFile);

	void SetWorldMatrix(const char* pName, glm::mat4 pMatrix, const Camera* pCam);

};

