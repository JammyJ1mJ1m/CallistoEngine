#pragma once
class IComponent
{
public:
    enum class ComponentTypes {
        COMPONENT_NONE = 0,
        COMPONENT_TRANSFORM = 1 << 0,
        COMPONENT_MODEL = 1 << 2,
        COMPONENT_SHADER = 1 << 4,
        COMPONENT_ANIMATION = 1 << 8,
    };

    virtual ComponentTypes GetType() const = 0;
    IComponent() = default;
    virtual ~IComponent();

    friend IComponent::ComponentTypes operator&(IComponent::ComponentTypes lhs, IComponent::ComponentTypes rhs) {
        return static_cast<IComponent::ComponentTypes>(static_cast<int>(lhs) & static_cast<int>(rhs));
    }

    friend IComponent::ComponentTypes operator|(IComponent::ComponentTypes lhs, IComponent::ComponentTypes rhs) {
        return static_cast<IComponent::ComponentTypes>(static_cast<int>(lhs) | static_cast<int>(rhs));
    }
};