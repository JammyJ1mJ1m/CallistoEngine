#pragma once
#include "IComponent.h"
#include <string>

class ComponentModel : public IComponent
{
public:
	ComponentModel() = default;
	// ComponentModel(const std::string pFilePath);
	~ComponentModel() = default;
	virtual ComponentTypes GetType() const;

};

