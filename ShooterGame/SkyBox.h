#pragma once
#include "Components\Entity.h"
class SkyBox :public Entity
{
	virtual void start();

public:
	SkyBox();
	~SkyBox() = default;

};

