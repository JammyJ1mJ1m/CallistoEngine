#pragma once
#include "IComponent.h"
#include "Bullet/btBulletDynamicsCommon.h"
#include <vector>
#include "../Vertex.h"


enum ColliderType
{
	BOX,
	SPHERE,
	CAPSULE,
	MESH
};

class ComponentCollider : public IComponent
{
	btCollisionShape* mCollisionShape;
	ColliderType mColliderType;

public:
	ComponentCollider() = default;

	// pass in model vertices to create a mesh collision shape
	ComponentCollider(const std::vector<Vertex>& pVerts, const std::vector<int>& pIndices);

	// pass in half extents to create a box collider
	ComponentCollider(btVector3 pHalfExtents);

	// TODO create sphere collider
	ComponentCollider(btScalar pRadius);
	// TODO create capsule collider

	// pass in a collision shape and a transform
	ComponentCollider(btCollisionShape* pShape, const btTransform& pTransform);
	~ComponentCollider();

	inline void SetCollisionShape(btCollisionShape* pCollisionShape) { mCollisionShape = pCollisionShape; }
	inline btCollisionShape* GetCollisionShape() { return mCollisionShape; }
	inline const ColliderType GetColliderType() { return mColliderType; }

	// ******************************************************
	// inherited stuff
	virtual ComponentTypes GetType() const;
};

