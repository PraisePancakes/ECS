#pragma once
#include "Component.hpp"

class TransformComponent : public Component
{
    float xPos;
    float yPos;

public:
    TransformComponent();

    void Translate(float dX, float dY) noexcept;
    void Update() override;
    void Init() override;
    void Render() override;

    ~TransformComponent() override;
};