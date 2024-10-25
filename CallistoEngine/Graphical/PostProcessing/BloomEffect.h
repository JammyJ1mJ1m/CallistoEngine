#pragma once
#include "../PostProcessEffect.h"
class BloomEffect : public PostProcessEffect
{
    void OnActivate() final override;

public:
    BloomEffect() : PostProcessEffect()
    {
        usesDepth = false;
    }
};

