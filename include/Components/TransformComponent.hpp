#pragma once
#include "../ECS.hpp"

class TransformComponent : public Component
{
    float xPos;
    float yPos;

public:
    TransformComponent() : Component(GetComponentTypeID<TransformComponent>()){};

    void Translate(float dX, float dY) noexcept
    {
        this->xPos += dX;
        this->yPos += dY;
    };

    TransformComponent *Clone() const override
    {
        return new TransformComponent(*this);
    }
    void Update() override{};
    void Init() override{};
    void Render() override{};

    ~TransformComponent() override{};
};