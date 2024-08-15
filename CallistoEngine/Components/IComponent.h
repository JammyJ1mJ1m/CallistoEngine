#pragma once
class IComponent
{
public:
    enum class ComponentTypes {
        COMPONENT_NONE = 0,
        COMPONENT_TRANSFORM =   1 ,
        COMPONENT_MODEL =       2 ,
        COMPONENT_SHADER =      3 ,
        COMPONENT_RIGIDBODY =   4 ,
        COMPONENT_COLLIDER =    5 ,   
        COMPONENT_SCRIPT =      6 ,
        COMPONENT_AUDIO =       7 ,
        COMPONENT_ANIMATION =   8 ,
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