#include "ComponentShaderDefault.h"
#include "Math/Vector.h"
#include <vector>
#include "TestLight.h"
#include "Managers/LightManager.h"

ComponentShaderDefault::ComponentShaderDefault(Camera* pCam, const char* pVert, const char* pFrag)
{
	mCamera = pCam;
#if OPENGL
	mShaderObject = new ShaderObject_GL(pVert, pFrag);
#elif DIRECTX
	mShaderObject = new ShaderObject_DX();
#endif
}



void ComponentShaderDefault::Render()
{
}

ComponentShaderDefault::~ComponentShaderDefault()
{
	delete mShaderObject;
}

void ComponentShaderDefault::Update(glm::mat4 pMat)
{

	//mShaderObject->SetWorldMatrix("transform", pMat, mCamera);
	// use program
	UseProgram();


	// set model
	mShaderObject->SetMat4("model", pMat);

	// set view
	mShaderObject->SetMat4("view", mCamera->GetView());
		
	// set projection
	mShaderObject->SetMat4("projection", mCamera->GetProjection());

	const std::vector<LightComponent*>& lights = LightManager::GetInstance().GetLights();

	mShaderObject->SetVec3("light.position", lights[0]->GetLight()->GetPosition());
	mShaderObject->SetVec3("light.diffuse", Vector3f(1, 1, 1));

	//glm::vec3 pos;
	Vector3f pos;
	pos.SetX(mCamera->GetPosition().GetX());
	pos.SetY( mCamera->GetPosition().GetY());
	pos.SetZ( mCamera->GetPosition().GetZ());
	mShaderObject->SetVec3("viewPos", pos);
}