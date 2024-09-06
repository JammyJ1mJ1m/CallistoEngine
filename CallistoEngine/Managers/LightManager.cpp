#include "LightManager.h"
#include "../Game.h"
#include "../Math/Vector.h"
#include "../lighting/PointLight.h"
//#include "../Entities/LightComponent.h"
#include "SceneManager.h"

LightManager* LightManager::mInstance = nullptr;

LightComponent* LightManager::CreatePointLight(const float pDistance, const Vector3f& pColour)
{
	PointLight* pointLight = new PointLight(pDistance, pColour);
	LightComponent* light = new LightComponent(pointLight);
	mLights.push_back(light);

	return light;
}

//void LightManager::CreateSpotLight(const float pDistance, const float pAngle, const Vector3f& pColour)
//{
//	SpotLight* spotLight = new SpotLight(pDistance, pAngle, pColour);
//	LightComponent* light = new LightComponent(spotLight);
//	mLights.push_back(light);
//}

//void LightManager::CreateDirectionalLight(const Vector3f& pDirection, const Vector3f& pColour)
//{
//	DirectionalLight* dirLight = new DirectionalLight(pDirection, pColour);
//	LightComponent* light = new LightComponent(dirLight);
//	mLights.push_back(light);
//}


LightManager::~LightManager()
{
}