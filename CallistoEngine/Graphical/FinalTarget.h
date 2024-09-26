#pragma once
#include <glad/glad.h>
#include "RenderTarget.h"

class FinalTarget final : public RenderTarget
{
public:
	void Activate() final override;

	FinalTarget() : RenderTarget() {}
};