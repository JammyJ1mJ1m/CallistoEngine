#pragma once
#include <iostream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "Window.h"
#include "../Managers/ResourceManager.h"

class PostProcessor
{
	static PostProcessor* mInstance;

	GLuint textureColorbuffer;
	GLuint quadVAO, quadVBO;
	GLuint postProcessingShader;

	PostProcessor();
public:
	static PostProcessor& GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new PostProcessor();

		return *mInstance;
	}
	//void GenTexture();
	bool Initialise();
	void LoadShader(const char* pVertexPath, const char* pFragPath);
	//PostProcessor(const char* pShaderPath);
	void UpdateSize(const int pWidth, const int pHeight);
	void CreateScreenBuffer();
	void DrawPP();
	~PostProcessor() = default;

};