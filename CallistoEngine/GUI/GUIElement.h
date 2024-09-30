#pragma once
#include "../Math/Vector.h"

class GUIElement
{

protected:
	Vector3f mPosition;
	Vector3f mRelativePosition;

	GUIElement() : mPosition(0, 0, 0), mRelativePosition(0, 0, 0) {};
public:
	void SetPosition(const Vector3f& pPos) { mPosition = pPos; }
	const Vector3f& GetPosition() const { return mPosition; }

	void SetRelativePosition(const Vector3f& pRelativePos) { mRelativePosition = pRelativePos; }
	const Vector3f& GetRelativePosition() const { return mRelativePosition; }

	virtual void Resize(const int pWidth, const int pHeight) = 0;
	virtual void Render() = 0;

	~GUIElement();
};

