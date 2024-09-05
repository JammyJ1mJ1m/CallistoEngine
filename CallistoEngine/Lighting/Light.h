#pragma once
#include "../Math/Vector.h"
#include "LightTypes.h"

class Light
{
protected:
	LightType mType;

	Vector3f mAmbient;
	Vector3f mDiffuse;
	Vector3f mSpecular;

public:
	/*Light();*/
	~Light() = default;

	inline const LightType GetType() const { return mType; };

	inline const Vector3f& GetAmbient() { return mAmbient; };
	inline const Vector3f& GetDiffuse() { return mDiffuse; };
	inline const Vector3f& GetSpecular() { return mSpecular; };

	inline void SetAmbient(const Vector3f& pAmbient) { mAmbient = pAmbient; };
	inline void SetDiffuse(const Vector3f& pDiffuse) { mDiffuse = pDiffuse; };
	inline void SetSpecular(const Vector3f& pSpecular) { mSpecular = pSpecular; };
};

