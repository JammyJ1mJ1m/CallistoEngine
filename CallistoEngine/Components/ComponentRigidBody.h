#pragma once
#include "IComponent.h"
//#include "../Dependencies/inc/Bullet/btBulletCollisionCommon.h"

#include "C:\Users\jamwi\source\repos\OpenGL_Engine\CallistoEngine\Dependencies\inc\Bullet/btBulletDynamicsCommon.h"
#include "ComponentTransform.h"

class ComponentRigidBody : public IComponent
{
	btRigidBody* mRigidBody;
	btCollisionShape* mCollisionShape;
	btDefaultMotionState* mMotionState;
	btScalar mMass;
	btVector3 mInertia;
	btVector3 mLocalInertia;
	btTransform mTransform;

	public:
		ComponentRigidBody();
		ComponentRigidBody(btCollisionShape* pShape, btScalar pMass, btVector3 pInertia, btTransform pTransform);
		~ComponentRigidBody() = default;

		inline btRigidBody* GetRigidBody() { return mRigidBody; }
		inline btCollisionShape* GetCollisionShape() { return mCollisionShape; }
		inline btDefaultMotionState* GetMotionState() { return mMotionState; }
		inline btScalar GetMass() { return mMass; }
		inline btVector3 GetInertia() { return mInertia; }
		inline btVector3 GetLocalInertia() { return mLocalInertia; }
		inline btTransform GetTransform() { return mTransform; }

		inline void SetRigidBody(btRigidBody* pRigidBody) { mRigidBody = pRigidBody; }
		inline void SetCollisionShape(btCollisionShape* pCollisionShape) { mCollisionShape = pCollisionShape; }
		inline void SetMotionState(btDefaultMotionState* pMotionState) { mMotionState = pMotionState; }
		inline void SetMass(btScalar pMass) { mMass = pMass; }

		void SyncWithTransform(ComponentTransform* pTransform);


		// ******************************************************
		// inherited stuff
		virtual ComponentTypes GetType() const;
};

