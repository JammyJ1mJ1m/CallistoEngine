#include "Renderer_GL.h"
#include "Components/ComponentModel.h"
#include "Components/ComponentShader.h"

void Renderer_GL::ClearScreen()
{
	glClearColor(_clearColour.GetX(), _clearColour.GetY(), _clearColour.GetZ(), _clearColour.GetW() );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer_GL::Destroy()
{
	
}

void Renderer_GL::Initialise(int width, int height)
{
 

}

void Renderer_GL::SwapBuffers()
{

}

void Renderer_GL::Render(Entity* entity)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// glUseProgram(shaderProgram);


	ComponentModel* model = entity->GetComponent <ComponentModel>();
	const Mesh* mesh = model->GetMesh();
	mesh->Draw();

}
