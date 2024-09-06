#pragma once
#include "IComponent.h"
#include "../Lighting/Light.h"



class LightComponent : public IComponent
{
	LightType mLightType;
	Light* mLight;

public:
	LightComponent(Light* pLight);
	//LightComponent() = default;
	~LightComponent() { delete mLight; };
	Light* GetLight() const { return mLight; };

	virtual ComponentTypes GetType() const;
};

