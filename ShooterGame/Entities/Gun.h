#pragma once
#include "Components\Entity.h"
#include "Components/ComponentModel.h"
#include "ComponentShaderDefault.h"

#include "Components/ComponentTransform.h"

#include "GunInformation.h"

class Gun : public Entity
{
	virtual void start();

public:
	Gun();
	~Gun() = default;

	void Initialise(GunInformation* pGuninfo);

	void SetPosition(const Vector3f& pPosition) override;
	//void SetPosition(glm::vec3 pPos);
	void SetRotation(glm::vec3 pRot);
	
	void Rotate(float pAmount, float dt);

	virtual void MoveForward() override;
	virtual void MoveBackward() override;
	virtual void MoveLeft() override;
	virtual void MoveRight() override;
};

