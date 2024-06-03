
#include "ComponentRigidBody.h"

ComponentRigidBody::ComponentRigidBody()
{
	mRigidBody = nullptr;
	mCollisionShape = nullptr;
	mMotionState = nullptr;
	mMass = 0;
	mInertia = btVector3(0, 0, 0);
	mLocalInertia = btVector3(0, 0, 0);
	mTransform = btTransform::getIdentity();
}


ComponentRigidBody::ComponentRigidBody(btCollisionShape* pShape, btScalar pMass, btVector3 pInertia, btTransform pTransform)
{
	mCollisionShape = pShape;
	mMass = pMass;
	mInertia = pInertia;
	mTransform = pTransform;
	mLocalInertia = btVector3(0, 0, 0);
	mCollisionShape->calculateLocalInertia(mMass, mLocalInertia);
	mMotionState = new btDefaultMotionState(mTransform);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mMass, mMotionState, mCollisionShape, mLocalInertia);
	mRigidBody = new btRigidBody(rigidBodyCI);
}

void ComponentRigidBody::SyncWithTransform(ComponentTransform* pTransform)
{
}

IComponent::ComponentTypes ComponentRigidBody::GetType() const
{
	return ComponentTypes::COMPONENT_RIGIDBODY;
}
