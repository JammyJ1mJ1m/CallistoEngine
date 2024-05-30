#include "ShaderObject_GL.h"
// include string stream
#include <sstream>
#include "../Managers/ResourceManager.h"
#include "../Camera.h"

ShaderObject_GL::ShaderObject_GL(const char* pVertexPath, const char* pFragPath)
{
	ResourceManager& manager = ResourceManager::getInstance();

	// load and configure vertex shader
	std::string vshaderSrc = manager.LoadShader(pVertexPath);
	const char* vertexShaderSource = vshaderSrc.c_str();


	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// load and configure frag shader
	std::string fShaderSrc = manager.LoadShader(pFragPath);
	const char* fragmentShaderSource = fShaderSrc.c_str();



	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// creating shader program
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//glUseProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glEnable(GL_DEPTH_TEST);
}

const void ShaderObject_GL::UseProgram()
{
	glUseProgram(shaderProgram);
}



void ShaderObject_GL::Render()
{
}

void ShaderObject_GL::SetMat4(const char* pName, glm::mat4 pMatrix)
{
	unsigned int transformLoc = glGetUniformLocation(shaderProgram, pName);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(pMatrix));
}

void ShaderObject_GL::SetVec3(const char* pName, glm::vec3 pVec)
{
}
