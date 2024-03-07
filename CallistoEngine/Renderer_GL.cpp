#include "Renderer_GL.h"
#include "Components/ComponentModel.h"

void Renderer_GL::ClearScreen()
{
	glClearColor(_clearColour.GetX(), _clearColour.GetY(), _clearColour.GetZ(), _clearColour.GetW());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer_GL::Destroy()
{
	// delete _shader; // Will delete shader objects automatically through ref counting
}

void Renderer_GL::Initialise(int width, int height)
{
	// Setup projection
	// _PM = glm::ortho(-1, +1, -1, +1, -1, +1);

	// Setup viewport and enable depth testing
	//glViewport(0, 0, width, height);
	//glEnable(GL_DEPTH_TEST);


	/////////////////////////////
	// Setup shaders

	// Create shader objects (and compile them)
	/*_vertexShader = new ShaderObject_GL("shader.vert", GL_VERTEX_SHADER);
	_fragmentShader = new ShaderObject_GL("shader.frag", GL_FRAGMENT_SHADER);*/

	//float vertices[] = {
	//-0.5f, -0.5f, 0.0f,
	// 0.5f, -0.5f, 0.0f,
	// 0.0f,  0.5f, 0.0f
	//};

	//unsigned int VBO;
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

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

	const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"

	"void main()\n"
	"{\n"
	"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

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

	glUseProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glGenVertexArrays(1, &VAO);
//
//	// ..:: Initialization code (done once (unless your object frequently changes)) :: ..
//// 1. bind Vertex Array Object
//	glBindVertexArray(VAO);
//	// 2. copy our vertices array in a buffer for OpenGL to use
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	// 3. then set our vertex attributes pointers
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);






	//// Create shader program and attach shader objects
	//_shader = new ShaderProgram_GL();
	//_shader->attachShader(_vertexShader);
	//_shader->attachShader(_fragmentShader);

	//// Link and use the shader
	//_shader->link();
	//_shader->use();

	//_shader->setUniformMatrix("PM", 4, 1, false, glm::value_ptr(_PM));
}

void Renderer_GL::SwapBuffers()
{

}

void Renderer_GL::Render(Entity* entity)
{

	ComponentModel* model = entity->GetComponent <ComponentModel>();
	model->GetMesh().GetVBO()->Draw();

	/*glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);*/
}
