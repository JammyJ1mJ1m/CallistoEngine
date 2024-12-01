#pragma once
#include "Components\Entity.h"
#include "Components/ComponentModel.h"
#include "ComponentShaderDefault.h"
#include "ComponentShaderScanLines.h"
#include "ComponentShaderError.h"
#include "Components/ComponentTransform.h"
#include "Messages/ExplodeMessage.h"
#include "Components/ExplodableComponent.h"

class ExpBarrel : public Entity
{
	virtual void start();
	void SetPosition(const Vector3f& pPosition) override;

public:
	ExpBarrel();
	~ExpBarrel() = default;

	void SetPosition(glm::vec3 pPos);

	virtual void MoveForward() ;
	virtual void MoveBackward() ;
	virtual void MoveLeft() ;
	virtual void MoveRight() ;
	virtual void OnMessage(Message* msg);

};

