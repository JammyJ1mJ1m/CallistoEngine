#include "ComponentShader.h"

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