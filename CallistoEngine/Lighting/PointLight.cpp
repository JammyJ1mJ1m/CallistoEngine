#include "PointLight.h"

void PointLight::CalculateDistance(const float pDistance)
{
	mDistance = pDistance;
	mConstant = 1.0f;
	mLinear = 4.4f / pDistance;
	mQuadratic = 80.0f / (pDistance * pDistance);
}

PointLight::PointLight()
{
	mAmbient = Vector3f(0.05f, 0.05f, 0.05f);
	mDiffuse = Vector3f(0.8f, 0.8f, 0.8f);
	mSpecular = Vector3f(1.0f, 1.0f, 1.0f);

	CalculateDistance(100.0f);
}

PointLight::PointLight(float pDistance, Vector3f& pAmb, Vector3f pDiff, Vector3f& pSpec, const Vector3f& pPosOffset)
{
	mAmbient = pAmb;
	mDiffuse = pDiff;
	mSpecular = pSpec;
	mPositionOffset = pPosOffset;

	CalculateDistance(pDistance);
}


PointLight::PointLight(float pDistance, Vector3f pAmb, const Vector3f& pPosOffset)
{
	mType = LightType::POINT;
	mAmbient = pAmb;
	mDiffuse = pAmb;
	mSpecular = pAmb;
	mPositionOffset = pPosOffset;


	CalculateDistance(pDistance);
}
