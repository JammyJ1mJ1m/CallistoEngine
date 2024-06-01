#pragma once
#include "Components\ComponentShader.h"
class ComponentShaderSkybox : public ComponentShader
{
public:
	ComponentShaderSkybox(Camera* pCam, const char* pVert, const char* pFrag);
	~ComponentShaderSkybox();
	//~ComponentShaderSkybox() = default;
	virtual void Render();
	virtual void Update(glm::mat4 pMat);
};

