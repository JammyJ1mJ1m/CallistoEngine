#include "GUIContainer.h"

GUIContainer::GUIContainer(const Vector3f& pPos)
{
	SetPosition(pPos);
}


GUIContainer::~GUIContainer()
{
	for (auto& element : mElements)
	{
		delete element;
	}
}

void GUIContainer::SetPosition(const Vector3f& pPos)
{
	mPosition = pPos;
	UpdateChildren();
}

void GUIContainer::UpdateChildren()
{
	for (auto& element : mElements)
	{
		Vector3f elementPos = element->GetRelativePosition();

		elementPos += mPosition;
		element->SetPosition(elementPos);
	}
}

void GUIContainer::Render()
{
	for (auto& element : mElements)
		element->Render();
}

