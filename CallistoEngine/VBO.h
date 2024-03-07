#pragma once
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
	virtual void Create(Vertex vertices[], int numVertices) = 0;
	virtual void Draw() = 0;
};

