#pragma once

#include "Mesh.h"

// GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Forward declarations
class GameObject;

// Platform independent renderer base class
// Basically represents a graphics context and its active shaders
class Renderer
{
	// Data
protected:
	// Colour	_clearColour;
public:

	// Structors
public:
	Renderer();
	virtual ~Renderer();

	// Gets/sets
public:

	// Functions
public:
	// virtual void Draw(const Mesh* mesh, glm::mat4 MVM) = 0;
	// virtual void Draw(GameObject* gob, glm::mat4 MVM);

	virtual void Initialise(int width, int height) = 0;
	virtual void Destroy() = 0;
	virtual void ClearScreen() = 0;
	virtual void SwapBuffers() = 0;

};

