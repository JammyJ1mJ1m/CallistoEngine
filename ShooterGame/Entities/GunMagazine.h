#pragma once
#include "Components\Entity.h"
#include "Components/ComponentModel.h"
#include "ComponentShaderDefault.h"

#include "Components/ComponentTransform.h"

class GunMagazine : public Entity
{
	virtual void start();
	void SetPosition(const Vector3f& pPosition) override;

public:
	GunMagazine();
	~GunMagazine() = default;
	
	void Initialise(const char* pModelName, const char* pModelMat);

	//void SetPosition(glm::vec3 pPos);
	void SetRotation(glm::vec3 pRot);
	
	void Rotate(float pAmount, float dt);

	virtual void MoveForward();
	virtual void MoveBackward();
	virtual void MoveLeft();
	virtual void MoveRight();
};

