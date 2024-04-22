#pragma once
#include "../ECS.hpp"
#include "../Physics/Math/Vector2D.hpp"

class TransformComponent : public Component
{
    Physics::Math::Vector2D m_Position;

public:
    TransformComponent() : Component(GetComponentTypeID<TransformComponent>()){};

    void Translate(float dX, float dY) noexcept {

    };

    TransformComponent *Clone() const override
    {
        return new TransformComponent(*this);
    }

    void SetPosition(Physics::Math::Vector2D pos)
    {
        this->m_Position = pos;
    };

    Physics::Math::Vector2D &GetPosition()
    {
        return this->m_Position;
    }

    void AddPosition(float x, float y)
    {
        this->m_Position.x = x;
        this->m_Position.y = y;
    }

    void AddPosition(Physics::Math::Vector2D pos)
    {
        this->m_Position.Add(pos);
    }

    void AddX(float x)
    {
        this->m_Position.x += x;
    };
    void AddY(float y)
    {
        this->m_Position.y += y;
    };

    void Update() override{};
    void Init() override{};
    void Render() override{};

    ~TransformComponent() override{};
};