#pragma once
#include "IComponent.h"
#include "../Objects/ShaderObject.h"

#if OPENGL
#include "../Objects/ShaderObject_GL.h"
#include "../Camera.h"
#elif DIRECTX
#include "../Objects/ShaderObject_DX.h"
#endif

class ComponentShader : public IComponent
{
	ShaderObject* mShaderObject;
	Camera* mCamera;


public:
	ComponentShader(Camera* pCam);
	virtual ComponentTypes GetType() const;
	void Render();
	const virtual void UseProgram();

	// void Create(const char* pVertexShader, const char* pFragmentShader);
	virtual ~ComponentShader();
	void Update(glm::mat4 pMat);
};

