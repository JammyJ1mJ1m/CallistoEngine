#pragma once
#include "Components\Entity.h"
#include "Components/ComponentTransform.h"

class SkyBox :public Entity
{
	virtual void start();
	void SetPosition() override;
public:
	SkyBox();
	~SkyBox() = default;
	void SetPosition(glm::vec3 pPos);

	virtual void MoveForward();
	virtual void MoveBackward();
	virtual void MoveLeft();
	virtual void MoveRight();

};
