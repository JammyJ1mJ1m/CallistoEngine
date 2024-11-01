#pragma once
#include <glad/glad.h>
#include "../Objects/ShaderObject_GL.h"

class GBuffer
{
private:
    unsigned int mGFBO;
    unsigned int mPositionTexture, mNormalTexture, mAlbedoSpecTexture;
    unsigned int mDepthTexture; 
    ShaderObject_GL* mGeometryPassShader;

public:
    GBuffer();
    ~GBuffer();

    // binds for writing
    void Activate();
    void UnbindGBuffer();
    // binds for reading textures
    void BindTextures();
    void Resize(int width, int height);
    void Free();

    inline unsigned int GetGBufferID() const { return mGFBO; }
    inline unsigned int GetDepthBufferID() const { return mDepthTexture; }
    inline unsigned int GetPositionTextureID() const { return mPositionTexture; }
    inline unsigned int GetNormalTextureID() const { return mNormalTexture; }
    inline unsigned int GetAlbedoSpecTextureID() const { return mAlbedoSpecTexture; }
    ShaderObject* GetShader() const { return mGeometryPassShader; }

};
