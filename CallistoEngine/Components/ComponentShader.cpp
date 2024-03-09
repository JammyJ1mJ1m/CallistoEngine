#include "ComponentShader.h"

ComponentShader::ComponentShader()
{

#if OPENGL
	mShaderObject = new ShaderObject_GL();
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
