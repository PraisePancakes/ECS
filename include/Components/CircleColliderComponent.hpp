#pragma once
#include "../ECS.hpp"

class CircleColliderComponent : public Component
{
    // CircleShape m_CollisionCircle;
public:
    CircleColliderComponent() : Component(GetComponentTypeID<CircleColliderComponent>()) { std::cout << "Collider Component Constructed " << GetComponentTypeID<CircleColliderComponent> << std::endl; };
    CircleColliderComponent *Clone() const override
    {
        return new CircleColliderComponent(*this);
    }

    void Update() override{};
    void Render() override{};
    void Init() override{};

    ~CircleColliderComponent() override{};
};