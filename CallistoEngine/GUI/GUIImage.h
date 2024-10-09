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
	Vector4f mColor;
	ShaderObject_GL* mShaderObject;

	//glm::mat4 mProjction;

	//float mScale;
	float mAspectRatio;
	//float mImageWidth;
	//float mImageHeight;
	//float mMaxWidth;
	//float mMaxHeight;


	float CalculateAspectRatio(const int pWidth, const int pHeight);
	void CalculateVertices(float width, float height);
	void InitialiseImage(const int pMaxWidth, const int pMaxHeight);

protected:
	void ResizeChild(const int pWidth, const int pHeight) override;
	bool InitialiseChild() override;

public:
	GUIImage(const Vector4f& pCol);

	/// <summary>
	/// Initialises the image based on the width, height and its max dimensions
	/// A value of 1 is used as the base minimum so that an artifact will still show on the screen
	/// </summary>
	/// <param name="pMaxWidth">Between 1-100, a percentage of how much screen to cover</param>
	/// <param name="pMaxHeight">Between 1-100, a percentage of how much screen to cover</param>
	GUIImage(const int pWidth, const int pHeight, const float pScale, const int pMaxWidth, const int pMaxHeight);
	~GUIImage() = default;

	inline void SetColor(const Vector4f& pCol) { mColor = pCol; }




	void Render() override;
};

