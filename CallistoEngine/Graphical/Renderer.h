#pragma once

// GLM


//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"

#include "../Math/Vector.h"

// Forward declarations
class Entity;

// Platform independent renderer base class
// Basically represents a graphics context and its active shaders
class Renderer
{
	// Data
protected:
	 Vector4f _clearColour;
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

	virtual void Render(Entity* entity) = 0;
	virtual void Initialise(int width, int height) = 0;
	virtual void Destroy() = 0;
	virtual void ClearScreen() = 0;
	virtual void SwapBuffers() = 0;

};
