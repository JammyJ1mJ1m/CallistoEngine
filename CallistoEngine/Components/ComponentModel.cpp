#include "ComponentModel.h"
#include "../Managers/ResourceManager.h"

ComponentModel::ComponentModel(Mesh* pMesh)
{
	SetMesh(pMesh);
	mMesh->CreateVBO();
}

ComponentModel::ComponentModel(std::string pMesh, std::string pMat, const bool pIsCubemap)
{
		// mMesh = ResourceManager::GetMesh(pMesh);
	ResourceManager& manager = ResourceManager::getInstance();

	Mesh* mesh = manager.LoadMesh(pMesh.c_str());
	mesh->AddMaterial(pMat, pIsCubemap);
	SetMesh(mesh);
	mMesh->CreateVBO();

}

IComponent::ComponentTypes ComponentModel::GetType() const
{
	return ComponentTypes::COMPONENT_MODEL;
}
