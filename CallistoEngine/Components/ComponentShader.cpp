#include "ComponentShader.h"

ComponentShader::ComponentShader( Camera* pCam, const char* pVert, const char* pFrag)
{
	mCamera = pCam;
#if OPENGL
	mShaderObject = new ShaderObject_GL(pVert, pFrag);
#elif DIRECTX
	mShaderObject = new ShaderObject_DX();
#endif
}

IComponent::ComponentTypes ComponentShader::GetType() const
{
	return ComponentTypes::COMPONENT_SHADER;
}

void ComponentShader::Render()
{
}

const void ComponentShader::UseProgram()
{
	mShaderObject->UseProgram();
}

ComponentShader::~ComponentShader()
{
	delete mShaderObject;
}

void ComponentShader::Update(glm::mat4 pMat)
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

}