#pragma once
#include "Components\ComponentShader.h"
#include "Misc/Camera.h"
class ComponentShaderDefault : public ComponentShader
{
public:
	ComponentShaderDefault(Entity* pParent, Camera* pCam, const char* pVert, const char* pFrag);
	~ComponentShaderDefault();
	//~ComponentShaderDefault() = default;
	virtual void Render();
	virtual void Update(glm::mat4 pMat);

};

