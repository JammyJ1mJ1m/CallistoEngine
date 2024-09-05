#pragma once
#include "IComponent.h"
#include "../Lighting/Light.h"



class LightComponent : public IComponent
{
	LightType mLightType;
	const Light* mLight;

public:
	LightComponent(const Light* pLight);
	//LightComponent() = default;
	~LightComponent() { delete mLight; };

	virtual ComponentTypes GetType() const;
};

