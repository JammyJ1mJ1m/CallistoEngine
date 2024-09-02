#pragma once
#include "IComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Bullet/btBulletDynamicsCommon.h"
#include "../Math/Vector.h"

class ComponentTransform : public IComponent
{

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 modelMatrix;

public:
	ComponentTransform();
	ComponentTransform(glm::vec3 pPos, glm::vec3 pRot, glm::vec3 pScale );
	~ComponentTransform() = default;

	//inline const glm::vec3& GetPosition() { return position; }
	inline const Vector3f& GetPosition() { return Vector3f(position.x,position.y,position.z); }
	inline const glm::vec3& GetRotation() { return rotation; }
	inline const glm::vec3& GetScale() { return scale; }

	//inline void SetPosition(glm::vec3 pPosition) { position = pPosition; UpdateModelMatrix(); }


	inline void SetPosition(const Vector3f& pPosition)
	{
		position.x = pPosition.GetX(); 
		position.y = pPosition.GetY();
		position.z = pPosition.GetZ();
		
		UpdateModelMatrix(); 
	}



	inline void SetRotation(glm::vec3 pRotation) { rotation = pRotation; UpdateModelMatrix(); }
	inline void SetScale(glm::vec3 pScale) { scale = pScale; UpdateModelMatrix(); }

	inline const glm::mat4 GetModelMatrix() { return modelMatrix; }
	inline void SetModelMatrix(glm::mat4 pModelMatrix) { modelMatrix = pModelMatrix; }
	void UpdateModelMatrix();

	void Translate(glm::vec3 pTranslation);
	void RotateX(const float pAngle);
	void RotateY(const float pAngle);
	void RotateZ(const float pAngle);
	void Scale(glm::vec3 pScale);

	void GetWorld();

	void SyncTransform(const btTransform& pTransform);

	virtual ComponentTypes GetType() const;
};