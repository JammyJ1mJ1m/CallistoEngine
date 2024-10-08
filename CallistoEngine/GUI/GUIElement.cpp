#include "GUIElement.h"
#include <iostream>
#include "../Game.h"

void GUIElement::ResizeBase(const int pWidth, const int pHeight)
{

	int defaultWindowWidth = 1423;
	int defaultWidthHeight = 800;

	float widthScale = static_cast<float>(pWidth) / defaultWindowWidth;
	float heightScale = static_cast<float>(pHeight) / defaultWidthHeight;
	mScale = std::min(widthScale, heightScale);

	if ((int)mOrigin & (int)GUIOrigin::_TOP != 0)
	{
		mPosition.SetY(pHeight - mPositionOffset.GetY() * mScale);
		mPosition.SetX(pWidth - mPositionOffset.GetX() * mScale);
	}
}

bool GUIElement::InitialiseBase()
{
	//	 calcualte the offset
	if ((int)mOrigin & (int)GUIOrigin::_TOP != 0)
	{
		float offsetY = Game::GetGame()->GetGameCamera()->mHeight - mPosition.GetY();
		mPositionOffset.SetY(offsetY);
	}

	if ((int)mOrigin & (int)GUIOrigin::_RIGHT != 0)
	{
		float offsetX = Game::GetGame()->GetGameCamera()->mWidth - mPosition.GetX();
		mPositionOffset.SetX(offsetX);
	}

	return false;
}

GUIElement::~GUIElement()
{
}

//GUIElement::GUIElement()
//{
//}
