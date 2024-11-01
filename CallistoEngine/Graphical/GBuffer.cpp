#include <iostream>
#include "GBuffer.h"

#define EXISTS(buffer) buffer > 0

//void GBuffer::Activate()
//{
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
GBuffer::GBuffer() :
    mGFBO(0),
    mPositionTexture(0),
    mNormalTexture(0),
    mAlbedoSpecTexture(0),
    mDepthTexture(0)
{
        mGeometryPassShader = new ShaderObject_GL("Resources/Shaders/gbuffer.vert", "Resources/Shaders/gbuffer.frag");
}

GBuffer::~GBuffer()
{
    Free();
}

void GBuffer::Free()
{
    if (EXISTS(mGFBO))
    {
        glDeleteFramebuffers(1, &mGFBO);
        mGFBO = 0;
    }

    if (EXISTS(mPositionTexture))
    {
        glDeleteTextures(1, &mPositionTexture);
        mPositionTexture = 0;
    }

    if (EXISTS(mNormalTexture))
    {
        glDeleteTextures(1, &mNormalTexture);
        mNormalTexture = 0;
    }

    if (EXISTS(mAlbedoSpecTexture))
    {
        glDeleteTextures(1, &mAlbedoSpecTexture);
        mAlbedoSpecTexture = 0;
    }

    if (EXISTS(mDepthTexture))
    {
        glDeleteRenderbuffers(1, &mDepthTexture);
        mDepthTexture = 0;
    }
}


void GBuffer::Activate()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mGFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glBindRenderbuffer(GL_RENDERBUFFER, mDepthRBO);

    //// Tell OpenGL which attachments to use
    //unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    //glDrawBuffers(3, attachments);
    mGeometryPassShader->UseProgram();
}

void GBuffer::BindTextures()
{
    // Bind position texture to texture unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mPositionTexture);

    // Bind normal texture to texture unit 1
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mNormalTexture);

    // Bind albedo + specular texture to texture unit 2
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mAlbedoSpecTexture);
}


void GBuffer::Resize(int width, int height)
{
    Free();

    glGenFramebuffers(1, &mGFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mGFBO);

    // Position buffer
    glGenTextures(1, &mPositionTexture);
    glBindTexture(GL_TEXTURE_2D, mPositionTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mPositionTexture, 0);

    // Normal buffer
    glGenTextures(1, &mNormalTexture);
    glBindTexture(GL_TEXTURE_2D, mNormalTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mNormalTexture, 0);

    // Albedo + Specular buffer
    glGenTextures(1, &mAlbedoSpecTexture);
    glBindTexture(GL_TEXTURE_2D, mAlbedoSpecTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mAlbedoSpecTexture, 0);

    // Depth buffer (optional)
    //glGenRenderbuffers(1, &mDepthRBO);
    //glBindRenderbuffer(GL_RENDERBUFFER, mDepthRBO);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthRBO);

    glGenTextures(1, &mDepthTexture);
    glBindTexture(GL_TEXTURE_2D, mDepthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTexture, 0);


    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);  


    // Check framebuffer status
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "GBuffer :: Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

