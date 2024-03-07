#pragma once
#include "VBO.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
class VBO_GL : public VBO
{
	// Data
private:
	GLuint mVaoID;
	GLuint mVboID;

	int mNumVertices;

	// Constructors
public:
	VBO_GL();
	virtual ~VBO_GL();

	// Functions
public:
	virtual void Create(Vertex vertices[], int numVertices);
	virtual void Draw();
private:
	void DrawVBO();
	void DrawVAO();
};

