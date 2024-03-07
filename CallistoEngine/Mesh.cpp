#include "Mesh.h"

#if DIRECTX
#include "VBO_DX.h"
#endif
#if OPENGL
#include "VBO_GL.h"

#endif

/******************************************************************************************************************/

Mesh::Mesh()
	: mLocked(false),
	mVbo(NULL)

{
}

/******************************************************************************************************************/

Mesh::~Mesh()
{
	delete mVbo;
	mVbo = NULL;
}

/******************************************************************************************************************/

bool Mesh::AddVertex(Vertex v)
{
	if (!mLocked)
	{
		mVertices.push_back(v);
		return true;
	}
	else
	{
		return false;
	}
}

bool Mesh::AddIndex(int i)
{
	if (!mLocked)
	{
		mIndices.push_back(i);
		return true;
	}
	else
	{
		return false;
	}
}

bool Mesh::AddIndex(int pIndices[], int pSize)
{
	if (!mLocked)
	{
		// int size = sizeof(pIndices);// / sizeof(pIndices[0]);
		for (size_t i = 0; i < pSize; i++)
		{
			mIndices.push_back(pIndices[i]);
		}
		return true;
	}
	else
	{
		return false;
	}
}

/******************************************************************************************************************/

bool Mesh::DeleteVertex(int i)
{
	if (!mLocked)
	{
		mVertices.erase(mVertices.begin() + i);
		return true;
	}
	else
	{
		return false;
	}
}

/******************************************************************************************************************/

bool Mesh::Clear()
{
	if (!mLocked)
	{
		mVertices.clear();
		return true;
	}
	return false;
}

/******************************************************************************************************************/

void Mesh::Reset()
{
	delete mVbo;
	mVbo = NULL;
	mLocked = false;
}

/******************************************************************************************************************/

VBO* Mesh::CreateVBO()
{
	mLocked = true;

#if DIRECTX
	_vbo = new VBO_DX();
#elif OPENGL
	mVbo = new VBO_GL();
#endif

	mVbo->Create(mVertices.data(), NumVertices(), mIndices.data(), mIndices.size());

	return mVbo;
}