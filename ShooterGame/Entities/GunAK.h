#pragma once
#include "Components\Entity.h"
#include "Components/ComponentModel.h"
#include "ComponentShaderDefault.h"

#include "Components/ComponentTransform.h"

class GunAK : public Entity
{
	virtual void start();
	void SetPosition(const Vector3f& pPosition) override;

public:
	GunAK();
	~GunAK() = default;

	//void SetPosition(glm::vec3 pPos);
	void SetRotation(glm::vec3 pRot);
	
	void Rotate(float pAmount, float dt);

	virtual void MoveForward();
	virtual void MoveBackward();
	virtual void MoveLeft();
	virtual void MoveRight();
};

