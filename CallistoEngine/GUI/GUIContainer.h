#pragma once
#include "GUIElement.h"
#include <vector>
#include <algorithm>

class GUIContainer : public GUIElement
{
	std::vector<GUIElement*> mElements;

public:
	// use this class to bundle gui elements together
	GUIContainer(const Vector3f& pPos);
	~GUIContainer();

	inline void AddElement(GUIElement* pElement) { mElements.push_back(pElement); UpdateChildren(); }
	inline void RemoveElement(int pIndex) {
		if (pIndex >= 0 && pIndex < mElements.size()) {
			mElements.erase(mElements.begin() + pIndex);
		}
	}
	inline void RemoveElement(GUIElement* pElement) {
		mElements.erase(std::remove(mElements.begin(), mElements.end(), pElement), mElements.end());
	}

	void SetPosition(const Vector3f& pPos);
	void UpdateChildren();

	void Resize(const int pWidth, const int pHeight) override;
	void Render() override;
};