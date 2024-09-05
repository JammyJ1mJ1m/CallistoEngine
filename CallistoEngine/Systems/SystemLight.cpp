#include "SystemLight.h"
#include "ComponentTransform.h"
#include "ComponentShader.h"
#include "../Math/Vector.h"
#include "../TestLight.h"
SystemLight::SystemLight()
{
	mLightManager = &LightManager::GetInstance();
	mMask = (IComponent::ComponentTypes::COMPONENT_SHADER | IComponent::ComponentTypes::COMPONENT_MODEL | IComponent::ComponentTypes::COMPONENT_TRANSFORM);
}

void SystemLight::Run(Entity* pEntity)
{

	// after spending all day implementing the light manager, light system and light component
	// I realised that I dont actually have a need for this system as I can just pass the lights 
	// list from the light manager to the shader component and update the shader with the lights there




	// =================================================================
	//		grab the list of light entities from the light manager
	// 
	//		manager has a static get all components function
	// =================================================================

	const std::vector<TestLight*>& lights = mLightManager->GetLights();


	// we still want to loop through all the normal entities and update the shaders with lights
	IComponent::ComponentTypes type = pEntity->GetMask();
	if ((type & mMask) == mMask)
	{
		ComponentTransform* transform = pEntity->GetComponent<ComponentTransform>();
		//glm::mat4 modelMatrix = transform->GetModelMatrix(); 
		Vector3f position = transform->GetPosition();

		ComponentShader* shader = pEntity->GetComponent<ComponentShader>();

		//lights[0]->SetPosition(lights[0]->GetComponent<ComponentTransform>()->GetPosition());
		shader->GetShaderObject()->SetVec3("light.position", lights[0]->GetComponent<ComponentTransform>()->GetPosition());
		shader->GetShaderObject()->SetVec3("light.diffuse", Vector3f(1,0,1));



		// sends over the uniforms, MVP etc
		//shader->Update(modelMatrix);
		//mRenderer->Render(pEntity);
	}
}
