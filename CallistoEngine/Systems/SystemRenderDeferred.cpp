#include "SystemRenderDeferred.h"
#include "ComponentTransform.h"
#include "ComponentShader.h"
#include "../Game.h"
#include "../Graphical/GBuffer.h"
SystemRenderDeferred::SystemRenderDeferred(Renderer* pRenderer)
{
	mRenderer = pRenderer;
	mMask = (IComponent::ComponentTypes::COMPONENT_SHADER | IComponent::ComponentTypes::COMPONENT_MODEL | IComponent::ComponentTypes::COMPONENT_TRANSFORM);
	mLightingShader = new ShaderObject_GL("Resources/Shaders/deferredLighting.vert", "Resources/Shaders/deferredLighting.frag");
	mLightingShader->UseProgram();
	mLightingShader->SetInt("gPosition", 0);
	mLightingShader->SetInt("gNormal", 1);
	mLightingShader->SetInt("gAlbedoSpec", 2);
}

void SystemRenderDeferred::Run(Entity* pEntity)
{
	IComponent::ComponentTypes t = pEntity->GetMask();
	if ((t & mMask) == mMask)
	{
		//################################################################
		//	  fill out the g buffer with position, normal and colour
		//################################################################

		ComponentTransform* transform = pEntity->GetComponent<ComponentTransform>();
		glm::mat4 modelMatrix = transform->GetModelMatrix();


		// get the gBuffer shader
		GBuffer* gBuffer = mRenderer->GetGBuffer();
		//// send the projection mat
		//gBuffer->GetShader()->SetMat4("projection", Game::GetGame()->GetGameCamera()->GetProjection());
		//// send the view mat
		//gBuffer->GetShader()->SetMat4("view", Game::GetGame()->GetGameCamera()->GetView());
		// send each models mat
		gBuffer->GetShader()->SetMat4("model", modelMatrix);

		mRenderer->Render(pEntity);

	}
}
void SystemRenderDeferred::RunLighting()
{
	mRenderer->UnbindFrame();
	mRenderer->ClearScreen();
	//################################################################
	//					 render the lights
	//################################################################
	mLightingShader->UseProgram();
	mRenderer->GetGBuffer()->BindTextures();

	const std::vector<LightComponent*>& lights = LightManager::GetInstance().GetLights();
	const float linear = 0.0014f;
	const float quadratic = 0.000007f;
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

		mLightingShader->SetFloat(LightLinearName.c_str(), linear);
		mLightingShader->SetFloat(LightQuadName.c_str(), quadratic);

	}
	mLightingShader->SetVec3("viewPos", Game::GetGame()->GetGameCamera()->GetPosition());

	mRenderer->RenderScreenQuad();

	//mLightingShader->SetVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
	//mLightingShader->SetVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);
	//// update attenuation parameters and calculate radius
	//const float linear = 0.09f;
	//const float quadratic = 0.032f;
	//mLightingShader->SetFloat("lights[" + std::to_string(i) + "].Linear", linear);
	//mLightingShader->SetFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
}
//void SystemRenderDeferred::DrawPP()
//{
//	mRenderer->DrawPP();
//}

void SystemRenderDeferred::Begin()
{
	mRenderer->Begin();
}

void SystemRenderDeferred::End()
{
	mRenderer->End();
}

void SystemRenderDeferred::PostProcess()
{
	mRenderer->Postprocess();
}

