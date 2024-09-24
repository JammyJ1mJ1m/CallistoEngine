#pragma once
#include "GUIElement.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "../Objects/ShaderObject_GL.h"

class GUIImage : public GUIElement
{
	unsigned int mTextureHandle;
	unsigned int mVAO, mVBO, mEBO;
	Vector3f mColor;
	ShaderObject_GL* mShaderObject;

	float CalculateAspectRatio(const int pWidth, const int pHeight);
public:
	GUIImage(const Vector3f& pCol);
	~GUIImage() = default;

	void Initialise(int width, int height, float scale);

	void Render() override;
};

