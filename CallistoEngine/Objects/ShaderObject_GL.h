#pragma once
#include "ShaderObject.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <iostream>

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

};

