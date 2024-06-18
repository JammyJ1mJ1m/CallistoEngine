#include "PhysicsManager.h"
#include "Bullet/BulletCollision/CollisionDispatch/btGhostObject.h"

const float PhysicsManager::mTimeStep = 1.0f / 60.0f;

PhysicsManager* PhysicsManager::mInstance = nullptr;

PhysicsManager::PhysicsManager(float pGrav)
	: mGravity(pGrav)
{
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mBroadphase = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver();
	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfiguration);
	mDynamicsWorld->setGravity(btVector3(0,-19.8, 0));
}


void PhysicsManager::Initialise()
{
}

void PhysicsManager::Update(double deltaTime)
{
	mDynamicsWorld->stepSimulation(deltaTime, 10);
}


PhysicsManager::~PhysicsManager()
{
	delete mDynamicsWorld;
	delete mSolver;
	delete mBroadphase;
	delete mDispatcher;
	delete mCollisionConfiguration;
}