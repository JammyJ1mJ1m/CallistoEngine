#pragma once
class IComponent
{
public:
    enum class ComponentTypes {
        COMPONENT_NONE = 0,
        COMPONENT_TRANSFORM = 1 << 0,
        COMPONENT_MODEL = 1 << 1,
        COMPONENT_SHADER = 1 << 2,
        COMPONENT_ANIMATION = 1 << 3,
    };

    virtual ComponentTypes GetType() const = 0;
    IComponent() = default;
    virtual ~IComponent();
};