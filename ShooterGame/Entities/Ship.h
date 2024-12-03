#pragma once
#include "Components\Entity.h"
#include "Components/ComponentModel.h"
#include "ComponentShaderDefault.h"
#include "Components/ComponentTransform.h"
#include "ShooterGame.h"


class Ship : public Entity
{
	virtual void start();
	void SetPosition(const Vector3f& pPosition) override;
	float mMoveForce;

public:
	Ship();
	~Ship() = default;
	 void SetPosition(glm::vec3 pPos);

	 virtual void MoveForward();
	 virtual void MoveBackward();
	 virtual void MoveLeft();
	 virtual void MoveRight();

	 virtual void OnMessage(Message* msg);

};