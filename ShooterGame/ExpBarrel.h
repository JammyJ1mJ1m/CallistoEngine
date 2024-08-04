#pragma once
#include "Components\Entity.h"
#include "Components/ComponentModel.h"
#include "ComponentShaderDefault.h"
#include "ComponentShaderError.h"
#include "Components/ComponentTransform.h"

class ExpBarrel : public Entity
{
	virtual void start();
	void SetPosition() override;

public:
	ExpBarrel();
	~ExpBarrel() = default;

	void SetPosition(glm::vec3 pPos);
	void applyExplosionForce(btDiscreteDynamicsWorld& world, const btVector3& explosionOrigin, btScalar explosionStrength, btScalar explosionRadius);

};

