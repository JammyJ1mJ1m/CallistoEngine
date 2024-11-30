#include "ComponentShader.h"

IComponent::ComponentTypes ComponentShader::GetType() const
{
	return ComponentTypes::COMPONENT_SHADER;
}

void ComponentShader::Render()
{
}

void ComponentShader::OnMessage(Message* msg)
{
}

const void ComponentShader::UseProgram()
{
	mShaderObject->UseProgram();
}