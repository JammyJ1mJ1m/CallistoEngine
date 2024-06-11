#include "Enemy.h"
#include "Components/ComponentRigidBody.h"
//#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
//#include "Bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"
#include "Dependencies/inc/Bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"

void convertVertices(const std::vector<glm::vec3>& glnVertices, std::vector<btVector3>& btVertices) {
	btVertices.reserve(glnVertices.size());
	for (const auto& v : glnVertices) {
		btVertices.emplace_back(v.x, v.y, v.z);
	}
}

void Enemy::start()
{
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("cube"), "Resources//Geometry/test/AwesomeAxolotls_1.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));
	glm::vec3 pos = glm::vec3(-8.0f, 15.0f, -15.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
	//mEntities.push_back(tri);



	btVector3 halfExtents(1, 1, 1); // This will create a box of size 2x2x2
	btCollisionShape* boxShape = new btBoxShape(halfExtents);



	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z)); // Starting at position (2.0f, 0.0f, 0.0f)

	btScalar mass = 1.0;
	btVector3 inertia;
	boxShape->calculateLocalInertia(mass, inertia);

	ComponentRigidBody* rb = new ComponentRigidBody(boxShape, mass, inertia, transform);
	AddComponent(rb);


	//// create mesh colider shape
	//std::vector<Vertex> vertices = Game::GetGame()->GetMesh("cube")->GetVertices();
	//std::vector<int> indices = Game::GetGame()->GetMesh("cube")->GetIndices();

	//std::vector<glm::vec3> verts;
	//// copy Vertex positions to glm::vec3 list
	//for (size_t i = 0; i < vertices.size(); i++) {
	//	verts.push_back(vertices[i].Position);
	//}

	//std::vector<btVector3> btVerts;

	//convertVertices(verts, btVerts);

	//btTriangleMesh* trimesh = new btTriangleMesh();
	//for (size_t i = 0; i < indices.size(); i += 3) {
	//	trimesh->addTriangle(btVerts[indices[i]], btVerts[indices[i + 1]], btVerts[indices[i + 2]]);
	//}

	//btBvhTriangleMeshShape* meshShape = new btBvhTriangleMeshShape(trimesh, false);
	////meshShape->updateBound();
}

Enemy::Enemy()
{
	start();
}
