#include "SystemLight.h"
#include "ComponentTransform.h"
#include "ComponentShader.h"
#include "../Math/Vector.h"

SystemLight::SystemLight()
{
	mLightManager = &LightManager::GetInstance();
	mMask = ( IComponent::ComponentTypes::COMPONENT_TRANSFORM | IComponent::ComponentTypes::COMPONENT_LIGHT);
}

void SystemLight::Run(Entity* pEntity)
{

	// after spending all day implementing the light manager, light system and light component
	// I realised that I dont actually have a need for this system as I can just pass the lights 
	// list from the light manager to the shader component and update the shader with the lights there

	// Aha, new day new train of thought, I use this system to sync the light pos with the trasnform pos
	// as the refactored manager generates light components rather than entire light entities, I think 
	// its cleaner this way, and I can still use the light manager to get the list of lights




	// =================================================================
	//		grab the list of light entities from the light manager
	// 
	//		manager has a static get all components function
	// =================================================================

	//const std::vector<LightComponent*>& lights = mLightManager->GetLights();


	// we still want to loop through all the normal entities and update the shaders with lights
	IComponent::ComponentTypes type = pEntity->GetMask();
	if ((type & mMask) == mMask)
	{
		ComponentTransform* transform = pEntity->GetComponent<ComponentTransform>();
		Vector3f position = transform->GetPosition();

		LightComponent* light = pEntity->GetComponent<LightComponent>();
		light->GetLight()->SetPosition(position );
	}
}
