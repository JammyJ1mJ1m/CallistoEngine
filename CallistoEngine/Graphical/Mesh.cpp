#include "Mesh.h"

#if DIRECTX
#include "VBO_DX.h"
#endif
#if OPENGL
#include "VBO_GL.h"
#include "../Managers/ResourceManager.h"
#endif

/******************************************************************************************************************/


Mesh::Mesh(const Mesh& other)
	: mLocked(other.mLocked),
	mVbo(other.mVbo),                // Point to the same VBO
	mVertices(other.mVertices),
	mIndices(other.mIndices),
	textures(other.textures)
{
	material = nullptr;
}

Mesh::Mesh(std::string pFile)
	: mLocked(false),
	mVbo(NULL)

{
	material = new Material(pFile);
}

Mesh::Mesh() : mLocked(false), mVbo(NULL)
{
}

/******************************************************************************************************************/

Mesh::~Mesh()
{
	delete mVbo;
	mVbo = NULL;
	delete material;
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

bool Mesh::AddVertices(std::vector<Vertex> v)
{
	if (!mLocked)
	{
		// int size = sizeof(pIndices);// / sizeof(pIndices[0]);
		for (size_t i = 0; i < v.size(); i++)
		{
			mVertices.push_back(v[i]);
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Mesh::AddVertices(Vertex v)
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

bool Mesh::AddIndex(std::vector<int> pIndices)
{
	if (!mLocked)
	{
		// int size = sizeof(pIndices);// / sizeof(pIndices[0]);
		for (size_t i = 0; i < pIndices.size(); i++)
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

bool Mesh::AddMaterial(std::string pMat)
{
	material = new Material(pMat);

	return false;
}
bool Mesh::AddMaterial(std::string pMat, const bool pIsCubemap)
{
	material = new Material(pMat, pIsCubemap);

	return false;
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

void Mesh::LoadTexture(std::string pFile)
{
	ResourceManager& manager = ResourceManager::getInstance();

	textures = manager.LoadTexture(pFile.c_str());
	// const char* vertexShaderSource = vshaderSrc.c_str();
}

void Mesh::Draw() const
{
	glDepthFunc(GL_TRUE);
	material->Draw();
	GetVBO()->Draw(material);
	glDepthFunc(GL_LESS);

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