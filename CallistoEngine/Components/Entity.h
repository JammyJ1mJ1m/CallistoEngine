#pragma once
#include "IComponent.h"
#include <vector>
#include <memory>
#include "../Math/Vector.h"
#include "ComponentTransform.h"

class Entity
{
	std::vector<IComponent*> mComponentList;
	std::vector<Entity*> mChildren;

	IComponent::ComponentTypes mMask;

	void create(const Entity& other)
	{
		// copy members over
		mComponentList = other.mComponentList;
		mMask = other.mMask;
	}

	virtual void start() = 0;

	protected:

public:
	const void UpdateChildPositions();
	const void AddChild(Entity* pChild, const Vector3f& pPos);
	
	const void AddChildren(std::vector<Entity*> pChildren) { mChildren.insert(mChildren.end(), pChildren.begin(), pChildren.end()); }
	const std::vector<Entity*> GetChildren() { return mChildren; }
	const Entity* GetChild(int pIndex) { return mChildren[pIndex]; }

	// structors
	Entity();
	Entity(const Entity& other);
	Entity& operator = (const Entity& other)
	{
		if (this != (&other))
			create(other);

		return *this;
	}

	~Entity()
	{
		for (size_t i = 0; i < mComponentList.size(); i++)
		{
			delete mComponentList[i];
		}
	};

	// methods
	void AddComponent(IComponent* pComponent);
	const IComponent::ComponentTypes GetMask() const { return mMask; }

	template<class T>
	inline T* GetComponent() const
	{
		for (IComponent* b : mComponentList)
			if (T* c = dynamic_cast<T*>(b))
				return c;

		return nullptr;
	}

	void UpdateMask(IComponent::ComponentTypes componentType) {
		mMask = static_cast<IComponent::ComponentTypes>(static_cast<int>(mMask) | static_cast<int>(componentType));
	}

	virtual void SetPosition(const Vector3f& pPosition) = 0;

	// common function a lot of entities will have
	virtual void MoveForward() = 0;
	virtual void MoveBackward() = 0;
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;

};