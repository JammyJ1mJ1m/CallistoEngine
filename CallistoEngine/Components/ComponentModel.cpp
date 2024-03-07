#include "ComponentModel.h"

ComponentModel::ComponentModel()
{
	/*

	-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	*/
	mMesh.AddVertex({ Vector3(-0.5f, -0.5f, 0.0f) });
	mMesh.AddVertex({ Vector3(0.5f, -0.5f, 0.0f) });
	mMesh.AddVertex({ Vector3(0.0f, 0.5f, 0.0f) });

	mMesh.CreateVBO();
}

IComponent::ComponentTypes ComponentModel::GetType() const
{
	return ComponentTypes::COMPONENT_MODEL;
}
