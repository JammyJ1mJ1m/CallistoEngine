#include "PhysicsManager.h"

const float PhysicsManager::mTimeStep = 1.0f / 60.0f;

PhysicsManager::PhysicsManager(float pGrav)
	: mGravity(pGrav)
{
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mBroadphase = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver();
	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfiguration);
	mDynamicsWorld->setGravity(btVector3(0, mGravity, 0));
}


void PhysicsManager::Initialise()
{
}

void PhysicsManager::Update(double deltaTime)
{
		mDynamicsWorld->stepSimulation(mTimeStep, 10);
}


PhysicsManager::~PhysicsManager()
{
	delete mDynamicsWorld;
	delete mSolver;
	delete mBroadphase;
	delete mDispatcher;
	delete mCollisionConfiguration;
}