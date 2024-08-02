#pragma once
#include "Material.h"
#include "Vertex.h"

class VBO
{
	// Data
protected:
	int _numVertices;

	// Constructors
public:
	VBO();
	virtual ~VBO();

	// Functions
	virtual void Create(Vertex pVertices[], int pNumVertices, int pIndices[], int pSize) = 0;
	virtual void Draw(Material* mat) = 0;
};

