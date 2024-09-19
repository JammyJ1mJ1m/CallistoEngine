#include "Renderer_GL.h"
#include "../Components/ComponentModel.h"
#include "../Components/ComponentShader.h"
#include "../Managers/ResourceManager.h"

void Renderer_GL::ClearScreen()
{
	// binds to the frame buffer for drawing the scene - later used in PP
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glEnable(GL_DEPTH_TEST);
	glClearColor(_clearColour.GetX(), _clearColour.GetY(), _clearColour.GetZ(), _clearColour.GetW());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer_GL::Destroy()
{

}



//GLuint CompileShader(GLenum type, const char* source)
//{
//	GLuint shader = glCreateShader(type);
//	glShaderSource(shader, 1, &source, NULL);
//	glCompileShader(shader);
//
//	// Check for shader compile errors
//	GLint success;
//	GLchar infoLog[512];
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(shader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	return shader;
//}
//
//GLuint CreateShaderProgram(const char* vertexSource, const char* fragmentSource)
//{
//	// Compile vertex and fragment shaders
//	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
//	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
//
//	// Link shaders into a program
//	GLuint shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	// Check for linking errors
//	GLint success;
//	GLchar infoLog[512];
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//	}
//
//	// Clean up shaders (they are now linked into the program and no longer needed)
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	return shaderProgram;
//}




void Renderer_GL::Initialise(int width, int height)
{
	PP = &PostProcessor::GetInstance();
	// 1. Create framebuffer
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	PP->Initialise();

	//// 2. Create texture to store scene
	//glGenTextures(1, &textureColorbuffer);
	//glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	// 3. Create renderbuffer for depth and stencil
	/*GLuint rbo;*/
	CreateRBO(width, height);

//	// 4. Setup quad for post-processing
//	float quadVertices[] = {
//		// positions   // texCoords
//		-1.0f,  1.0f,  0.0f, 1.0f,
//		-1.0f, -1.0f,  0.0f, 0.0f,
//		 1.0f, -1.0f,  1.0f, 0.0f,
//
//		-1.0f,  1.0f,  0.0f, 1.0f,
//		 1.0f, -1.0f,  1.0f, 0.0f,
//		 1.0f,  1.0f,  1.0f, 1.0f
//	};
//
//	glGenVertexArrays(1, &quadVAO);
//	glGenBuffers(1, &quadVBO);
//	glBindVertexArray(quadVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//
//	// Load post-processing shader
//	//postProcessingShader = LoadShader("postprocessing.vert", "postprocessing.frag");
//
//	const char* postProcessingVertexShaderSource = R"(
//#version 330 core
//layout (location = 0) in vec2 aPos;
//layout (location = 1) in vec2 aTexCoords;
//
//out vec2 TexCoords;
//
//void main()
//{
//    TexCoords = aTexCoords;
//    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
//}
//)";
//
//	const char* postProcessingFragmentShaderSource = R"(
//#version 330 core
//out vec4 FragColor;
//in vec2 TexCoords;
//
//uniform sampler2D screenTexture;
//
//void main()
//{
//    vec3 color = texture(screenTexture, TexCoords).rgb;
//
//    color = vec3(pow(color.x, 7.0 / 5.0), color.y, pow(color.z, 8.0 / 5.0));
//   
//
//    FragColor = vec4(color, 1.0);
//}
//)";
//
//	const char* edgeDetectionFragmentShaderSource = R"(
//#version 330 core
//out vec4 FragColor;
//
//in vec2 TexCoords;
//
//uniform sampler2D screenTexture;
//
//const float offset = 1.0 / 800.0;  
//
//void main()
//{
//    vec2 offsets[9] = vec2[](
//        vec2(-offset,  offset), // top-left
//        vec2( 0.0f,    offset), // top-center
//        vec2( offset,  offset), // top-right
//        vec2(-offset,  0.0f),   // center-left
//        vec2( 0.0f,    0.0f),   // center-center
//        vec2( offset,  0.0f),   // center-right
//        vec2(-offset, -offset), // bottom-left
//        vec2( 0.0f,   -offset), // bottom-center
//        vec2( offset, -offset)  // bottom-right    
//    );
//
//    float kernel[9] = float[](
//    1.0 / 16, 2.0 / 16, 1.0 / 16,
//    2.0 / 16, 4.0 / 16, 2.0 / 16,
//    1.0 / 16, 2.0 / 16, 1.0 / 16  
//);
//    
//    vec3 sampleTex[9];
//    for(int i = 0; i < 9; i++)
//    {
//        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
//    }
//    vec3 col = vec3(0.0);
//    for(int i = 0; i < 9; i++)
//        col += sampleTex[i] * kernel[i];
//    
//    FragColor = vec4(col, 1.0);
//} 
//)";
//
//
//
//	postProcessingShader = CreateShaderProgram(postProcessingVertexShaderSource, postProcessingFragmentShaderSource);


}

void Renderer_GL::CreateRBO(int width, int height)
{
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	// Check framebuffer completeness
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Renderer_GL::SwapBuffers()
{
}

void Renderer_GL::Render(Entity* entity)
{

	ComponentModel* model = entity->GetComponent <ComponentModel>();
	model->GetMesh()->Draw();
}

void Renderer_GL::DrawPP()
{
	PP->DrawPP();
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glDisable(GL_DEPTH_TEST); 
	//glClear(GL_COLOR_BUFFER_BIT);

	//glUseProgram(postProcessingShader);
	//glBindVertexArray(quadVAO);
	//glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// Screen quad texture (the scene)
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer_GL::StartPP()
{
}

void Renderer_GL::BindRBO(int W, int H) 
{
	CreateRBO(W,H);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}
