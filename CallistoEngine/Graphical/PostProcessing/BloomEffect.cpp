#include "BloomEffect.h"
#include "../Renderer_GL.h"
void BloomEffect::OnActivate()
{
    //For bloom, we need the gaussian texture from the last stage, but
    //we also need the raw image from the main target. Since we don't care about
    //the depth buffer, we can bind the raw image over it instead
    //shader->SetInt("scene", 0);
    //glActiveTexture(GL_TEXTURE0);
    shader->SetInt("scene", 1);


    unsigned int id = Renderer_GL::GetInstance().GetRawFrame();
    //if (id == 0)
    //    id = PipelineManager::Instance().GetRawFrame();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, id);
}
