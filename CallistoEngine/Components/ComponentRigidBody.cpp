
#include "ComponentRigidBody.h"
#include "PhysicsManager.h"
#include "iostream"

ComponentRigidBody::ComponentRigidBody()
{
	mRigidBody = nullptr;
	//mCollisionShape = nullptr;
	mMotionState = nullptr;
	mMass = 0;

	mTransform = btTransform::getIdentity();
}


ComponentRigidBody::ComponentRigidBody(ComponentCollider* pCollider, btScalar pMass, const glm::vec3& pPos)
{
	mMass = pMass;
	mInertia = btVector3();

	// Don't want to calculate inertia for static mesh objects
	if (pCollider->GetColliderType() == ColliderType::BOX)
		pCollider->GetCollisionShape()->calculateLocalInertia(mMass, mInertia);

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pPos.x, pPos.y, pPos.z));

	mTransform = transform;
	mMotionState = new btDefaultMotionState(mTransform);


	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mMass, mMotionState, pCollider->GetCollisionShape(), mInertia);

	mRigidBody = new btRigidBody(rigidBodyCI);

	mRigidBody->setDamping(0.25, 0.25);  // Linear and angular damping
	mRigidBody->setFriction(0.5);  // Set friction
	//mRigidBody->setRestitution(1);  // Set restitution (bounciness)
	//mRigidBody->setAngularFactor(btVector3(1, 1, 1));  // Allow rotation around all axes

	// add rb to phys manager world
	PhysicsManager::GetInstance().AddRigidBody(mRigidBody);

}

void ComponentRigidBody::SyncWithTransform(ComponentTransform* pTransform)
{
	btTransform trans;
	trans = mRigidBody->getWorldTransform();
	pTransform->SetPosition(glm::vec3(trans.getOrigin().x() * 2, trans.getOrigin().y() * 2, trans.getOrigin().z() * 2));
	pTransform->SetRotation(glm::vec3(trans.getRotation().x() * 2, trans.getRotation().y() * 2, trans.getRotation().z() * 2));
}

IComponent::ComponentTypes ComponentRigidBody::GetType() const
{
	return ComponentTypes::COMPONENT_RIGIDBODY;
}
ComponentRigidBody::~ComponentRigidBody()
{
	// remove RB from physcis manager
	PhysicsManager::GetInstance().GetDynamicsWorld().removeRigidBody(mRigidBody);// RemoveRigidBody(mRigidBody);
	// delete rigid body
	delete mRigidBody;
	// delete mCollisionShape;
	delete mMotionState;
}
