
#include "ComponentRigidBody.h"
#include "PhysicsManager.h"

ComponentRigidBody::ComponentRigidBody()
{
	mRigidBody = nullptr;
	mCollisionShape = nullptr;
	mMotionState = nullptr;
	mMass = 10.0f;

	mTransform = btTransform::getIdentity();
}


ComponentRigidBody::ComponentRigidBody(btCollisionShape* pShape, btScalar pMass, btVector3 pInertia, btTransform pTransform)
{
	mCollisionShape = pShape;
	mMass = pMass;
	mTransform = pTransform;
	mMotionState = new btDefaultMotionState(mTransform);
	mRigidBody = new btRigidBody(mMass, mMotionState, pShape);


	// add rb to phys manager world
	PhysicsManager::GetInstance().AddRigidBody(mRigidBody);
}

void ComponentRigidBody::SyncWithTransform(ComponentTransform* pTransform)
{
	btTransform pos;
	GetMotionState()->getWorldTransform(pos);
	//std::cout << pos.getOrigin().x() << " " << pos.getOrigin().y() << " " << pos.getOrigin().z() << std::endl;

	pTransform->SetPosition(glm::vec3(pos.getOrigin().x(), pos.getOrigin().y(), pos.getOrigin().z()));
}

IComponent::ComponentTypes ComponentRigidBody::GetType() const
{
	return ComponentTypes::COMPONENT_RIGIDBODY;
}
