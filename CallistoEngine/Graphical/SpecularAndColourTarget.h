#pragma once
#include <glad/glad.h>
#include "RenderTarget.h"

class SpecularAndColourTarget final : public RenderTarget
{
public:
	void Activate() final override;

	SpecularAndColourTarget() : RenderTarget() {}
};