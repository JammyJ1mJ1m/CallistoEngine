#include "ComponentShaderSkybox.h"

ComponentShaderSkybox::ComponentShaderSkybox(Camera* pCam, const char* pVert, const char* pFrag)
{
	mCamera = pCam;
#if OPENGL
	mShaderObject = new ShaderObject_GL(pVert, pFrag);
#elif DIRECTX
	mShaderObject = new ShaderObject_DX();
#endif
}



void ComponentShaderSkybox::Render()
{
}

ComponentShaderSkybox::~ComponentShaderSkybox()
{
	delete mShaderObject;
}

void ComponentShaderSkybox::Update(glm::mat4 pMat)
{

	//mShaderObject->SetWorldMatrix("transform", pMat, mCamera);
	// use program
	UseProgram();


	// set model
	//mShaderObject->SetMat4("model", pMat);

	// set view
	glm::mat4 camView = mCamera->GetView();
	glm::mat4 view = glm::mat4(glm::mat3(camView));
	mShaderObject->SetMat4("view", view);

	// set projection
	mShaderObject->SetMat4("projection", mCamera->GetProjection());

}