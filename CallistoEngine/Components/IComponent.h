#pragma once
class IComponent
{
public:
    enum class ComponentTypes {
        COMPONENT_NONE      = 1 << 0,
        COMPONENT_TRANSFORM = 1 << 1 ,
        COMPONENT_MODEL     = 1 << 2 ,
        COMPONENT_SHADER    = 1 << 3 ,
        COMPONENT_RIGIDBODY = 1 << 4 ,
        COMPONENT_COLLIDER  = 1 << 5 ,   
        COMPONENT_LIGHT     = 1 << 6 ,
        COMPONENT_AUDIO     = 1 << 7 ,
        COMPONENT_SCRIPT    = 1 << 8 ,
        COMPONENT_ANIMATION = 1 << 9 ,
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

    friend IComponent::ComponentTypes operator~(IComponent::ComponentTypes type) {
        return static_cast<IComponent::ComponentTypes>(~static_cast<int>(type));
    }

    // Method to exclude COMPONENT_SHADER from the mask
    static bool HasComponent(IComponent::ComponentTypes mask, IComponent::ComponentTypes component) {
        return (mask & component) == component;
    }

    static IComponent::ComponentTypes ExcludeComponent(IComponent::ComponentTypes mask, IComponent::ComponentTypes component) {
        return mask & ~component;
    }
};