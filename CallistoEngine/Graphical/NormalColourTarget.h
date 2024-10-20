#pragma once
#include <glad/glad.h>
#include "RenderTarget.h"

class NormalColourTarget final : public RenderTarget
{
public:
	void Activate() final override;

	NormalColourTarget() : RenderTarget() {}
};