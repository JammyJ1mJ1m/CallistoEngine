#include "LightComponent.h"

LightComponent::LightComponent(const Light* pLight)
{
    mLightType = pLight->GetType();
	mLight = pLight;
}

IComponent::ComponentTypes LightComponent::GetType() const
{
    return ComponentTypes::COMPONENT_TRANSFORM;
}
