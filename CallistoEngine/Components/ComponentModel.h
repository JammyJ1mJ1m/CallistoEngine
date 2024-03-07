#pragma once
#include "IComponent.h"
#include <string>
#include "../Mesh.h"

class ComponentModel : public IComponent
{
	Mesh* mMesh;
public:
	ComponentModel(Mesh* pMesh);
	// ComponentModel(const std::string pFilePath);
	~ComponentModel() = default;
	virtual ComponentTypes GetType() const;
	const Mesh* GetMesh() { return mMesh; };
	void SetMesh(Mesh* pMesh) { mMesh = pMesh; } ;
};

