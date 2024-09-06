#include "LightComponent.h"

LightComponent::LightComponent(Light* pLight)
{
    mLightType = pLight->GetType();
	mLight = pLight;
}

IComponent::ComponentTypes LightComponent::GetType() const
{
    return ComponentTypes::COMPONENT_LIGHT;
}
