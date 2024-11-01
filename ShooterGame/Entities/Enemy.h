#pragma once
#include "Components\Entity.h"
#include "Components/ComponentModel.h"
#include "ComponentShaderDefault.h"
#include "Components/ComponentTransform.h"
#include "ShooterGame.h"


class Enemy : public Entity
{
	virtual void start();
	void SetPosition(const Vector3f& pPosition) override;

public:
	Enemy();
	~Enemy() = default;
	 void SetPosition(glm::vec3 pPos);

	 virtual void MoveForward();
	 virtual void MoveBackward();
	 virtual void MoveLeft();
	 virtual void MoveRight();
};