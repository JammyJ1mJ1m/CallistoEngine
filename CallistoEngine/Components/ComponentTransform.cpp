#include "ComponentTransform.h"
#include "GLM/gtx/quaternion.hpp"

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
	GetWorld();
}

//void ComponentTransform::UpdateModelMatrix(const glm::mat4& pParentMat)
//{
//	modelMatrix =  modelMatrix * pParentMat;
//	// set the new position
//	position = glm::vec3(modelMatrix[3]);
//}


void ComponentTransform::UpdateModelMatrix(const glm::mat4& pParentMat)
{
	// Compute the local transformation matrix
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
	glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
	glm::mat4 scaling = glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 localMatrix = translation * rotationZ * rotationY * rotationX * scaling;

	
		// Compute the world matrix by combining the parent's world matrix with the local matrix
		modelMatrix = pParentMat * localMatrix;
	
	
	
}

void ComponentTransform::Translate(glm::vec3 pTranslation)
{
	modelMatrix = glm::translate(modelMatrix, pTranslation);
	UpdateModelMatrix();
}

void ComponentTransform::RotateX(const float pAngle)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(pAngle), glm::vec3(1,0,0));
	UpdateModelMatrix();
}

void ComponentTransform::RotateY(const float pAngle)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(pAngle), glm::vec3(0, 1, 0));
	UpdateModelMatrix();

}

void ComponentTransform::RotateZ(const float pAngle)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(pAngle), glm::vec3(0, 0, 1));
	UpdateModelMatrix();

}

void ComponentTransform::Scale(glm::vec3 pScale)
{
	modelMatrix = glm::scale(modelMatrix, pScale);
	UpdateModelMatrix();

}

void ComponentTransform::GetWorld()
{
	//TODO re implement this with a returned mat4

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix *= glm::mat4(glm::quat(rotation));
	modelMatrix *= glm::scale(modelMatrix, scale);
}

void ComponentTransform::SyncTransform(const btTransform& pTransform)
{
	btVector3 bulletPosition = pTransform.getOrigin();
	position = glm::vec3(bulletPosition.getX(), bulletPosition.getY(), bulletPosition.getZ());

	btQuaternion bulletRotation = pTransform.getRotation();
	rotation = glm::eulerAngles(glm::quat(bulletRotation.getW(), bulletRotation.getX(), bulletRotation.getY(), bulletRotation.getZ()));

	UpdateModelMatrix();	
}


IComponent::ComponentTypes ComponentTransform::GetType() const
{
	return ComponentTypes::COMPONENT_TRANSFORM;
}