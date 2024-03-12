#include "ShaderObject_GL.h"
// include string stream
#include <sstream>
#include "../Managers/ResourceManager.h"

ShaderObject_GL::ShaderObject_GL()
{
	ResourceManager& manager = ResourceManager::getInstance();

	std::string vshaderSrc = manager.LoadShader("../CallistoEngine/Shaders/default.vert");
	const char* vertexShaderSource = vshaderSrc.c_str();
	/*const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";*/

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

	std::string fShaderSrc = manager.LoadShader("../CallistoEngine/Shaders/default.frag");
	const char* fragmentShaderSource = fShaderSrc.c_str();

	/*const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"

		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";*/

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
}

const void ShaderObject_GL::UseProgram()
{
	glUseProgram(shaderProgram);
}



void ShaderObject_GL::Render()
{
}

void ShaderObject_GL::LoadShader(const char* pFile)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string shaderCode;
	
	std::ifstream shaderFileStream;
	
	// ensure ifstream objects can throw exceptions:
	shaderFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		// open files
		shaderFileStream.open(pFile);
		
		std::stringstream shaderStringStream;
		// read file's buffer contents into streams
		shaderStringStream << shaderFileStream.rdbuf();
		
		// close file handlers
		shaderFileStream.close();
		
		// convert stream into string
		shaderCode = shaderStringStream.str();
		
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

void ShaderObject_GL::SetWorldMatrix(const char* pName, glm::mat4 pMatrix)
{
	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(pMatrix));
}
