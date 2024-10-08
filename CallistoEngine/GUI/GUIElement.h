#pragma once
#include "../Math/Vector.h"
#include "GUIOrigin.h"

class GUIElement
{

protected:
	GUIOrigin mOrigin;

	Vector3f mPositionOffset;
	Vector3f mPosition;
	Vector3f mRelativePosition;
	float mScale;

	GUIElement() : mPositionOffset(0, 0, 0), mPosition(0, 0, 0), mRelativePosition(0, 0, 0) {};
	
	void ResizeBase(const int pWidth, const int pHeight);
	bool InitialiseBase();

protected:
	virtual void ResizeChild(const int pWidth, const int pHeight) = 0;
	virtual bool InitialiseChild() = 0;

public:
	void SetPosition(const Vector3f& pPos) { mPosition = pPos; }
	const Vector3f& GetPosition() const { return mPosition; }

	void SetRelativePosition(const Vector3f& pRelativePos) { mRelativePosition = pRelativePos; }
	const Vector3f& GetRelativePosition() const { return mRelativePosition; }


	//public function that can be called by anyone
	// calls its private base function
	// calls a protected pure virtual function on the child


	virtual void Resize(const int pWidth, const int pHeight)
	{
		ResizeBase(pWidth, pHeight);
		ResizeChild(pWidth, pHeight);
	}
	virtual bool Initialise()
	{
		InitialiseBase();
			InitialiseChild();
		return true;
	}

	virtual void Render() = 0;
	~GUIElement();
};

