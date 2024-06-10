
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

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(pMass, mMotionState, pShape, pInertia);

	mRigidBody = new btRigidBody(mMass,mMotionState,mCollisionShape);


	// add rb to phys manager world
	PhysicsManager::GetInstance().AddRigidBody(mRigidBody);
	//std::cout << "mass "<< mRigidBody->getMass() << std::endl;
}

void ComponentRigidBody::SyncWithTransform(ComponentTransform* pTransform)
{

	btTransform pos;
	GetMotionState()->getWorldTransform(pos);
	pos = mRigidBody->getWorldTransform();
	
	//std::cout << "mass " << mRigidBody->getMass()<< " " << pos.getOrigin().x() << " " << pos.getOrigin().y() << " " << pos.getOrigin().z() << std::endl;

	pTransform->SetPosition(glm::vec3(pos.getOrigin().x() *2, pos.getOrigin().y()*2, pos.getOrigin().z()*2));
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
