#pragma once
#include "Components\Entity.h"
#include "Components/ComponentModel.h"
#include "ComponentShaderDefault.h"
#include "Components/ComponentTransform.h"
#include "ShooterGame.h"


class Enemy : public Entity
{
	virtual void start();

public:
	Enemy();
	~Enemy() = default;


};

