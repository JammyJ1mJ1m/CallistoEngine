#include "PostProcessEffect.h"

#include "Renderer_GL.h"
#include "../Game.h"

void PostProcessEffect::Create()
{
	target = new RenderTarget();
}

void PostProcessEffect::Render()
{
	target->Activate();
	shader->UseProgram();

	////Set shader variables
	OnActivate();
	shader->SetFloat("width", Game::GetGame()->GetGameCamera()->mWidth);

	//shader->SetFloat("albedo", 0);
	//shader->SetFloat("depth", 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Renderer_GL::GetInstance().GetFrame());

	if (usesDepth)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Renderer_GL::GetInstance().GetDepth());
	}

	Renderer_GL::GetInstance().RenderScreenQuad();
	target->BindTextures();
}

void PostProcessEffect::Resize(int width, int height)
{
	target->Resize(width, height);
}

void PostProcessEffect::SetTarget(RenderTarget* target)
{
	delete this->target;
	this->target = target;
}

PostProcessEffect::PostProcessEffect(const char* shader) : target(nullptr)
{
	//this->shader = AssetManager::Instance().GetShader(shader);
	//screenQuad = AssetManager::Instance().GetModel("Assets/Models/plane.obj");
}

PostProcessEffect::~PostProcessEffect()
{
	delete target;
}

void PostProcessEffect::LoadShader(const char* pVertexPath, const char* pFragPath, const char* pShaderID)
{
	ResourceManager& RM = ResourceManager::getInstance();
	//std::string vertexShader = RM.LoadShader(pVertexPath);
	//std::string fragShader = RM.LoadShader(pFragPath);

	shader = RM.CreateShader(pVertexPath, pFragPath, pShaderID);
	//shader = new ShaderObject_GL(vertexShader.c_str(), fragShader.c_str());
}
