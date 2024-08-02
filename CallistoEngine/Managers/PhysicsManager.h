#pragma once
//#include "Bullet/btBulletDynamicsCommon.h"
// #include "../Dependencies/inc/Bullet/btBulletDynamicsCommon.h"
//#include "Bullet/btBulletCollisionCommon.h"
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

	static PhysicsManager* mInstance;

	PhysicsManager(float pGrav = -9.8f);

public:

	static PhysicsManager& GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new PhysicsManager();

		return *mInstance;
	}

	void AddRigidBody(btRigidBody* pBody) { mDynamicsWorld->addRigidBody(pBody); };
	

	static const float mTimeStep;

	//PhysicsManager(float pGrav = -9.8f);
	~PhysicsManager();

	void SetGravity(float gravity) { mGravity = gravity; }
	float GetGravity() { return mGravity; }

	inline btDiscreteDynamicsWorld& GetDynamicsWorld() { return *mDynamicsWorld; }

	void Initialise();

	// steps through the physics 
	void Update(double deltaTime);
};