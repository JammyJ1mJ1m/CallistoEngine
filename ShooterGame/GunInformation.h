#pragma once
#include "Math/Vector.h"
#include <string>

class GunInformation
{
	Vector3f position;

	std::string modelPath;
	std::string modelMat;

	std::string gunName;
	int magCount;
	int magSize;
	float fireRate;

	bool hasChild;
	std::string childName;
	std::string childPath;

public:
	GunInformation() = default;
	~GunInformation() = default;

	// Getters
	Vector3f getPosition() const { return position; }
	std::string getModelPath() const { return modelPath; }
	std::string getModelMat() const { return modelMat; }
	std::string getGunName() const { return gunName; }
	int getMagCount() const { return magCount; }
	int getMagSize() const { return magSize; }
	float getFireRate() const { return fireRate; }

	bool GetHasChild() const { return hasChild; }
	std::string getChildName() const { return childName; }
	std::string getChildPath() const { return childPath; }

	// Setters
	void setPosition(const Vector3f& newPos) { position = newPos; }
	void setModelPath(const std::string& newModelPath) { modelPath = newModelPath; }
	void setModelMat(const std::string& newModelMat) { modelMat = newModelMat; }
	void setGunName(const std::string& newGunName) { gunName = newGunName; }
	void setMagCount(int newMagCount) { magCount = newMagCount; }
	void setMagSize(int newMagSize) { magSize = newMagSize; }
	void setFireRate(float newFireRate) { fireRate = newFireRate; }
	void SetHasChild(bool pHasChild) { hasChild = pHasChild; }
	void setChildName(const std::string& newChildName) { childName = newChildName; }
	void setChildPath(const std::string& newChildPath) { childPath = newChildPath; }
};

