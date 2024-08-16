#pragma once
#include "Components\ComponentShader.h"
class ComponentShaderError : public ComponentShader
{
public:
	ComponentShaderError(Camera* pCam, const char* pVert, const char* pFrag);
	~ComponentShaderError();
	//~ComponentShaderDefault() = default;
	virtual void Render();
	virtual void Update(glm::mat4 pMat);

};

