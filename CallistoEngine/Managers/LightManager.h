#pragma once

#include <string>
#include <vector>
#include "../Lighting/LightTypes.h"
#include "../Lighting/Light.h"
#include "../Components/LightComponent.h"

#include "../TestLight.h"

class LightManager
{
	//std::vector<Light*> mLights;

	// lightmanager creates and owns the lights, BUT also hands them to the main game entity list?
	std::vector<TestLight*> mLights;
	static LightManager* mInstance;

	LightManager() = default;
public:

	static LightManager& GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new LightManager();
		return *mInstance;
	}

	// creates a point light based Entity and returns it
	TestLight* CreatePointLight(const float pDistance, const Vector3f& pColour);
	// TestLight*s CreateSpotLight(const float pDistance,const float pAngle, const Vector3f& pColour);
	// TestLight* CreateDirectionalLight(const Vector3f& pDirection, const Vector3f& pColour);
	// void CreatePointLight(const float pDistance, const Vector3f& pColour, const Vector3f& pDiffuse, const Vector3f& pSpecular);
	
	const std::vector<TestLight*>& GetLights() const { return mLights; }
	
	~LightManager();
};