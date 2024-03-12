#pragma once
#include "IComponent.h"
#include <vector>
#include <memory>

class Entity final
{
	std::vector<  IComponent*> mComponentList;

	IComponent::ComponentTypes mMask;

	void create(const Entity& other)
	{
		// copy members over
		mComponentList = other.mComponentList;
		mMask = other.mMask;
	}
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
		for ( IComponent* b : mComponentList)
			if (T* c = dynamic_cast<T*>(b))
				return c;

		return nullptr;
	}

	void UpdateMask(IComponent::ComponentTypes componentType) {
		mMask = static_cast<IComponent::ComponentTypes>(static_cast<int>(mMask) | static_cast<int>(componentType));
	}
};



/*


class Entity final
{
	std::vector< std::shared_ptr <IComponent> > mComponentList;

	IComponent::ComponentTypes mMask;

	void create(const Entity& A)
	{
		mComponentList = A.mComponentList;
		mMask = A.mMask;
	}

public:
	Entity() = default;// default constructor
	Entity(const Entity& A);				// copy constructor
	Entity& operator = (const Entity& A)	// assignment operator
	{
		if (this != (&A))
		{
			create(A);
		}
		return *this;
	}

	void AddComponent(std::shared_ptr <IComponent> pComponent);

	template<class T>
	inline std::shared_ptr <T> GetComponent() const
	{
		for (std::shared_ptr <IComponent> b : mComponentList)
			if (std::shared_ptr<T> c = std::dynamic_pointer_cast<T>(b))
				return c;

		return nullptr;
	}

	void UpdateMask(IComponent::ComponentTypes componentType) {
		mMask = static_cast<IComponent::ComponentTypes>(static_cast<int>(mMask) | static_cast<int>(componentType));
	}

	const IComponent::ComponentTypes& GetMask() const { return mMask; }

	~Entity() = default;
};

*/