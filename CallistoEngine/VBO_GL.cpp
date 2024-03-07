#if OPENGL
#include "VBO_GL.h"
typedef unsigned char byte;

/******************************************************************************************************************/

VBO_GL::VBO_GL()
	: mVboID(0), mVaoID(0), mNumVertices(0)
{
}

/******************************************************************************************************************/

VBO_GL::~VBO_GL()
{
	glDeleteBuffers(1, &mVboID);
	glDeleteVertexArrays(1, &mVaoID);
}

/******************************************************************************************************************/

void VBO_GL::Create(Vertex vertices[], int numVertices)
{
	mNumVertices = numVertices;

	glGenVertexArrays(1, &mVaoID);
	glBindVertexArray(mVaoID);

	glGenBuffers(1, &mVboID);

	glBindBuffer(GL_ARRAY_BUFFER, mVboID);

	glEnableVertexAttribArray(0); // Vertex positions
	// glEnableVertexAttribArray(1); // Colours

	// Set vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);

	// Set colour data
	// glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (byte*)12);

	// Allocate space for the buffers and initialise the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*numVertices, vertices, GL_STATIC_DRAW);

	// OK, finish with VAO setup
	glBindVertexArray(0);

	// glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

/******************************************************************************************************************/

void VBO_GL::Draw()
{
	DrawVAO();
}

/******************************************************************************************************************/

void VBO_GL::DrawVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, mVboID);

	// Enable that vertex attrib array
	int vertexLocation = 0;
	int colourLocation = 1;
	glEnableVertexAttribArray(vertexLocation);
	glEnableVertexAttribArray(colourLocation);

	// Set vertex data
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, false, sizeof(Vertex), 0);

	// Set colour data
	glVertexAttribPointer(colourLocation, 4, GL_FLOAT, false, sizeof(Vertex), (byte*)16);

	// Draw
	glDrawArrays(GL_LINE_STRIP, 0, mNumVertices);

	// Disable vertex attrib array
	glDisableVertexAttribArray(vertexLocation);
	glDisableVertexAttribArray(colourLocation);

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/******************************************************************************************************************/

void VBO_GL::DrawVAO()
{
	glBindVertexArray(mVaoID);

	// Draw
	glDrawArrays(GL_LINE_STRIP, 0, mNumVertices);

	glBindVertexArray(0);
}

/******************************************************************************************************************/

#endif