#pragma once
#include "Light.h"

class PointLight : public Light
{

	float mConstant;
	float mLinear;
	float mQuadratic;
	float mDistance;

	// this figueres out and sets the attenuation values 
	void CalculateDistance(const float pDistance);

public:
	PointLight();
	PointLight(float pDistance, Vector3f& pAmb, Vector3f pDiff, Vector3f& pSpec);
	PointLight(float pDistance, Vector3f pAmb);
	~PointLight() = default;

	inline const float GetConstant() { return mConstant; };
	inline const float GetLinear() { return mLinear; };
	inline const float GetQuadratic() { return mQuadratic; };

	inline void SetConstant(float pConstant) { mConstant = pConstant; };
	inline void SetLinear(float pLinear) { mLinear = pLinear; };
	inline void SetQuadratic(float pQuadratic) { mQuadratic = pQuadratic; };
};

