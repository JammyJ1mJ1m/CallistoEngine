#pragma once
#include "IComponent.h"
#include "../Objects/ShaderObject.h"

#if OPENGL
#include "../Objects/ShaderObject_GL.h"
#include "../Camera.h"
#elif DIRECTX
#include "../Objects/ShaderObject_DX.h"
#endif



// default engine shader component, no lights and will attempt textures
class ComponentShader : public IComponent
{
protected:
	ShaderObject* mShaderObject;
	Camera* mCamera;

	const virtual void UseProgram();
public:
	ComponentShader(Camera* pCam);
	virtual ComponentTypes GetType() const;
	void Render();

	// void Create(const char* pVertexShader, const char* pFragmentShader);
	virtual ~ComponentShader();
	void Update(glm::mat4 pMat);

};

