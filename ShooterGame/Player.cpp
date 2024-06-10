#include "Player.h"
#include "ShooterGame.h"
#include "Components/ComponentRigidBody.h"

void convertVerticess(const std::vector<glm::vec3>& glnVertices, std::vector<btVector3>& btVertices) {
	btVertices.reserve(glnVertices.size());
	for (const auto& v : glnVertices) {
		btVertices.emplace_back(v.x, v.y, v.z);
	}
}
void Player::start()
{
	AddComponent(new ComponentModel(Game::GetGame()->GetMesh("ship"), "Resources/textures/TCube.mtl"));
	AddComponent(new ComponentShaderDefault(ShooterGame::GetGameCamera(), "Resources/Shaders/default.vert", "Resources/Shaders/default.frag"));

	glm::vec3 pos = glm::vec3(0.0f, -5.0f, 0.0f);
	AddComponent(new ComponentTransform(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 1, 1)));
	//mEntities.push_back(tri);



	btVector3 halfExtents(4.0, 0.2, 4.0); // This will create a box of size 2x2x2
	btCollisionShape* boxShape = new btBoxShape(halfExtents);

	// create mesh colider shape
	std::vector<Vertex> vertices = Game::GetGame()->GetMesh("ship")->GetVertices();
	std::vector<int> indices = Game::GetGame()->GetMesh("ship")->GetIndices();

	std::vector<glm::vec3> verts;
	// copy Vertex positions to glm::vec3 list
	for (size_t i = 0; i < vertices.size(); i++) {
		verts.push_back(vertices[i].Position);
	}

	std::vector<btVector3> btVerts;

	convertVerticess(verts, btVerts);

	btTriangleMesh* trimesh = new btTriangleMesh();
	for (size_t i = 0; i < indices.size(); i += 3) {
		trimesh->addTriangle(btVerts[indices[i]], btVerts[indices[i + 1]], btVerts[indices[i + 2]]);
	}

	btBvhTriangleMeshShape* meshShape = new btBvhTriangleMeshShape(trimesh, false);
	//meshShape->updateBound();


	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z)); // Starting at position (2.0f, 0.0f, 0.0f)

	const btVector3 inertia(0, 0, 0);
	int mass = 0;

	ComponentRigidBody* rb = new ComponentRigidBody(meshShape, mass, inertia, transform);
	AddComponent(rb);
}

Player::Player()
{

	start();
}
