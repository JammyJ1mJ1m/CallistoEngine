#pragma once
#include "IComponent.h"
//#include "../Dependencies/inc/Bullet/btBulletCollisionCommon.h"
#include <Bullet/btBulletCollisionCommon.h>
#include "Bullet/btBulletDynamicsCommon.h"
#include "ComponentTransform.h"
#include "componentCollider.h"
#include "Entity.h"
#include "../Math/Vector.h"

class ComponentRigidBody : public IComponent
{
	btRigidBody* mRigidBody;
	//btCollisionShape* mCollisionShape;
	btDefaultMotionState* mMotionState;
	btScalar mMass;
	btTransform mTransform;
	btVector3 mInertia;

	public:
		ComponentRigidBody();
		//ComponentRigidBody(btCollisionShape* pShape, btScalar pMass, const btVector3& pInertia, const btTransform& pTransform);
		ComponentRigidBody(ComponentCollider* pCollider, btScalar pMass,  const Vector3f& pPos, bool gravityEnabled = true);
		~ComponentRigidBody() ;

		inline btRigidBody* GetRigidBody() { return mRigidBody; }
		inline btDefaultMotionState* GetMotionState() { return mMotionState; }
		inline btScalar GetMass() { return mMass; }
		inline btTransform GetTransform() { return mTransform; }

		inline void SetRigidBody(btRigidBody* pRigidBody) { mRigidBody = pRigidBody; }
		inline void SetMotionState(btDefaultMotionState* pMotionState) { mMotionState = pMotionState; }
		inline void SetMass(btScalar pMass) { mMass = pMass; }

		void SyncWithTransform(ComponentTransform* pTransform);
		void SyncWithTransform(Entity* pEntity);
		void SetPosition(const Vector3f pPos);

		// ******************************************************
		// inherited stuff
		virtual ComponentTypes GetType() const;
};

