#include "ComponentModel.h"
#include "../Managers/ResourceManager.h"

ComponentModel::ComponentModel(Mesh* pMesh)
{

	SetMesh(pMesh);
	/*

	-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	*/


	mMesh->CreateVBO();
}

ComponentModel::ComponentModel(std::string pMesh, std::string pMat)
{
		// mMesh = ResourceManager::GetMesh(pMesh);
	ResourceManager& manager = ResourceManager::getInstance();

	Mesh* mesh = manager.LoadMesh(pMesh.c_str());
	mesh->AddMaterial(pMat);
	SetMesh(mesh);
	mMesh->CreateVBO();

}

IComponent::ComponentTypes ComponentModel::GetType() const
{
	return ComponentTypes::COMPONENT_MODEL;
}
