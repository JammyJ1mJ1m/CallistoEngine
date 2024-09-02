#pragma once
#include "IComponent.h"
#include "../Objects/ShaderObject.h"

#if OPENGL
#include "../Objects/ShaderObject_GL.h"
#include "../Misc/Camera.h"
#elif DIRECTX
#include "../Objects/ShaderObject_DX.h"
#endif



// default engine shader component, no lights and will attempt textures
class ComponentShader : public IComponent
{
protected:
	ShaderObject* mShaderObject;
	Camera* mCamera;

	const void UseProgram();
	virtual ComponentTypes GetType() const;
	//ComponentShader() = default;

public:
	//virtual ComponentShader(Camera* pCam, const char* pVert, const char* pFrag) = 0;

	
	virtual ~ComponentShader() = default;
	virtual void Render() = 0;
	virtual void Update(glm::mat4 pMat) = 0;

};