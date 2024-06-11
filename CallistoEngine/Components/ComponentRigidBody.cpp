
#include "ComponentRigidBody.h"
#include "PhysicsManager.h"
#include "iostream"

ComponentRigidBody::ComponentRigidBody()
{
	mRigidBody = nullptr;
	mCollisionShape = nullptr;
	mMotionState = nullptr;
	mMass = 0;

	mTransform = btTransform::getIdentity();
}


ComponentRigidBody::ComponentRigidBody(btCollisionShape* pShape, btScalar pMass, const btVector3& pInertia, const btTransform& pTransform)
{
	mCollisionShape = pShape;
	mMass = pMass;
	mTransform = pTransform;
	mMotionState = new btDefaultMotionState(mTransform);


	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mMass, mMotionState, mCollisionShape, pInertia);

	mRigidBody = new btRigidBody(rigidBodyCI);
	
	//mRigidBody->setDamping(0.05, 0.05);  // Linear and angular damping
	//mRigidBody->setFriction(0.5);  // Set friction
	mRigidBody->setRestitution(1);  // Set restitution (bounciness)
	//mRigidBody->setAngularFactor(btVector3(1, 1, 1));  // Allow rotation around all axes

	// add rb to phys manager world
	PhysicsManager::GetInstance().AddRigidBody(mRigidBody);

}

void ComponentRigidBody::SyncWithTransform(ComponentTransform* pTransform)
{
	btTransform trans;
	trans = mRigidBody->getWorldTransform();
	pTransform->SetPosition(glm::vec3(trans.getOrigin().x() * 2, trans.getOrigin().y() * 2, trans.getOrigin().z()*2));
	pTransform->SetRotation(glm::vec3(trans.getRotation().x() * 2, trans.getRotation().y() * 2, trans.getRotation().z() * 2));
}

IComponent::ComponentTypes ComponentRigidBody::GetType() const
{
	return ComponentTypes::COMPONENT_RIGIDBODY;
}
ComponentRigidBody::~ComponentRigidBody()
{
	// delete rigid body
	delete mRigidBody;
	delete mCollisionShape;
	delete mMotionState;
	// remove RB from physcis manager
	//PhysicsManager::GetInstance().RemoveRigidBody(mRigidBody);
}
