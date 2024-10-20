#pragma once
#include <glad/glad.h>
#include "RenderTarget.h"

class PositionColourTarget final : public RenderTarget
{
public:
	void Activate() final override;

	PositionColourTarget() : RenderTarget() {}

	void Resize(int width, int height) override;

};