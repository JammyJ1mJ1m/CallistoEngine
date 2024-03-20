#pragma once

#include "VBO.h"
#include <vector>
#include "Material.h"


class Mesh final
{
public:

	// Data
private:
	bool mLocked;	// True once we've made the VBO; can no longer add vertices etc unless reset
	VBO* mVbo;
	std::vector<Vertex> mVertices;
	std::vector<int> mIndices;

	int textures;

	Material* material;

	// Constructors etc
public:
	Mesh(std::string pFile);
	Mesh();
	~Mesh();

	// Gets/sets
public:
	VBO* GetVBO()			const { return mVbo; }
	int NumVertices()		const { return (int)mVertices.size(); }
	Vertex GetVertex(int i)	const { return mVertices[i]; }
	Vertex& GetVertexRef(int i) { return mVertices[i]; }

	// Functions
public:
	VBO* CreateVBO();
	bool AddVertex(Vertex v);
	bool AddVertices(std::vector<Vertex> v);
	bool AddVertices(Vertex v);
	bool AddIndex(int i);
	bool AddIndex(std::vector<int> pIndices);
	bool AddMaterial(std::string pMat);
	bool AddIndex(int pIndices[], int pSize);
	bool Clear();
	bool DeleteVertex(int i);
	void LoadTexture(std::string pFile);
	void Draw() const;

	// Unlocks the mesh but also deletes the VBO
	void Reset();
};

