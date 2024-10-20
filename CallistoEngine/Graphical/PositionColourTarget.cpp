#include "PositionColourTarget.h"

void PositionColourTarget::Activate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PositionColourTarget::Resize(int width, int height)
{
}
