#include "ComponentShaderError.h"

ComponentShaderError::ComponentShaderError(Camera* pCam, const char* pVert, const char* pFrag)
{
	mCamera = pCam;
#if OPENGL
	mShaderObject = new ShaderObject_GL(pVert, pFrag);
#elif DIRECTX
	mShaderObject = new ShaderObject_DX();
#endif
}



void ComponentShaderError::Render()
{
}

ComponentShaderError::~ComponentShaderError()
{
	delete mShaderObject;
}

void ComponentShaderError::Update(glm::mat4 pMat)
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

	mShaderObject->SetFloat("fTime", glfwGetTime());

}