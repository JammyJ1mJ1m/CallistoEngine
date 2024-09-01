
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


ComponentRigidBody::ComponentRigidBody(ComponentCollider* pCollider, btScalar pMass, const glm::vec3& pPos, bool gravityEnabled)
{
	mMass = pMass;
	mInertia = btVector3();

	if (pCollider->GetColliderType() != ColliderType::MESH)
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

	if (!gravityEnabled) {
		mRigidBody->setGravity(btVector3(0, 0.0, 0));
	}



	// add rb to phys manager world
	PhysicsManager::GetInstance().AddRigidBody(mRigidBody);
}

//float RadToDeg(float rad)
//{
//	return rad * 180 / 3.14159265359;
//}

void ComponentRigidBody::SyncWithTransform(ComponentTransform* pTransform)
{
	btTransform bulletTransform;
	mRigidBody->getMotionState()->getWorldTransform(bulletTransform);

	pTransform->SyncTransform(bulletTransform);


	//btTransform trans;
	//trans = mRigidBody->getWorldTransform();
	//pTransform->SetPosition(glm::vec3(trans.getOrigin().x()/* * 2*/, trans.getOrigin().y() /** 2*/, trans.getOrigin().z() /** 2*/));
	//glm::vec3 t = glm::vec3(trans.getRotation().x() /** 2*/, trans.getRotation().y()/* * 2*/, trans.getRotation().z()/* * 2*/);
	//pTransform->SetRotation(t);
}

void ComponentRigidBody::SetPosition(glm::vec3 pPos)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pPos.x, pPos.y, pPos.z));
	mRigidBody->setWorldTransform(transform);
	mRigidBody->getMotionState()->setWorldTransform(transform);

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
