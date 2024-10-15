#include "ComponentShaderWindow.h"
#include "Math/Vector.h"
#include <vector>
#include "TestLight.h"
#include "Managers/LightManager.h"

ComponentShaderWindow::ComponentShaderWindow(Camera* pCam, const char* pVert, const char* pFrag)
{
	mCamera = pCam;
#if OPENGL
	mShaderObject = new ShaderObject_GL(pVert, pFrag);
#elif DIRECTX
	mShaderObject = new ShaderObject_DX();
#endif
}



void ComponentShaderWindow::Render()
{
}

ComponentShaderWindow::~ComponentShaderWindow()
{
	delete mShaderObject;
}

void ComponentShaderWindow::Update(glm::mat4 pMat)
{

	//mShaderObject->SetWorldMatrix("transform", pMat, mCamera);
	// use program
	UseProgram();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	// set model
	mShaderObject->SetMat4("model", pMat);

	// set view
	mShaderObject->SetMat4("view", mCamera->GetView());

	// set projection
	mShaderObject->SetMat4("projection", mCamera->GetProjection());

	mShaderObject->SetInt("diffuseTex", 0);
	mShaderObject->SetInt("emissionTex", 1);
	mShaderObject->SetInt("specularMap", 2);

	const std::vector<LightComponent*>& lights = LightManager::GetInstance().GetLights();

	// get all the lights and update
	for (size_t i = 0; i < lights.size(); i++)
	{
		std::string lightPosName = "light[" + std::to_string(i) + "].position";
		std::string lightDiffuseName = "light[" + std::to_string(i) + "].diffuse";
		mShaderObject->SetVec3(lightPosName.c_str(), lights[i]->GetLight()->GetPosition());
		mShaderObject->SetVec3(lightDiffuseName.c_str(), lights[i]->GetLight()->GetDiffuse());
	}

	mShaderObject->SetFloat("time", glfwGetTime());

	//glm::vec3 pos;
	Vector3f pos;
	pos.SetX(mCamera->GetPosition().GetX());
	pos.SetY(mCamera->GetPosition().GetY());
	pos.SetZ(mCamera->GetPosition().GetZ());
	mShaderObject->SetVec3("viewPos", pos);
}