#include "ComponentCollider.h"


ComponentCollider::ComponentCollider(const std::vector<Vertex>& pVerts, const std::vector<int>& pIndices)
{
	std::vector<glm::vec3> verts;
	std::vector<btVector3> btVerts;

	for (size_t i = 0; i < pVerts.size(); i++) {
		btVerts.emplace_back(pVerts[i].Position.x, pVerts[i].Position.y, pVerts[i].Position.z);
	}

	btTriangleMesh* trimesh = new btTriangleMesh();
	for (size_t i = 0; i < pIndices.size(); i += 3) 
	{
		trimesh->addTriangle(btVerts[pIndices[i]], btVerts[pIndices[i + 1]], btVerts[pIndices[i + 2]]);
	}

	btConvexHullShape* convexHullShape = new btConvexHullShape();
	for (const auto& vert : btVerts) {
		convexHullShape->addPoint(vert);
	}

	mCollisionShape = new btBvhTriangleMeshShape(trimesh,false);
	mColliderType = ColliderType::MESH;
}

ComponentCollider::ComponentCollider(btVector3 pHalfExtents)
{
		mCollisionShape = new btBoxShape(pHalfExtents);
		mColliderType = ColliderType::BOX;
}

ComponentCollider::ComponentCollider(btScalar pRadius)
{
	mCollisionShape = new btSphereShape(pRadius);
	mColliderType = ColliderType::SPHERE;
}

ComponentCollider::ComponentCollider(btCollisionShape* pShape, const btTransform& pTransform)
{
	mCollisionShape = pShape;
	mColliderType = ColliderType::MESH;
}


IComponent::ComponentTypes ComponentCollider::GetType() const
{
	return ComponentTypes::COMPONENT_COLLIDER;
}

ComponentCollider::~ComponentCollider()
{
	delete mCollisionShape;
}
