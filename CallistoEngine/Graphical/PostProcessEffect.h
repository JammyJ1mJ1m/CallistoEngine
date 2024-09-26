#pragma once
#include <string>
#include "../Objects/ShaderObject_GL.h"
#include "RenderTarget.h"

class PostProcessEffect
{
private:
    // replace this with the vertices
    //Model* screenQuad;

    bool isActive = true;

    std::string shaderName;

    RenderTarget* target;
    ShaderObject* shader;
    bool usesDepth = true;

    virtual void OnActivate() {}
protected:

public:

    void Create();

    void Render();
    void Resize(int width, int height);

    void SetTarget(RenderTarget* target);

    void SetActive(bool isActive) { this->isActive = isActive; }

    inline bool IsActive() const { return isActive; }

    inline void UseDepth(bool usesDepth) { this->usesDepth = usesDepth; }

    explicit PostProcessEffect(const char* shader);
    explicit PostProcessEffect() = default;
    virtual ~PostProcessEffect();

    void LoadShader(const char* pVertexPath, const char* pFragPath, const char* pShaderID);

};
