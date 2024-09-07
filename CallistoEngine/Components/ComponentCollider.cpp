#include "ComponentCollider.h"


Vector<float, 3> ComponentCollider::FindSmallest(const std::vector<Vertex>& pVerts) {
	// Initialize to a very large number
	Vector<float, 3> smallest(5000.0f,5000.0f,5000.0f);

	// Iterate over all vertices to find the smallest x, y, and z
	for (const auto& vert : pVerts) {
		if (vert.Position.x < smallest.GetX()) smallest.SetX(vert.Position.x);
		if (vert.Position.y < smallest.GetY()) smallest.SetY(vert.Position.y);
		if (vert.Position.z < smallest.GetZ()) smallest.SetZ(vert.Position.z);
	}
	return smallest;
}

Vector<float, 3> ComponentCollider::FindLargest(const std::vector<Vertex>& pVerts)
{
	Vector<float, 3> largest(-5000.0f, -5000.0f,-5000.0f);


	for (size_t i = 0; i < pVerts.size(); i++)
	{
		if (pVerts[i].Position.x > largest.GetX()) largest.SetX(pVerts[i].Position.x);
		if (pVerts[i].Position.y > largest.GetY()) largest.SetY(pVerts[i].Position.y);
		if (pVerts[i].Position.z > largest.GetZ()) largest.SetZ(pVerts[i].Position.z);
	}
	return largest;
}

//ComponentCollider::ComponentCollider(const std::vector<Vertex>& pVerts,const Vector3f& pPos)
//{
//	// Find the smallest and largest vertices
//	Vector3f smallest = FindSmallest(pVerts);
//	Vector3f largest = FindLargest(pVerts);
//
//	// Calculate the center of the bounding box
//	Vector3f center = (smallest + largest);
//
//	// Calculate the half-extents
//	btVector3 halfExtents = btVector3(
//		(largest.GetX() - smallest.GetX()) ,
//		(largest.GetY() - smallest.GetY()) ,
//		(largest.GetZ() - smallest.GetZ()) 
//	);
//
//
//	mCollisionShape = new btBoxShape(halfExtents);
//
//	//// Adjust the position of the collider to center it on the mesh's bounding box center
//	//mTransform.setIdentity();
//	//mTransform.setOrigin(btVector3(center.GetX(), center.GetY(), center.GetZ()));
//
//	//// offset the transform position by the difference of center and pPos
//	//mTransform.setOrigin(mTransform.getOrigin() - btVector3(pPos.GetX(), pPos.GetY(), pPos.GetZ()));
//
//	// Set the collider type
//	mColliderType = ColliderType::BOX;
//}

ComponentCollider::ComponentCollider(const std::vector<Vertex>& pVerts, const float pScale )
{
	Vertex min = pVerts[0];
	Vertex max = pVerts[0];

	Vector3f smallest = FindSmallest(pVerts);
	Vector3f largest = FindLargest(pVerts);

	// now grab the half extents
	btVector3 halfExtents = btVector3((largest.GetX() - smallest.GetX()), (largest.GetY() - smallest.GetY()), (largest.GetZ() - smallest.GetZ()));
	mCollisionShape = new btBoxShape(halfExtents * pScale);
	mColliderType = ColliderType::BOX;
}

ComponentCollider::ComponentCollider(const std::vector<Vertex>& pVerts, const ColliderType pType)
{
	if (pType == ColliderType::SPHERE)
	{
		// find the largest distance from the center of the object
		float maxDistance = 0;
		for (size_t i = 0; i < pVerts.size(); i++)
		{
			float distance = glm::length(pVerts[i].Position);
			if (distance > maxDistance) maxDistance = distance;
		}
		mCollisionShape = new btSphereShape(maxDistance * 2);
		mColliderType = ColliderType::SPHERE;
	}
	else if (pType == ColliderType::BOX)
	{
		Vertex min = pVerts[0];
		Vertex max = pVerts[0];

		for (size_t i = 0; i < pVerts.size(); i++)
		{
			// loop through and find the smallest and largest vertex position values
			if ((pVerts[i].Position.x < min.Position.x) &&
				(pVerts[i].Position.y < min.Position.y) &&
				(pVerts[i].Position.z < min.Position.z))
			{

				min.Position.x = pVerts[i].Position.x;
				min.Position.y = pVerts[i].Position.y;
				min.Position.z = pVerts[i].Position.z;
			}

			if (pVerts[i].Position.x > max.Position.x) max.Position.x = pVerts[i].Position.x;
			if (pVerts[i].Position.y > max.Position.y) max.Position.y = pVerts[i].Position.y;
			if (pVerts[i].Position.z > max.Position.z) max.Position.z = pVerts[i].Position.z;
		}
		// now grab the half extents
		btVector3 halfExtents = btVector3((max.Position.x - min.Position.x), (max.Position.y - min.Position.y), (max.Position.z - min.Position.z));
		mCollisionShape = new btBoxShape(halfExtents);
		mColliderType = ColliderType::BOX;
	}
	else if (pType == ColliderType::CYLINDER)
	{
		// find the largest distance from the center of the object
		float maxDistance = 0;
		for (size_t i = 0; i < pVerts.size(); i++)
		{
			float distance = glm::length(pVerts[i].Position);
			if (distance > maxDistance) maxDistance = distance;
		}
		mCollisionShape = new btCylinderShape(btVector3(maxDistance, maxDistance, maxDistance));
		mColliderType = ColliderType::CYLINDER;
	}
}

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
	trimesh->setScaling(btVector3(2, 2, 2));
	mCollisionShape = new btBvhTriangleMeshShape(trimesh, false);
	mColliderType = ColliderType::MESH;
}

ComponentCollider::ComponentCollider(btVector3 pHalfExtents)
{
	mCollisionShape = new btBoxShape(pHalfExtents);
	mColliderType = ColliderType::BOX;
}

ComponentCollider::ComponentCollider(float x, float y, float z)
{
	mCollisionShape = new btBoxShape(btVector3(x, y, z));
	mColliderType = ColliderType::BOX;
}

ComponentCollider::ComponentCollider(btScalar pRadius)
{
	mCollisionShape = new btSphereShape(pRadius);

	mColliderType = ColliderType::SPHERE;
}

ComponentCollider::ComponentCollider(float pRadius, float pHeight)
{
	mCollisionShape = new btCylinderShape(btVector3(pRadius, pHeight, pRadius));
	mColliderType = ColliderType::CYLINDER;
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
