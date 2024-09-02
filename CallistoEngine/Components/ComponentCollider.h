#pragma once
#include "IComponent.h"
#include "Bullet/btBulletDynamicsCommon.h"
#include <vector>
#include "../Graphical/Vertex.h"
#include "../Math/Vector.h"


enum ColliderType
{
	BOX,
	SPHERE,
	CAPSULE,
	CYLINDER,
	MESH
};

class ComponentCollider : public IComponent
{
	btCollisionShape* mCollisionShape;
	ColliderType mColliderType;
	btTransform mTransform;

	Vector<float,3> FindSmallest(const std::vector<Vertex>& pVerts);
	Vector<float,3> FindLargest(const std::vector<Vertex>& pVerts);

public:
	Vector3f GetCenter() 
	{
		btVector3 center = mTransform.getOrigin();
		Vector3f res;
		res.SetX(center.getX());
		res.SetY(center.getY());
		res.SetZ(center.getZ());
		return res;
	}
	ComponentCollider() = default;

	// pass in geometry to create a auto sized collider - cube in this case
	//ComponentCollider(const std::vector<Vertex>& pVerts, const Vector3f& pPos);
	ComponentCollider(const std::vector<Vertex>& pVerts/*, const Vector3f& pPos*/);
	
	// pass in geometry to create a auto sized collider - sphere in this case
	ComponentCollider(const std::vector<Vertex>& pVerts, const ColliderType pType);

	// pass in model vertices to create a mesh collision shape
	ComponentCollider(const std::vector<Vertex>& pVerts, const std::vector<int>& pIndices);

	// pass in half extents to create a box collider
	ComponentCollider(btVector3 pHalfExtents);
	ComponentCollider(float x, float y, float z);

	// TODO create sphere collider
	ComponentCollider(btScalar pRadius);
	// TODO create capsule collider

	// TODO create cylinder collider
	ComponentCollider(float pRadius, float pHeight);

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

