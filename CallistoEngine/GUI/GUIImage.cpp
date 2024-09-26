#include "GUIImage.h"
#include "../Managers/ResourceManager.h"
#include "../Graphical/Window.h"

float GUIImage::CalculateAspectRatio(const int pWidth, const int pHeight)
{
	return pWidth / pHeight;
}

GUIImage::GUIImage(const Vector3f& pCol)
{
	mColor = pCol;

}

void GUIImage::Initialise(int width, int height, float scale)
{
	height *= scale;
	width *= scale;

	//float offsetX = width / 2;
	//float offsetY = height / 2;

	const char* mFontShaderVert = "Resources/Shaders/Text/Image.vert";

	const char* mFontShaderFrag = "Resources/Shaders/Text/Image.frag";

	mShaderObject = new ShaderObject_GL(mFontShaderVert, mFontShaderFrag);
	mShaderObject->UseProgram();

	// TODO  grab the window sizes
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(1423), 0.0f, static_cast<float>(800));
	glUniformMatrix4fv(glGetUniformLocation(mShaderObject->GetShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	mTextureHandle = ResourceManager::getInstance().LoadTexture("Resources/textures/GUI/3DTestTrans.png");

	float quadVertices[] = {
		// Positions          // Texture Coords
		   0.0f,   height, 0.0f,  0.0f, 1.0f, // Top-left
		   width,  height, 0.0f,  1.0f, 1.0f, // Top-right
		   width,  0.0f,   0.0f,  1.0f, 0.0f, // Bottom-right
		   0.0f,   0.0f,   0.0f,  0.0f, 0.0f  // Bottom-left
	};

	unsigned int quadIndices[] = {
		0, 1, 2,
		2, 3, 0
	};


	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0);

}

void GUIImage::Render()
{
	// Use the shader program
	mShaderObject->UseProgram();
	int wHeight = Window::TheWindow->GetWindowHeight();
	int wWidth = Window::TheWindow->GetWindowWidth();

	//glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(wWidth), 0.0f, static_cast<float>(wHeight));
	//glUniformMatrix4fv(glGetUniformLocation(mShaderObject->GetShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureHandle);
	glUniform1i(glGetUniformLocation(mShaderObject->GetShaderProgram(), "texture1"), 0); // Set the texture unit

	glUniform3f(glGetUniformLocation(mShaderObject->GetShaderProgram(), "translation"), mPosition.x, mPosition.y, 0.0f);
	// Bind the VAO and draw the quad
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}
