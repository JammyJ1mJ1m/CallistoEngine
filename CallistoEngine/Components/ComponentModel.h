#pragma once
#include "IComponent.h"
#include <string>
 #include "../Graphical/Mesh.h"
// #include "../Managers/ResourceManager.h"

class ComponentModel : public IComponent
{
	Mesh* mMesh;
public:
	ComponentModel(Mesh* pMesh);
	ComponentModel(Mesh* pMesh, std::string pMat, const bool pIsCubemap = false );
	// ComponentModel(const std::string pFilePath);
	~ComponentModel() = default;
	virtual ComponentTypes GetType() const;
	const Mesh* GetMesh() { return mMesh; };
	void SetMesh(Mesh* pMesh) { mMesh = pMesh; } ;
};

