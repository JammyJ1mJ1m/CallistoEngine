#include "SystemRenderDeferred.h"
#include "ComponentTransform.h"
#include "ComponentShader.h"
#include "../Game.h"
#include "../Graphical/GBuffer.h"
#include "../Graphical/MainRenderTarget.h"
#include "../Lighting/PointLight.h"

SystemRenderDeferred::SystemRenderDeferred(Renderer* pRenderer)
{
	mRenderer = pRenderer;
	mMask = (IComponent::ComponentTypes::COMPONENT_SHADER | IComponent::ComponentTypes::COMPONENT_MODEL | IComponent::ComponentTypes::COMPONENT_TRANSFORM);
	mMask = IComponent::ExcludeComponent(mMask, IComponent::ComponentTypes::COMPONENT_SHADER);

	mLightingShader = new ShaderObject_GL("Resources/Shaders/deferredLighting.vert", "Resources/Shaders/deferredLighting.frag");
	mLightingShader->UseProgram();
	mLightingShader->SetInt("gPosition", 0);
	mLightingShader->SetInt("gNormal", 1);
	mLightingShader->SetInt("gAlbedoSpec", 2);
}

void SystemRenderDeferred::Run(Entity* pEntity)
{
	IComponent::ComponentTypes t = pEntity->GetMask();

	// We do not want to proceed if the entity has a shader, we will assume that if it does contain a shader
	// it requires a more specific shader approach ( transparency, light objects etc) in a forward renderer    
	//                           
	if(IComponent::HasComponent(t, IComponent::ComponentTypes::COMPONENT_SHADER))
		return;
	if ((t & mMask) == mMask)
	{
		//################################################################
		//	  fill out the g buffer with position, normal and colour
		//################################################################

		ComponentTransform* transform = pEntity->GetComponent<ComponentTransform>();
		glm::mat4 modelMatrix = transform->GetModelMatrix();

		GBuffer* gBuffer = mRenderer->GetGBuffer();
		gBuffer->GetShader()->SetMat4("model", modelMatrix);
		//gBuffer->GetShader()->SetVec3("viewPos", Game::GetGame()->GetGameCamera()->GetPosition());

		mRenderer->Render(pEntity);

	}
}
void SystemRenderDeferred::RunLighting()
{
	mRenderer->UnbindFrame();
	//mRenderer->ClearScreen();
	mRenderer->GetMainTarget()->Activate();
	mRenderer->ClearScreen();
	//################################################################
	//					 render the lights
	//################################################################
	mLightingShader->UseProgram();
	mRenderer->GetGBuffer()->BindTextures();

	mLightingShader->SetVec3("viewPos", Game::GetGame()->GetGameCamera()->GetPosition());

	const std::vector<LightComponent*>& lights = LightManager::GetInstance().GetLights();
	float linear = 0.07f;
	float quadratic = 0.017f;
	// get all the lights and update
	for (size_t i = 0; i < lights.size(); i++)
	{
		std::string lightPosName = "lights[" + std::to_string(i) + "].Position";
		std::string lightDiffuseName = "lights[" + std::to_string(i) + "].Color";

		mLightingShader->SetVec3(lightPosName.c_str(),		lights[i]->GetLight()->GetPosition());
		Vector3f col = lights[i]->GetLight()->GetDiffuse();
		mLightingShader->SetVec3(lightDiffuseName.c_str(),	lights[i]->GetLight()->GetDiffuse());

		std::string LightLinearName = "lights[" + std::to_string(i) + "].Linear";
		std::string LightQuadName = "lights[" + std::to_string(i) + "].Quadratic";

		if (lights[i]->GetLight()->GetType() == LightType::POINT)
		{
			PointLight* instance = static_cast<PointLight*>(lights[i]->GetLight());
			linear = instance->GetLinear();
			quadratic = instance->GetQuadratic();
		}
		mLightingShader->SetFloat(LightLinearName.c_str(), linear);
		mLightingShader->SetFloat(LightQuadName.c_str(), quadratic);

	}

	
	 mRenderer->RenderScreenQuad();
	 mRenderer->UnbindFrame();
	 mRenderer->SetFrame(mRenderer->GetMainTarget()->GetTextureID());
	// output the results to a texture - mMaintarget

	//mLightingShader->SetVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
	//mLightingShader->SetVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);
	//// update attenuation parameters and calculate radius
	//const float linear = 0.09f;
	//const float quadratic = 0.032f;
	//mLightingShader->SetFloat("lights[" + std::to_string(i) + "].Linear", linear);
	//mLightingShader->SetFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
}

void SystemRenderDeferred::CopyBuffer(const int pCopyFrom, const int pCopyTo)
{
	mRenderer->CopyBuffer(pCopyFrom, pCopyTo);
}


void SystemRenderDeferred::Begin()
{
	mRenderer->Begin();
	//mRenderer->ClearScreen();
}

void SystemRenderDeferred::End()
{
	mRenderer->End();
}

void SystemRenderDeferred::PostProcess()
{
	mRenderer->Postprocess();
}

