#pragma once
#include "Components\ComponentShader.h"
#include "Camera.h"
class ComponentShaderDefault : public ComponentShader
{
public:
	ComponentShaderDefault(Camera* pCam, const char* pVert, const char* pFrag);
	~ComponentShaderDefault();
	//~ComponentShaderDefault() = default;
	virtual void Render();
	virtual void Update(glm::mat4 pMat);

};

