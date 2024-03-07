#pragma once
#include "Vector3.h"
#include "VBO.h"
#include <vector>


class Mesh final
{
public:

	// Data
private:
	bool mLocked;	// True once we've made the VBO; can no longer add vertices etc unless reset
	VBO* mVbo;
	std::vector<Vertex> mVertices;
	std::vector<int> mIndices;

	// Constructors etc
public:
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
	bool AddIndex(int i);
	bool AddIndex(int pIndices[], int pSize);
	bool Clear();
	bool DeleteVertex(int i);

	// Unlocks the mesh but also deletes the VBO
	void Reset();
};

