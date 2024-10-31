#include "SystemRenderForward.h"
#include "ComponentTransform.h"
#include "ComponentShader.h"
#include "../Misc/Camera.h"

SystemRenderForward::SystemRenderForward(Renderer* pRenderer)
{
	mRenderer = pRenderer;
	mMask = (IComponent::ComponentTypes::COMPONENT_SHADER | IComponent::ComponentTypes::COMPONENT_MODEL | IComponent::ComponentTypes::COMPONENT_TRANSFORM);
}

void SystemRenderForward::Run(Entity* pEntity)
{
	IComponent::ComponentTypes t = pEntity->GetMask();
	if ((t & mMask) == mMask)
	{

		ComponentTransform* transform = pEntity->GetComponent<ComponentTransform>();
		glm::mat4 modelMatrix = transform->GetModelMatrix(); 

		ComponentShader* shader = pEntity->GetComponent<ComponentShader>();

		// sends over the uniforms, MVP etc
		shader->Update(modelMatrix);
		mRenderer->Render(pEntity);
	}
}

//void SystemRender::DrawPP()
//{
//	mRenderer->DrawPP();
//}

void SystemRenderForward::Begin()
{
	mRenderer->BeginForward();
}

void SystemRenderForward::End()
{
	mRenderer->EndForward();
}

void SystemRenderForward::PostProcess()
{
	mRenderer->Postprocess();
}

