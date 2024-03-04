#pragma once
#include "Engine/Components/IComponent.h"

class ComponentModel : public IComponent
{
	void create(const ComponentModel& A)
	{
		// copy all the data
		//m_data = A.m_data;
		//m_data = new Data(*A.m_data);
	}

public:
	ComponentModel();
	// copy constructor
	ComponentModel(const ComponentModel& other);

	// copy assignment
	ComponentModel& operator=(const ComponentModel& other)
	{
		if (this != (&other))
		{
			create(other);
		}
		return *this;
	}

	~ComponentModel();
};

