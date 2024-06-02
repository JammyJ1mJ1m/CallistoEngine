#pragma once
#include "Bullet/btBulletDynamicsCommon.h"

class PhysicsManager
{
	btDiscreteDynamicsWorld* mDynamicsWorld;
	btDefaultCollisionConfiguration* mCollisionConfiguration;
	btCollisionDispatcher* mDispatcher;
	btDbvtBroadphase* mBroadphase;
	btSequentialImpulseConstraintSolver* mSolver;

	float timeAccumulator = 0.0f;
	float mGravity;

public:
	static const float mTimeStep;

	PhysicsManager(float pGrav = -9.8f);
	~PhysicsManager();

	void SetGravity(float gravity) { mGravity = gravity; }
	float GetGravity() { return mGravity; }

	inline btDiscreteDynamicsWorld& GetDynamicsWorld() { return *mDynamicsWorld; }

	void Initialise();

	// steps through the physics 
	void Update(double deltaTime);
};