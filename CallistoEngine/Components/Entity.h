#pragma once
#include "IComponent.h"
#include <vector>
#include <memory>


class Entity
{
	std::vector<  IComponent*> mComponentList;

	IComponent::ComponentTypes mMask;

	void create(const Entity& other)
	{
		// copy members over
		mComponentList = other.mComponentList;
		mMask = other.mMask;
	}

	virtual void start() = 0;


public:

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

	virtual void SetPosition() = 0;

	// common function a lot of entities will have
	virtual void MoveForward() = 0;
	virtual void MoveBackward() = 0;
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;

};