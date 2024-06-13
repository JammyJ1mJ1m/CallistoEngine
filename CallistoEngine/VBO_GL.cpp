#if OPENGL
#include "VBO_GL.h"
#include "stddef.h"
#include "cstddef"
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


void VBO_GL::Create(Vertex pVertices[], int pNumVertices, int* pIndices, int pSize)
{
	mNumVertices = pNumVertices;
	mNumIndices = pSize;

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &mVaoID);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &mVboID);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(mVaoID);

	glBindBuffer(GL_ARRAY_BUFFER, mVboID);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * pNumVertices, pVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mNumIndices, &pIndices[0], GL_STATIC_DRAW);

	// position 

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)0);

	//// colors
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	// textures
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,TexCoords));

	// normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,Normal));


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// sets culling mode
	 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void VBO_GL::Draw(Material* mat)
{
	DrawVAO(mat);
}

void VBO_GL::DrawVBO()
{
}

void VBO_GL::DrawVAO(Material* mat)
{
	glBindVertexArray(mVaoID);
	// Draw
	// glDrawArrays(GL_TRIANGLES, 0, mNumVertices);
	// glDrawElements(GL_TRIANGLES, mNumIndices, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, mNumIndices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
#endif