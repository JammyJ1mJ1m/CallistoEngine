#pragma once
#include "Components\Entity.h"
#include "Components/ComponentModel.h"
#include "ComponentShaderDefault.h"

#include "Components/ComponentTransform.h"

class Player : public Entity
{
	virtual void start();

	public:
		Player();
		~Player() = default;


};

