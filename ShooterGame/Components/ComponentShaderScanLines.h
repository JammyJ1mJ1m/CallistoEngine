#pragma once
#include "Components\ComponentShader.h"
class ComponentShaderScanLines : public ComponentShader
{
public:
	ComponentShaderScanLines(Camera* pCam, const char* pVert, const char* pFrag);
	~ComponentShaderScanLines();
	//~ComponentShaderScanLines() = default;
	virtual void Render();
	virtual void Update(glm::mat4 pMat);

};

