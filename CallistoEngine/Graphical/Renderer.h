#pragma once

// GLM


//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"

#include "../Math/Vector.h"
#include "GBuffer.h"

// Forward declarations
class Entity;
class PostProcessEffect;
class MainRenderTarget;

// Platform independent renderer base class
// Basically represents a graphics context and its active shaders
class Renderer
{

	// Data
protected:
	static Renderer* mInstance;
	Vector4f _clearColour;

public:

	virtual MainRenderTarget* GetMainTarget() = 0;
	virtual void SetFrame(unsigned int f) = 0;;
	virtual unsigned int GetFrame() const = 0;
	// virtual void SetPixelated(unsigned int b) = 0;
	// virtual unsigned int GetPixelated() const = 0;
	virtual inline unsigned int GetRawFrame() const = 0;
	virtual unsigned int GetDepth() const = 0;
	virtual void RenderScreenQuad() = 0;
	virtual void UnbindFrame() = 0;
	virtual void AddEffect(PostProcessEffect* effect) = 0;


	//Renderer();
	virtual ~Renderer();

	// Gets/sets
public:

	// Functions
public:
	// virtual void Draw(const Mesh* mesh, glm::mat4 MVM) = 0;
	// virtual void Draw(GameObject* gob, glm::mat4 MVM);

	// Renders a frame
	virtual void Render(Entity* entity) = 0;
	// Use to setup initial rendering settings
	virtual void Initialise(int width, int height) = 0;
	// Clears the depth and colour bits
	virtual void ClearScreen() = 0;
	// Called when window size changes
	virtual void Resize(int W, int H) = 0;

	virtual void Begin() = 0;
	virtual void End() = 0;
	virtual void BeginForward() = 0;
	virtual void EndForward() = 0;
	virtual void Postprocess() = 0;
	virtual void CopyBuffer(const int pCopyFrom, const int pCopyTo) = 0;

	// use this once at the start of the frame to clear / bind everything thats needed
	//virtual void StartPP() = 0;
	virtual GBuffer* GetGBuffer() = 0;
};

