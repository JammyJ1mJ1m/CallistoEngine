#pragma once
#include "Components\ComponentShader.h"
#include "Misc/Camera.h"
class ComponentShaderWindow : public ComponentShader
{
public:
	ComponentShaderWindow(Camera* pCam, const char* pVert, const char* pFrag);
	~ComponentShaderWindow();
	//~ComponentShaderWindow() = default;
	virtual void Render();
	virtual void Update(glm::mat4 pMat);

};

