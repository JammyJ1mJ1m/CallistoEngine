#include "GUIImage.h"
#include "../Managers/ResourceManager.h"
#include "../Graphical/Window.h"
#include "GUIManager.h"

float GUIImage::CalculateAspectRatio(const int pWidth, const int pHeight)
{
	return pWidth / pHeight;
}

void GUIImage::CalculateVertices(float width, float height)
{
	// Define vertices for a quad, using (0, 0) as the bottom-left corner
	float quadVertices[] = {
		// Positions         // Texture Coords
		0.0f,    height, 0.0f,  0.0f, 1.0f, // Top-left
		width,   height, 0.0f,  1.0f, 1.0f, // Top-right
		width,   0.0f,   0.0f,  1.0f, 0.0f, // Bottom-right
		0.0f,    0.0f,   0.0f,  0.0f, 0.0f  // Bottom-left
	};

	unsigned int quadIndices[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Generate buffers
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);

	// Bind and set VAO/VBO/EBO
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

	// Set vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

GUIImage::GUIImage(const Vector4f& pCol)
{
	mColor = pCol;

}

GUIImage::GUIImage(const int pWidth, const int pHeight, const float pScale, const int pMaxWidth, const int pMaxHeight) 
{
	mElementDimensions.SetX(pWidth);
	mElementDimensions.SetY(pHeight);
	mElementMaxDimensions.SetX(pMaxWidth);
	mElementMaxDimensions.SetY(pMaxHeight);

	mScale = pScale;
	mColor = Vector4f();
	Initialise();
}
bool GUIImage::InitialiseChild()
{
	InitialiseImage(mElementMaxDimensions.GetX(), mElementMaxDimensions.GetY());
	return true;
}
void GUIImage::InitialiseImage(const int pMaxWidth, const int pMaxHeight)
{
	float maxWidth = mElementMaxDimensions.GetX();
	float maxHeight = mElementMaxDimensions.GetY();

	if (pMaxWidth < 1)
		maxWidth = 1;
	else if (pMaxWidth > 100)
		maxWidth = 100;
	else
		maxWidth = pMaxWidth;

	if (pMaxHeight < 1)
		maxHeight = 1;
	else if (pMaxHeight > 100)
		maxHeight = 100;
	else
		maxHeight = pMaxHeight;

	maxWidth /= 100;
	maxHeight /= 100;
	mElementMaxDimensions.SetX(maxWidth);
	mElementMaxDimensions.SetY(maxHeight);

	// Get the current window dimensions
	int windowWidth = Window::TheWindow->GetWindowWidth();
	int windowHeight = Window::TheWindow->GetWindowHeight();

	// Calculate initial size as a fraction of the window size
	float initialWidth = windowWidth * maxWidth; // 50% of the window width
	float initialHeight = windowHeight * maxHeight; // 50% of the window height

	// Maintain aspect ratio while scaling
	float imageAspectRatio = static_cast<float>(mElementDimensions.GetX()) / mElementDimensions.GetY();
	if (initialWidth / initialHeight > imageAspectRatio) {
		initialWidth = initialHeight * imageAspectRatio;
	}
	else {
		initialHeight = initialWidth / imageAspectRatio;
	}

	// Update the image dimensions with the scaled values
	mElementDimensions.SetX(static_cast<int>(initialWidth));
	mElementDimensions.SetY(static_cast<int>(initialHeight));

	const char* mFontShaderVert = "Resources/Shaders/Text/Image.vert";
	const char* mFontShaderFrag = "Resources/Shaders/Text/Image.frag";

	mShaderObject = new ShaderObject_GL(mFontShaderVert, mFontShaderFrag);
	mShaderObject->UseProgram();

	// Use the UI projection matrix from the GUIManager
	glUniformMatrix4fv(glGetUniformLocation(mShaderObject->GetShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(GUIManager::GetInstance().GetUIProjection()));

	// Load the texture
	mTextureHandle = ResourceManager::getInstance().LoadTexture("Resources/textures/GUI/whiteBarInfill.png");

	// Calculate vertices based on the adjusted image size
	CalculateVertices(mElementDimensions.GetX(), mElementDimensions.GetY());
}


void GUIImage::ResizeChild(const int pWidth, const int pHeight)
{
	// Calculate the aspect ratio of the image
	float imageAspectRatio = static_cast<float>(mElementDimensions.GetX()) / mElementDimensions.GetY();

	// Calculate new scale factor based on window size, ensuring that the image doesn't exceed a fraction of the window size
	float maxWidth = pWidth * mElementMaxDimensions.GetX();   // Maximum width is 50% of the window width
	float maxHeight = pHeight * mElementMaxDimensions.GetY(); // Maximum height is 50% of the window height

	// Maintain aspect ratio while scaling
	float newWidth = maxWidth;
	float newHeight = maxHeight;
	if (newWidth / newHeight > imageAspectRatio) {
		newWidth = newHeight * imageAspectRatio;  // Adjust width based on height
	}
	else {
		newHeight = newWidth / imageAspectRatio;  // Adjust height based on width
	}

	// Update the quad vertices with the new dimensions while maintaining aspect ratio
	CalculateVertices(newWidth, newHeight);
}


void GUIImage::Render()
{
	// ratio = W / H
	// W = H * Ratio
	// H = W / Ratio

	// Use the shader program
	mShaderObject->UseProgram();
	int windowWidth = Window::TheWindow->GetWindowWidth();
	int windowHeight = Window::TheWindow->GetWindowHeight();

	float newScale = std::min(static_cast<float>(windowWidth) / mElementDimensions.GetX(), static_cast<float>(windowHeight) / mElementDimensions.GetY());
	float newWidth = mElementDimensions.GetX() * newScale;
	float newHeight = mElementDimensions.GetY() * newScale;

	//mProjction = glm::ortho(0.0f, static_cast<float>(windowWidth), 0.0f, static_cast<float>(windowHeight));
	glUniformMatrix4fv(glGetUniformLocation(mShaderObject->GetShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(GUIManager::GetInstance().GetUIProjection()));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureHandle);
	glUniform1i(glGetUniformLocation(mShaderObject->GetShaderProgram(), "texture1"), 0); // Set the texture unit

	glUniform3f(glGetUniformLocation(mShaderObject->GetShaderProgram(), "translation"), mPosition.x, mPosition.y, 0.0f);
	glUniform4f(glGetUniformLocation(mShaderObject->GetShaderProgram(), "color"), mColor.GetX(), mColor.GetY(), mColor.GetZ(), mColor.GetW());
	// Bind the VAO and draw the quad
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}
