#include "ComponentTransform.h"

ComponentTransform::ComponentTransform()
{
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	modelMatrix = glm::mat4(1.0f);
	UpdateModelMatrix();
}

ComponentTransform::ComponentTransform(glm::vec3 pPos, glm::vec3 pRot, glm::vec3 pScale )
{
	position = pPos;
	rotation = pRot;
	scale = pScale;
	modelMatrix = glm::mat4(1.0f);
	UpdateModelMatrix();
}

void ComponentTransform::UpdateModelMatrix()
{
	Translate(position);
	Rotate(rotation);
	Scale(scale);
}

void ComponentTransform::Translate(glm::vec3 pTranslation)
{
	modelMatrix = glm::translate(modelMatrix, pTranslation);
}

void ComponentTransform::Rotate(glm::vec3 pAxis)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(0.0f), pAxis);
}

void ComponentTransform::Scale(glm::vec3 pScale)
{
	modelMatrix = glm::scale(modelMatrix, pScale);
}


IComponent::ComponentTypes ComponentTransform::GetType() const
{
	return ComponentTypes::COMPONENT_TRANSFORM;
}