#if OPENGL
#include "VBO_GL.h"
typedef unsigned char byte;

VBO_GL::VBO_GL()
	: mVboID(0), mVaoID(0), mNumVertices(0)
{
}


VBO_GL::~VBO_GL()
{
	glDeleteBuffers(1, &mVboID);
	glDeleteVertexArrays(1, &mVaoID);
}


void VBO_GL::Create(Vertex pVertices[], int pNumVertices, int pIndices[], int pSize)
{
	mNumVertices = pNumVertices;
	mNumIndices = pSize;


	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &mVaoID);
	glGenBuffers(1, &mVboID);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(mVaoID);

	glBindBuffer(GL_ARRAY_BUFFER, mVboID);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * pNumVertices, pVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pIndices) * mNumIndices, pIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// sets culling mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void VBO_GL::Draw()
{
	DrawVAO();
}

void VBO_GL::DrawVBO()
{
	//glBindBuffer(GL_ARRAY_BUFFER, mVboID);

	//// Enable that vertex attrib array
	//int vertexLocation = 0;
	//int colourLocation = 1;
	//glEnableVertexAttribArray(vertexLocation);
	//glEnableVertexAttribArray(colourLocation);

	//// Set vertex data
	//glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, false, sizeof(Vertex), 0);

	//// Set colour data
	//glVertexAttribPointer(colourLocation, 4, GL_FLOAT, false, sizeof(Vertex), (byte*)16);

	//// Draw
	//glDrawArrays(GL_LINE_STRIP, 0, mNumVertices);

	//// Disable vertex attrib array
	//glDisableVertexAttribArray(vertexLocation);
	//glDisableVertexAttribArray(colourLocation);

	//// Unbind buffers
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO_GL::DrawVAO()
{
	glBindVertexArray(mVaoID);
	// Draw
	// glDrawArrays(GL_TRIANGLES, 0, mNumVertices);
	glDrawElements(GL_TRIANGLES, mNumIndices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
#endif