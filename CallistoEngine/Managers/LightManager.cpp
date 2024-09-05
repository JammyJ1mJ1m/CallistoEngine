#include "LightManager.h"
#include "../Game.h"
#include "../Math/Vector.h"
#include "../lighting/PointLight.h"
#include "../TestLight.h"
#include "SceneManager.h"

LightManager* LightManager::mInstance = nullptr;

TestLight* LightManager::CreatePointLight(const float pDistance, const Vector3f& pColour)
{
	PointLight* pointLight = new PointLight(pDistance, pColour);
	TestLight* light = new TestLight(pointLight);
	mLights.push_back(light);

	return light;
}

//void LightManager::CreateSpotLight(const float pDistance, const float pAngle, const Vector3f& pColour)
//{
//	SpotLight* spotLight = new SpotLight(pDistance, pAngle, pColour);
//	TestLight* light = new TestLight(spotLight);
//	mLights.push_back(light);
//}

//void LightManager::CreateDirectionalLight(const Vector3f& pDirection, const Vector3f& pColour)
//{
//	DirectionalLight* dirLight = new DirectionalLight(pDirection, pColour);
//	TestLight* light = new TestLight(dirLight);
//	mLights.push_back(light);
//}


LightManager::~LightManager()
{
}